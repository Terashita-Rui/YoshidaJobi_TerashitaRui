#include"bullet_penetration.h"
#include"bullet.h"
#include"game.h"
#include"manager.h"
#include"renderer.h"
#include"explosion.h"
#include"enemy.h"
#include"enemy_homing.h"
#include"score.h"
#include"math.h"

//�e�N�X�`��
#define TEXTURE_NAME "data/Texture/bullet/bullet000.png"

LPDIRECT3DTEXTURE9 CBullet_p::m_pTexture = NULL;

CBullet_p::CBullet_p(OBJTYPE nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bUse = false;
	m_move = D3DXVECTOR3(6.0f, 0.0f, 0.0f);
	m_fSpeed = 6.0f;
}

CBullet_p::~CBullet_p()
{

}

HRESULT CBullet_p::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_size = size;
	m_pos = pos;
	CScene2D::Init(pos, size);
	SetObjType(CScene::OBJTYPE_BULLET);

	return S_OK;
}

void CBullet_p::Uninit(void)
{
	CScene2D::Uninit();
}

void CBullet_p::Update(void)
{
	for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	{
		CScene *pScene;
		pScene = CScene::GetScene(OBJTYPE_ENEMY, nCntScene);
		if (pScene != NULL)
		{
			CScene::OBJTYPE objType;
			objType = pScene->GetObjType();

			//obj���G�Ȃ�           �@���G
			if (objType == CScene::OBJTYPE_ENEMY)
			{
				m_EnemyPos = pScene->GetPos();
				m_Vector = m_EnemyPos - m_pos;
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
	m_pos.x += m_fSpeed;

	//�����蔻��
	Collision();
}

void CBullet_p::Draw(void)
{
	CScene2D::Draw();
}

bool CBullet_p::Collision(void)
{
	CScore *pScore;
	pScore = CGame::GetScore();

	for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	{
		CScene *pScene;
		pScene = CScene::GetScene(OBJTYPE_ENEMY, nCntScene);

		if (pScene != NULL)
		{
			CScene::OBJTYPE objType;
			objType = pScene->GetObjType();

			//obj���G�Ȃ�           �@���G
			if (objType == CScene::OBJTYPE_ENEMY)
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
					pScore->AddScore(10);
					//�G����
					pScene->Uninit();
					m_bUse = true;
				}
			}
		}
	}
	return m_bUse;
}
//����
CBullet_p *CBullet_p::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �N���X�̐���
	CBullet_p *pBullet_p;
	pBullet_p = new CBullet_p;

	// �k���`�F�b�N
	if (pBullet_p != NULL)
	{
		// ����������
		pBullet_p->Init(pos, size);
		pBullet_p->BindTexture(m_pTexture);
	}

	return pBullet_p;
}

HRESULT CBullet_p::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME,
		&m_pTexture);

	return S_OK;
}

void CBullet_p::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}