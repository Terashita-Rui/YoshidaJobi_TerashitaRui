#include"scene2D.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"

//�e�N�X�`��
#define TEXTURE_TITLE_BG "data/Texture/title/title.png"											//�w�i
#define TEXTURE_TITLE_LOGO "data/Texture/title/title_logo.png"									//�^�C�g�����S
#define TEXTURE_TITLE_GAME "data/Texture/title/start_button.png"								//�Q�[���ɑJ�ڂ���{�^��
#define TEXTURE_TITLE_OP_BUTTON "data/Texture/title/operation_button2.png"						//��������Ɉړ�����{�^��
#define TEXTURE_TITLE_OP "data/Texture/title/operation.png"										//����������

#define TEXTURE_GAME_SELECTBULLET_NORMAL "data/Texture/game/select_bullet_normal.png"			//�m�[�}���e�I��
#define TEXTURE_GAME_SELECTBULLET_HOMING "data/Texture/game/select_bullet_homing.png"			//�z�[�~���O�e�I��
#define TEXTURE_GAME_SELECTBULLET_PENETRETION "data/Texture/game/select_bullet_penetration.png" //�ђʒe�I��

#define TEXTURE_RESULT_BG "data/Texture/result/rankingBG.png"									//���U���g�w�i

LPDIRECT3DTEXTURE9 CScene2D::m_apTexture[TEXTYPE_MAX] = {};

CScene2D::CScene2D(OBJTYPE nPriority) : CScene::CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

CScene2D::~CScene2D()
{

}

HRESULT CScene2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice(); //�f�o�C�X���擾����

	m_pos = pos;
	m_size = size;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	VERTEX_2D *pVtx; //���_���̃|�C���^

					 //���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

void CScene2D::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�����[�X���ĂԂ�m_pVtxBuff���f���[�g����邩��Ō�ɂ��
	Release();
}

void CScene2D::Update(void)
{

}

void CScene2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice(); //�f�o�C�X���擾����
													//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D); //���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, m_pTexture);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); //�|���S���̕`�� 
}

CScene2D *CScene2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int ntype)
{
	CScene2D *pScene2D;
	pScene2D = new CScene2D;

	if (pScene2D != NULL)
	{
		pScene2D->m_pTexture = m_apTexture[ntype];
		pScene2D->Init(pos, size);
	}

	return pScene2D;
}

void CScene2D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

D3DXVECTOR3 CScene2D::GetPos(void)
{
	return m_pos;
}

void CScene2D::SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;
	m_pos = pos;
	m_size = size;
	CScene::SetPos(m_pos);
	CScene::SetSize(m_size);

	// �ʒu���X�V
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_pos.x - size.x, m_pos.y - size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + size.x, m_pos.y - size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - size.x, m_pos.y + size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + size.x, m_pos.y + size.y, 0.0f);

	m_pVtxBuff->Unlock();
}

bool CScene2D::SetTex(int nPatternAnim)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	// �ʒu���X�V
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nPatternAnim * 0.125f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(nPatternAnim * 0.125f + 0.125f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(nPatternAnim * 0.125f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(nPatternAnim * 0.125f + 0.125f, 1.0f);

	m_pVtxBuff->Unlock();

	return true;
}

D3DXVECTOR3 CScene2D::GetSize(void)
{
	return m_size;
}

void CScene2D::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

void CScene2D::SetColor(D3DXCOLOR col)
{
	m_col = col;

	//���_�o�b�t�@�̍X�V
	if (m_pVtxBuff != NULL)
	{
		VERTEX_2D *pVtx;
		//���_�o�b�t�@�̃��b�N
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		// ���_����ݒ�
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;

		//���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}

void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	// �e�N�X�`���̊��蓖��
	m_pTexture = pTexture;
}

HRESULT CScene2D::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	//�^�C�g��
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TITLE_BG,
		&m_apTexture[TEXTYPE_TITLE_BG]);
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TITLE_LOGO,
		&m_apTexture[TEXTYPE_TITLE_LOGO]);
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TITLE_GAME,
		&m_apTexture[TEXTYPE_TITLE_GAMEBUTTON]);
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TITLE_OP_BUTTON,
		&m_apTexture[TEXTYPE_TITLE_OP_BUTTON]);
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TITLE_OP,
		&m_apTexture[TEXTYPE_TITLE_OP]);

	//�Q�[��
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GAME_SELECTBULLET_NORMAL,
		&m_apTexture[TEXTYPE_GAME_NORMALBULLET]);
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GAME_SELECTBULLET_HOMING,
		&m_apTexture[TEXTYPE_GAME_HOMINGBULLET]);
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GAME_SELECTBULLET_PENETRETION,
		&m_apTexture[TEXTYPE_GAME_PENETRETIONBULLET]);

	//���U���g
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_RESULT_BG,
		&m_apTexture[TEXTYPE_RESULT_BG]);

	return S_OK;
}

void CScene2D::Unload(void)
{
	for (int nCnt = 0; nCnt < TEXTYPE_MAX; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;

		}
	}
}