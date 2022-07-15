#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "input.h"
#include "score.h"
#include "number.h"
#include"sound.h"

#include "title.h"
#include "game.h"
#include "result.h"

CRenderer *CManager::m_pRenderer = NULL;
CInputKeyborad *CManager::m_pInputKeyborad = NULL;
CPlayer *CManager::m_pPlayer = NULL;
CEnemy *CManager::m_pEnemy = NULL;
CScore *CManager::m_pScore = NULL;
CNumber *CManager::m_pNumber = NULL;
CSound *CManager::m_pSound = NULL;

CTitle *CManager::m_pTitle = NULL;
CGame *CManager::m_pGame = NULL;
CResult *CManager::m_pResult = NULL;
CManager::MODE CManager::m_mode = MODE_TITLE;

CManager::CManager()
{

}

CManager::~CManager()
{

}

HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
		//レンダリング処理生成
		m_pRenderer = new CRenderer;
		m_pRenderer->Init(hWnd, true);

		//入力処理生成
		m_pInputKeyborad = new CInputKeyborad;
		m_pInputKeyborad->Init(hInstance, hWnd);

		//サウンド処理生成
		m_pSound = new CSound;
		m_pSound->Init(hInstance, hWnd);

	return S_OK;
}

void CManager::Uninit(void)
{
	//オブジェクト全破壊
	CScene::ReleaseAll();

	//キーボードの破棄
	if (m_pInputKeyborad != NULL)
	{
		m_pInputKeyborad->Uninit();
		delete m_pInputKeyborad;
		m_pInputKeyborad = NULL;
	}
	
	//レンダラーの破棄
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

void CManager::Update(void)
{
	//キーボードの更新処理
	if (m_pInputKeyborad != NULL)
	{
		m_pInputKeyborad->Update();
	}
	//レンダラーの更新処理
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}
}

void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}

CInputKeyborad *CManager::GetInputKeyborad(void)
{
	return m_pInputKeyborad;
}

CPlayer *CManager::GetPlayer(void)
{
	return m_pPlayer;
}

CEnemy* CManager::GetEnemy(void)
{
	return m_pEnemy;
}

CManager::MODE CManager::GetMode()
{
	return m_mode;
}

void CManager::SetMode(CManager::MODE mode)
{
	CScene::ReleaseAll();

	switch (mode)
	{
	case MODE_TITLE:
			m_pTitle = new CTitle;
			m_pTitle->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		break;
	case MODE_GAME:
			m_pGame = new CGame;
			m_pGame->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		break;
	case MODE_RESULT:
			m_pResult = new CResult;
			m_pResult->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		break;
	default:
		break;
	}

	m_mode = mode;
}

CSound *CManager::GetSound(void)
{
	return m_pSound;
}