#include"player.h"
#include"scene2D.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"
#include"sound.h"

#include"bullet.h"
#include"bullet_homing.h"
#include"bullet_penetration.h"

#define TEXTURE_NAME "data/Texture/jet.png"

LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;
CBullet *CPlayer::m_pBullet = NULL;
CBullet_p *CPlayer::m_pBullet_p = NULL;
CBullet_h *CPlayer::m_pBullet_h = NULL;

CPlayer::CPlayer(OBJTYPE nPriority) :CScene2D(nPriority)
{
	m_move = D3DXVECTOR3(4.0f, 0.0f, 0.0f);
	m_nCT = 0;
	m_nButtetNum = 1;
}

CPlayer::~CPlayer()
{

}

HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_size = size;
	m_pos = pos;

	CScene2D::Init(pos,size);
	SetObjType(CScene::OBJTYPE_PLAYER);
	return S_OK;
}

void CPlayer::Uninit(void)
{
	CSound *pSound;
	pSound = CManager::GetSound();

	pSound->Stop();
	CScene2D::Uninit();
}

void CPlayer::Update(void)
{
	CScene2D::Update();
	CInputKeyborad *pInputKeyborad;
	CSound *pSound;
	pSound = CManager::GetSound();
	m_nCT++;
	pInputKeyborad = CManager::GetInputKeyborad();
	D3DXVECTOR3				pos;	//�|���S���̈ʒu
	pos = GetPos();

	//���ړ�
	if (pInputKeyborad->GetPress(DIK_A) == true)
	{
		pos.x -= m_move.x;
	}

	//�E�ړ�
	if (pInputKeyborad->GetPress(DIK_D) == true)
	{
		pos.x += 4.0f;
	}

	//��ړ�
	if (pInputKeyborad->GetPress(DIK_W) == true)
	{
		pos.y -= 4.0f;
	}

	//���ړ�
	if (pInputKeyborad->GetPress(DIK_S) == true)
	{
		pos.y += 4.0f;
	}

	//�X�e�[�W�O�ɏo�悤�Ƃ���Ɣ��΂���o��悤�ɂȂ鏈��
	if (pos.x >= 1280.0f)
	{
		pos.x = 0.0f;
	}
	else if (pos.x <= 0.0f)
	{
		pos.x = 1280.0f;
	}

	if (pos.y >= 720.0f)
	{
		pos.y = 0.0f;
	}
	else if (pos.y <= 0.0f)
	{
		pos.y = 720.0f;
	}

	//�e�؂�ւ�
	if (pInputKeyborad->GetTrigger(DIK_Q) || pInputKeyborad->GetTrigger(DIK_LEFT))
	{
		m_nButtetNum--;
	}
	if (pInputKeyborad->GetTrigger(DIK_E) || pInputKeyborad->GetTrigger(DIK_RIGHT))
	{
		m_nButtetNum++;
	}
	//1�`3�Ő؂�ւ�������1������3���傫���Ȃ�����1��3�ɂ���
	if (m_nButtetNum >= 4)
	{
		m_nButtetNum = 3;
	}
	if (m_nButtetNum <= 0)
	{
		m_nButtetNum = 1;
	}

	//�e����
	if (pInputKeyborad->GetPress(DIK_SPACE) == true)
	{
		if (m_nCT > 30)
		{
			switch (m_nButtetNum)
			{
			case 1:
				pSound->PlaySound(pSound->SOUND_SHOOT_SE);
				CBullet::Create(pos, D3DXVECTOR3(BULLET_WIDTH, BULLET_HEIGHT, 0.0f));
				break;
			case 2:
				pSound->PlaySound(pSound->SOUND_SHOOT_SE);
				CBullet_h::Create(pos, D3DXVECTOR3(BULLET_WIDTH, BULLET_HEIGHT, 0.0f));
				break;
			case 3:
				pSound->PlaySound(pSound->SOUND_SHOOT_SE);
				CBullet_p::Create(pos, D3DXVECTOR3(BULLET_WIDTH, BULLET_HEIGHT, 0.0f));
				break;
			default:
				break;
			}

			//�z�[�~���O�e�����o���p
			//CBullet_h::Create(pos, D3DXVECTOR3(BULLET_WIDTH, BULLET_HEIGHT, 0.0f));

			m_nCT = 0;
		}
	}
	//pos�̏���n��
	SetPosition(pos, m_size);
}

void CPlayer::Draw(void)
{
	CScene2D::Draw();
}

CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CPlayer *pPlayer;
	pPlayer = new CPlayer(OBJTYPE_PLAYER);

	if (pPlayer != NULL)
	{
		pPlayer->Init(pos,size);
		pPlayer->BindTexture(m_pTexture);
	}

	pPlayer->SetPos(pos);
	pPlayer->m_pos = pos;
	pPlayer->m_size = size;

	return pPlayer;
}

HRESULT CPlayer::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME,
		&m_pTexture);

	return S_OK;
}

void CPlayer::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;

	}
}