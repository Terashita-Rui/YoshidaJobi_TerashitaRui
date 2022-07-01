#include"bullet.h"
#include"game.h"
#include"manager.h"
#include"renderer.h"
#include"explosion.h"
#include"enemy.h"
#include"enemy_homing.h"
#include"score.h"
#include"math.h"

#define TEXTURE_NAME "data/Texture/bullet/bullet001.png"

LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;

CBullet::CBullet(OBJTYPE nPriority) : CScene2D(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bUse = false;
	m_move = D3DXVECTOR3(6.0f, 0.0f, 0.0f);
	m_fSpeed = 8.0f;
}

CBullet::~CBullet()
{

}

HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_size = size;
	m_pos = pos;
	CScene2D::Init(pos,size);
	//���̃I�u�W�F�N�g�͒e���Ďw�肷��
	SetObjType(OBJTYPE_BULLET);

	return S_OK;
}

void CBullet::Uninit(void)
{
	CScene2D::Uninit();
}

void CBullet::Update(void)
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
		m_bUse = true;
		Uninit();
	}
	//pos�擾
	m_pos = GetPos();

	//�ړ�
	m_pos.x += m_fSpeed;

	//�����蔻��
	Collision();
}

void CBullet::Draw(void)
{
	CScene2D::Draw();
}

bool CBullet::Collision(void)
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
					srand((unsigned int)time(NULL));
					//����
					CExplosion::Create(Pos, D3DXVECTOR3(EXPLOSION_WIDTH, EXPLOSION_HIGHT, 0.0f));
					pScore->AddScore(10);
					//�G����
					pScene->Uninit();
					m_bUse = true;
					//�e����
					Uninit();
					break;
				}
			}
		}
	}
		return m_bUse;
}

//����
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �N���X�̐���
	CBullet *pBullet;
	pBullet = new CBullet(OBJTYPE_BULLET);

	// �k���`�F�b�N
	if (pBullet != NULL)
	{
		// ����������
		pBullet->Init(pos, size);
		pBullet->BindTexture(m_pTexture);
	}

	pBullet->m_pos = pos;
	pBullet->m_size = size;

	return pBullet;
}

HRESULT CBullet::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME,
		&m_pTexture);

	return
		S_OK;
}

void CBullet::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}