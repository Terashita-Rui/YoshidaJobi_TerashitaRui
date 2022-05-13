#include"title.h"
#include"scene2D.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"fade.h"
#include"sound.h"

CTitle::CTitle(OBJTYPE nPriority) :CScene(nPriority)
{
	for (int nCnt = 0; nCnt < SELECT_MAX; nCnt++)
	{
		m_apScene2D[nCnt] = NULL;
	}

}

CTitle::~CTitle()
{

}

HRESULT CTitle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene::SetObjType(CScene::OBJTYPE_NONE);

	CSound *pSound;
	pSound = CManager::GetSound();
	pSound->PlaySound(pSound->SOUND_TITLE_BGM);

	CScene2D::Load();

	CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), CScene2D::TEXTYPE_TITLE_BG); //�^�C�g���w�i
	CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 200.0f, 0.0f), D3DXVECTOR3(550.0f, 100.0f, 0.0f), CScene2D::TEXTYPE_TITLE_LOGO);	//�^�C�g����
	m_apScene2D[SELECT_GAME] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 480.0f, 0.0f), D3DXVECTOR3(200.0f, 50.0f, 0.0f), CScene2D::TEXTYPE_TITLE_GAMEBUTTON); //�Q�[���ɑJ�ڂ���BUTTON
	m_apScene2D[SELECT_OP] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 620.0f, 0.0f), D3DXVECTOR3(200.0f, 50.0f,0.0f), CScene2D::TEXTYPE_TITLE_OP_BUTTON);	//�����������BUTTON

	m_apScene2D[SELECT_GAME]->SetColor(SELECT_COL);
	m_apScene2D[SELECT_OP]->SetColor(DEFAULT_COL);

	m_bOP_button = false;
	m_bGame_button = false;
	m_nSelect = SELECT_GAME;

	return S_OK;
}

void CTitle::Uninit(void)
{
	Unload();

	Release();
}

void CTitle::Update(void)
{
	CInputKeyborad *pInputKeyborad;
	pInputKeyborad = CManager::GetInputKeyborad();

	CSound *pSound;
	pSound = CManager::GetSound();

#ifdef _DEBUG
	if (pInputKeyborad->GetPress(DIK_RETURN) == true)
	{//�G���^�[�ŉ�ʑJ��
		//CFade::SetFade(CManager::MODE_GAME);
	}
#endif

	if (pInputKeyborad->GetTrigger(DIK_SPACE) || pInputKeyborad->GetTrigger(DIK_RETURN))
	{
		//���������ʕ\�����Ă鎞
		if (m_bOP_button == true)
		{
			m_bOP_button = false;
			m_pOp->Uninit();
		}
		else
		{
			switch (m_nSelect)
			{
			default:
				break;
			case SELECT_GAME:
				//�Q�[����ʂɑJ��
				pSound->PlaySound(pSound->SOUND_SELECT_DECISION_SE);
				CFade::SetFade(CManager::MODE_GAME);
				pSound->StopSound(pSound->SOUND_TITLE_BGM);
				break;
			case SELECT_OP:
				//����������
				pSound->PlaySound(pSound->SOUND_SELECT_DECISION_SE);
				m_pOp = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), CScene2D::TEXTYPE_TITLE_OP); //�������
				m_bOP_button = true;
				break;
			}
		}
	}

	//���������ʏI��
	//ESC�L�[��������
	if (pInputKeyborad->GetTrigger(DIK_ESCAPE))
	{
		if (m_bOP_button == true)
		{
			m_bOP_button == false;
			m_pOp->Uninit();
		}

		else
		{
			PostQuitMessage(0);
		}
	}

	//�I�����̐؂�ւ�
	if(m_bGame_button ==false&&m_bOP_button==false)
	{
		//w������������
		if (pInputKeyborad->GetTrigger(DIK_W) || pInputKeyborad->GetTrigger(DIK_UP))
		{
			pSound->PlaySound(pSound->SOUND_SELECT_SE);
			m_apScene2D[m_nSelect]->SetColor(DEFAULT_COL);
			if (m_nSelect <= 0) 
			{
				m_nSelect = SELECT_MAX - 1;
			}
			else
			{
				m_nSelect--;
			}
			m_apScene2D[m_nSelect]->SetColor(SELECT_COL);
		}

		//s������������
		if (pInputKeyborad->GetTrigger(DIK_S) || pInputKeyborad->GetTrigger(DIK_DOWN))
		{
			pSound->PlaySound(pSound->SOUND_SELECT_SE);
			m_apScene2D[m_nSelect]->SetColor(DEFAULT_COL);
			if (m_nSelect >= SELECT_MAX - 1)
			{
				m_nSelect = 0;
			}
			else
			{
				m_nSelect++;
			}
			m_apScene2D[m_nSelect]->SetColor(SELECT_COL);
		}

	}
}

void CTitle::Draw(void)
{

}

HRESULT CTitle::Load(void)
{

	return S_OK;
}

void CTitle::Unload(void)
{
}