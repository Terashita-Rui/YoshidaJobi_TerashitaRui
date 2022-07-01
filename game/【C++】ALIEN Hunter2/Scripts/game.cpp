#include"game.h"
#include"manager.h"
#include"input.h"
#include"player.h"
#include"number.h"
#include"explosion.h"
#include"fade.h"
#include"score.h"
#include"sound.h"
#include"scene2D.h"

#include"enemy.h"
#include"enemy_homing.h"

#include"bullet.h"
#include"bullet_homing.h"
#include"bullet_penetration.h"

CPlayer *CGame::m_pPlayer = NULL;
CScore *CGame::m_pScore = NULL;
CNumber *CGame::m_pNumber = NULL;
CEnemy *CGame::m_pEnemy = NULL;
CEnemy_h *CGame::m_pEnemy_h = NULL;

CGame::CGame(OBJTYPE nPriority) : CScene::CScene(nPriority)
{
	for (int nCnt = 0; nCnt<4; nCnt++)
	{
		m_nCT[nCnt] = 0;
		m_nTime[nCnt] = 0;
		m_apScene2D[nCnt] = NULL;
	}
}

CGame::~CGame()
{

}

HRESULT CGame::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//テクスチャ読み込み
	CPlayer::Load();
	CExplosion::Load();
	CNumber::Load();

	CEnemy::Load();
	CEnemy_h::Load();

	CBullet::Load();
	CBullet_h::Load();
	CBullet_p::Load();

	CScene2D::Load();

	CSound *pSound;
	pSound = CManager::GetSound();
	pSound->PlaySound(pSound->SOUND_GAME_BGM);

	//各ポリゴン生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(200.0f, 200.0f, 0.0f), D3DXVECTOR3(PLAYER_WIDTH, PLAYER_HIGHT, 0.0f));

	
	m_apScene2D[SELECT_NORMAL] = CScene2D::Create(D3DXVECTOR3(SELECT_BULLET_POS_X, SELECT_BULLET_POS_Y, 0.0f), D3DXVECTOR3(SELECT_BULLET_SIZE_X, SELECT_BULLET_SIZE_Y, 0.0f), CScene2D::TEXTYPE_GAME_NORMALBULLET); //ノーマル弾選択
	m_apScene2D[SELECT_HOMING] = CScene2D::Create(D3DXVECTOR3(SELECT_BULLET_POS_X, SELECT_BULLET_POS_Y, 0.0f), D3DXVECTOR3(SELECT_BULLET_SIZE_X, SELECT_BULLET_SIZE_Y, 0.0f), CScene2D::TEXTYPE_GAME_HOMINGBULLET); //ホーミング弾選択
	m_apScene2D[SELECT_PENETRETION] = CScene2D::Create(D3DXVECTOR3(SELECT_BULLET_POS_X, SELECT_BULLET_POS_Y, 0.0f), D3DXVECTOR3(SELECT_BULLET_SIZE_X, SELECT_BULLET_SIZE_Y, 0.0f), CScene2D::TEXTYPE_GAME_PENETRETIONBULLET); //貫通弾選択

	m_pScore = CScore::Create(D3DXVECTOR3(880.0f, 50.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));

	m_apScene2D[SELECT_NORMAL]->SetColor(SELECT_COL);
	m_apScene2D[SELECT_HOMING]->SetColor(DEFAULT_COL);
	m_apScene2D[SELECT_PENETRETION]->SetColor(DEFAULT_COL);

	m_nSelect = SELECT_NORMAL;

	return S_OK;
}

void CGame::Uninit(void)
{
	//テクスチャアンロード
	CPlayer::Unload();
	CExplosion::Unload();
	CNumber::Unload();

	CEnemy::Unload();
	CEnemy_h::Unload();

	CBullet::Unload();
	CBullet_h::Unload();
	CBullet_p::Unload();

	Release();
}

void CGame::Update(void)
{
	CSound *pSound;
	pSound = CManager::GetSound();

	//乱数ランダムにするアレ
	srand((unsigned)time(NULL)); 

	//keyboard操作生成
	CInputKeyborad *pInputKeyborad;
	pInputKeyborad = CManager::GetInputKeyborad();

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		m_nCT[nCnt]++;
		m_nTime[nCnt] = 40 + rand() % 60;
	}
	m_nCT[4]++;

	//エネミークリエイトするpos
	float fCreaterPosY1, fCreaterPosY2, fCreaterPosY3;
	//乱数生成
	fCreaterPosY1 = 50 + rand() % 690;
	fCreaterPosY2 = 50 + rand() % 690;
	fCreaterPosY3 = 50 + rand() % 690;

	//敵生成のパターン変えるやつ
	int nNumber;
	//乱数生成2
	nNumber = 1 + rand() % 3;

	//とりあえずエンターでリザルト行く
	//if (pInputKeyborad->GetPress(DIK_RETURN) == true)
	//{
	//	CFade::SetFade(CManager::MODE_RESULT);
	//}

	//Qか←押したら
	if (pInputKeyborad->GetTrigger(DIK_Q) || pInputKeyborad->GetTrigger(DIK_LEFT))
	{//選択中の弾の表示切り替え
		pSound->PlaySound(pSound->SOUND_SELECT_SE);
		m_apScene2D[m_nSelect]->SetColor(DEFAULT_COL);
		if (m_nSelect <= 0)
		{
			m_nSelect = SELECT_NORMAL;
		}
		else
		{
			m_nSelect--;
		}
		m_apScene2D[m_nSelect]->SetColor(SELECT_COL);
	}

	//Eか→押したら
	if (pInputKeyborad->GetTrigger(DIK_E) || pInputKeyborad->GetTrigger(DIK_RIGHT))
	{//選択中の弾の表示切り替え
		pSound->PlaySound(pSound->SOUND_SELECT_SE);
		m_apScene2D[m_nSelect]->SetColor(DEFAULT_COL);
		if (m_nSelect >= SELECT_MAX - 1)
		{
			m_nSelect = SELECT_MAX - 1;
		}
		else
		{
			m_nSelect++;
		}
		m_apScene2D[m_nSelect]->SetColor(SELECT_COL);
	}

#if 1
	if (m_nCT[0] > 50)
	{
		switch (nNumber)
		{
		case 1:
			if (m_nCT[1] < m_nTime[0])
			{
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(1280.0f, fCreaterPosY1, 0.0f), D3DXVECTOR3(ENEMY_WIDTH, ENEMY_WIDTH, 0.0f));
			m_nCT[1] = 0;
			}
			if (m_nCT[2] < m_nTime[1])
			{
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(1280.0f, fCreaterPosY2, 0.0f), D3DXVECTOR3(ENEMY_WIDTH, ENEMY_WIDTH, 0.0f));
			m_nCT[2] = 0;
			}
			if (m_nCT[3] < m_nTime[2])
			{
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(1280.0f, fCreaterPosY3, 0.0f), D3DXVECTOR3(ENEMY_WIDTH, ENEMY_WIDTH, 0.0f));
			m_nCT[3] = 0;
			}

			m_nCT[0] = 0;
			break;
		case 2:
			if (m_nCT[1] < m_nTime[0])
			{
				m_pEnemy = CEnemy::Create(D3DXVECTOR3(1280.0f, fCreaterPosY1, 0.0f), D3DXVECTOR3(ENEMY_WIDTH, ENEMY_WIDTH, 0.0f));
				m_nCT[1] = 0;
			}
			if (m_nCT[2] < m_nTime[1])
			{
			m_pEnemy_h = CEnemy_h::Create(D3DXVECTOR3(1280.0f, fCreaterPosY2, 0.0f), D3DXVECTOR3(ENEMY_WIDTH, ENEMY_WIDTH, 0.0f));
			m_nCT[2] = 0;
			}
			if (m_nCT[3] < m_nTime[2])
			{
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(1280.0f, fCreaterPosY3, 0.0f), D3DXVECTOR3(ENEMY_WIDTH, ENEMY_WIDTH, 0.0f));
			m_nCT[3] = 0;
			}

			m_nCT[0] = 0;
			break;
		case 3:
			if (m_nCT[1] < m_nTime[0])
			{
				m_pEnemy_h = CEnemy_h::Create(D3DXVECTOR3(1280.0f, fCreaterPosY1, 0.0f), D3DXVECTOR3(ENEMY_WIDTH, ENEMY_WIDTH, 0.0f));
				m_nCT[1] = 0;
			}
			if (m_nCT[2] < m_nTime[1])
			{
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(1280.0f, fCreaterPosY2, 0.0f), D3DXVECTOR3(ENEMY_WIDTH, ENEMY_WIDTH, 0.0f));
			m_nCT[2] = 0;
			}
			if (m_nCT[3] < m_nTime[2])
			{
			m_pEnemy_h = CEnemy_h::Create(D3DXVECTOR3(1280.0f, fCreaterPosY3, 0.0f), D3DXVECTOR3(ENEMY_WIDTH, ENEMY_WIDTH, 0.0f));
			m_nCT[3] = 0;
			}

			m_nCT[0] = 0;
			break;
		default:
			break;
		}
	}
#endif

}

void CGame::Draw(void)
{

}

CScore *CGame::GetScore(void)
{
	return m_pScore;
}

//CBg *CGame::GetBg(void)
//{
//
//}

CPlayer *CGame::GetPlayer(void)
{
	return m_pPlayer;
}