#include"explosion.h"
#include"manager.h"
#include"renderer.h"
#include"sound.h"

#define TEXTURE_NAME "data/Texture/bullet/explosion000.png"

LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;

CExplosion::CExplosion(int nPrioity)
{
	m_nCountAnim = 0;
	m_nPatternAnim = 0;
}

CExplosion::~CExplosion()
{

}

HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos,size);
	SetObjType(CScene::OBJTYPE_EXPLOSION);
	return S_OK;
}

void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
}

void CExplosion::Update(void)
{
	CSound *pSound;
	pSound = CManager::GetSound();

	m_nCountAnim++;
	if (m_nCountAnim % 4 == 0)
	{
		m_nCountAnim = 0;
		m_nPatternAnim++;
		CScene2D::SetTex(m_nPatternAnim);

		if (m_nPatternAnim == 7)
		{
			pSound->PlaySound(pSound->SOUND_EXPLOSION_SE);
			Uninit();
		}
	}
}

void CExplosion::Draw(void)
{
	CScene2D::Draw();
}

HRESULT CExplosion::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME,
		&m_pTexture);

	return S_OK;
}

void CExplosion::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

CExplosion *CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �N���X�̐���
	CExplosion *pExplosion;
	pExplosion = new CExplosion;

	// �k���`�F�b�N
	if (pExplosion != NULL)
	{
		// ����������
		pExplosion->Init(pos,size);
		pExplosion->BindTexture(m_pTexture);
	}

	return pExplosion;
}