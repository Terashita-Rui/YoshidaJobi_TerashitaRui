#include"result.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"sound.h"
#include"scene2D.h"
#include"ranking.h"

CResult::CResult(OBJTYPE nPriority) : CScene::CScene(nPriority)
{
	m_pRanking = NULL;
}

CResult::~CResult()
{

}

HRESULT CResult::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CSound *pSound;
	pSound = CManager::GetSound();
	pSound->PlaySound(pSound->SOUND_RESULT_BGM);

	CScene2D::Load();
	
	CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), CScene2D::TEXTYPE_RESULT_BG); //ƒ^ƒCƒgƒ‹”wŒi

	//if (m_pRanking == NULL)
	//{
	//	m_pRanking = CRanking::Create(D3DXVECTOR3(SCREEN_WIDTH + 120 * MAX_SCORE / 2.0f, 60, 0.0f),
	//		D3DXVECTOR3(120, 240, 0.0f));
	//}

	return S_OK;
}

void CResult::Uninit(void)
{
	Release();
}

void CResult::Update(void)
{
	CInputKeyborad *pInputKeyborad;
	pInputKeyborad = CManager::GetInputKeyborad();
	CSound *pSound;
	pSound = CManager::GetSound();

	if (pInputKeyborad->GetPress(DIK_RETURN) == true || pInputKeyborad->GetPress(DIK_SPACE) == true)
	{
		pSound->Stop();
		CManager::SetMode(CManager::MODE_TITLE);
	}
	if (pInputKeyborad->GetTrigger(DIK_ESCAPE))
	{
		PostQuitMessage(0);
	}
}

void CResult::Draw(void)
{

}