#ifndef _RESULT_H_
#define _RESULT_H_

#include"main.h"
#include"scene.h"
#include"score.h"

#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define MAX_RANKING 5

class CRanking;
class CScore;

class CResult : public CScene
{
public:
	CResult(OBJTYPE nPriority = OBJTYPE_NONE);;
	~CResult();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	LPDIRECT3DTEXTURE9 *m_pTexture;
	int	m_nRankingData[MAX_RANKING];
	CScore *m_Score[MAX_RANKING];

	CRanking *m_pRanking;

};
#endif // !_RESULT_H_
