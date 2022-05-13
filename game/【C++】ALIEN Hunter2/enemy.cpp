#include"enemy.h"
#include"renderer.h"
#include"manager.h"
#include"explosion.h"
#include"score.h"
#include"fade.h"
#include"score.h"
#include"game.h"

#define TEXTURE_NAME "data/Texture/enemy/enemy000.png"

LPDIRECT3DTEXTURE9 CEnemy::m_pTexture = NULL;

CEnemy::CEnemy(OBJTYPE nPriority) : CScene2D(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bUse = false;
	m_move = D3DXVECTOR3(6.0f, 0.0f, 0.0f);
	m_fSpeed = 4.0f;
}

CEnemy::~CEnemy()
{

}

HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_pos = pos;
	m_size = size;
	CScene2D::Init(pos,size);
	SetObjType(CScene::OBJTYPE_ENEMY);
	return S_OK;
}

void CEnemy::Uninit(void)
{
	CScene2D::Uninit();
}

void CEnemy::Update(void)
{
	for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	{
		CScene *pScene;
		//obj�Ƀv���C���[�w��
		pScene = CScene::GetScene(OBJTYPE_PLAYER, nCntScene);
		if (pScene != NULL)
		{
			CScene::OBJTYPE objType;
			objType = pScene->GetObjType();

			//obj���v���C���[�Ȃ�
			if (objType == CScene::OBJTYPE_PLAYER)
			{
				m_PlayerPos = pScene->GetPos();
				m_Vector = m_PlayerPos - m_pos;
				m_fLenght = sqrt((m_Vector.x*m_Vector.x) + (m_Vector.y*m_Vector.y));
				m_fAngle = atan2(m_Vector.x, m_Vector.y);
			}
		}
	}
	//���n��
	SetPosition(m_pos, m_size);

	//�e��ʊO�s���������
	if (m_pos.x > SCREEN_WIDTH ||
		m_pos.x < 0 ||
		m_pos.y > SCREEN_HEIGHT ||
		m_pos.y < 0)
	{
		Uninit();
	}
	//pos�擾
	m_pos = GetPos();

	//�ړ�
	m_pos.x -= m_fSpeed;

	//�����蔻��
	Collision();
}

void CEnemy::Draw(void)
{
	CScene2D::Draw();
}

bool CEnemy::Collision(void)
{
	for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	{
		CScene *pScene;
		pScene = CScene::GetScene(OBJTYPE_PLAYER, nCntScene);

		if (pScene != NULL)
		{
			CScene::OBJTYPE objType;
			objType = pScene->GetObjType();

			//obj���v���C���[�Ȃ�
			if (objType == CScene::OBJTYPE_PLAYER)
			{
				//obj�̊e���
				D3DXVECTOR3 Pos = pScene->GetPos();
				D3DXVECTOR3 Size = pScene->GetSize();

				//�����蔻����{����������
				if (m_pos.x + m_size.x > Pos.x - Size.x &&
					m_pos.x - m_size.x < Pos.x + Size.x &&
					m_pos.y + m_size.y > Pos.y - Size.y &&
					m_pos.y - m_size.y < Pos.y + Size.y)
				{
					//����
					CExplosion::Create(Pos, D3DXVECTOR3(EXPLOSION_WIDTH, EXPLOSION_HIGHT, 0.0f));
					//�v���C���[����
					pScene->Uninit();
					CFade::SetFade(CManager::MODE_RESULT);
					m_bUse = true;
					Uninit();
					return m_bUse;
					break;
				}
			}
		}
	}
}

CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CEnemy *pEnemy;
	pEnemy = new CEnemy(OBJTYPE_ENEMY);

	if (pEnemy != NULL)
	{
		pEnemy->Init(pos, size);
		pEnemy->BindTexture(m_pTexture);
	}

	pEnemy->m_pos = pos;
	pEnemy->m_size = size;

	return pEnemy;
}

HRESULT CEnemy::Load(void)
{
	// �f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME,
		&m_pTexture);

	return S_OK;
}

void CEnemy::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}