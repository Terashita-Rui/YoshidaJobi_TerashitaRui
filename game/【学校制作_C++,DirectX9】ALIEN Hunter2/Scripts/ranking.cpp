#include "ranking.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "score.h"
#include "game.h"

CScore *CRanking::m_pScore = NULL;

CRanking::CRanking(OBJTYPE nPriority) :CScene(nPriority)
{

}

CRanking::~CRanking()
{
	FILE *pFile;
	pFile = fopen("ranking.txt", "w");
	int nCntNum = 0;

	if (pFile != NULL)
	{
		for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
		{
			//書き込み
			fprintf(pFile, "%d\n", m_nRankingData[nCnt]);
		}
	}
	fclose(pFile);
}

HRESULT CRanking::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	SetObjType(OBJTYPE_UI);

	FILE *pFile;
	pFile = fopen("ranking.txt", "r");
	int nCntNum = 0;

	if (pFile != NULL)
	{
		for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
		{
			//ランキング取得
			fscanf(pFile, "%d", &m_nRankingData[nCnt]);
		}
	}
	fclose(pFile);

	//取ったスコア取得
	m_nNewScore = m_pScore->GetScore();
	int nSaveData = 0;
	int nSaveData2 = 0;

	for (int nCnt1 = 0; nCnt1 < MAX_RANKING; nCnt1++)
	{
		if (m_nNewScore > m_nRankingData[nCnt1])
		{
			nSaveData = m_nRankingData[nCnt1];
			//入れたいとこを開ける処理
			for (int nCnt2 = nCnt1; nCnt2 < MAX_RANKING - 1; nCnt2++)
			{
				//数値を保存２
				nSaveData2 = m_nRankingData[nCnt2 + 1];
				//前に保存した数値を入れる
				m_nRankingData[nCnt2 + 1] = nSaveData;
				//上書き
				nSaveData = nSaveData2;
			}
			//開けたところに数値を入れる
			m_nRankingData[nCnt1] = m_nNewScore;
			break;
		}
	}

	return S_OK;
}

void CRanking::Uninit(void)
{
	Release();
}

void CRanking::Update(void)
{

}

void CRanking::Draw(void)
{

}

CRanking *CRanking::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CRanking *pRanking;
	pRanking = new CRanking(OBJTYPE_UI);
	if (pRanking != NULL)
	{

		pRanking->Init(pos,size);
	}

	return pRanking;
}