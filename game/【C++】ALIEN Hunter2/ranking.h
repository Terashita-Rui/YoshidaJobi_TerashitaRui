#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"
#include "scene.h"
#define MAX_RANKING 5
//ランキングファイル
#define RANKING_TEXT_NAME "data/Text/ranking.txt"

class CScore;

class CRanking : public CScene
{
public:
	CRanking(OBJTYPE nPriority = OBJTYPE_NONE);	
	~CRanking();	
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CRanking *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
	int m_nRankingData[MAX_RANKING]; //テキストに保存してあるスコア
	int	m_nNewScore; //今取ったスコア

	static CScore *m_pScore; //scoreのポインタ
};

#endif // !_RANKING_H_