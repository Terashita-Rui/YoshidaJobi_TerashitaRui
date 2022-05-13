#include "score.h"
#include "number.h"


CScore::CScore(OBJTYPE nPriority) : CScene(nPriority)
{
	memset(&m_apNumber[0], 0, sizeof(m_apNumber));
}

CScore::~CScore()
{

}

HRESULT CScore::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_size = size;
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		m_apNumber[nCntScore] = CNumber::Create(D3DXVECTOR3(pos.x + m_size.x * nCntScore, pos.y, 0.0f), m_size.x, m_size.y);
	}
	m_nScore = 0;

	return S_OK;
}

void CScore::Uninit(void)
{
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		if (m_apNumber[nCntScore] != NULL)
		{
			m_apNumber[nCntScore]->Uninit();
			delete m_apNumber[nCntScore];
			m_apNumber[nCntScore] = NULL;
		}
	}
	Release();
}

void CScore::Update(void)
{

	m_apNumber[0]->SetNumber(m_nScore % 100000000 / 10000000);
	m_apNumber[1]->SetNumber(m_nScore % 10000000 / 1000000);
	m_apNumber[2]->SetNumber(m_nScore % 1000000 / 100000);
	m_apNumber[3]->SetNumber(m_nScore % 100000 / 10000);
	m_apNumber[4]->SetNumber(m_nScore % 10000 / 1000);
	m_apNumber[5]->SetNumber(m_nScore % 1000 / 100);
	m_apNumber[6]->SetNumber(m_nScore % 100 / 10);
	m_apNumber[7]->SetNumber(m_nScore % 10 / 1);
}

void CScore::Draw(void)
{
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		m_apNumber[nCntScore]->Draw();
	}
}

void CScore::AddScore(int nValue)
{
	m_nScore += nValue;
}

CScore *CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScore *pScore = NULL;
	pScore = new CScore;

	if (pScore != NULL)
	{
		pScore->Init(pos, size);
		pScore->SetObjType(CScene::OBJTYPE_UI);
	}
	return pScore;
}