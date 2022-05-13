#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"
#include "scene.h"

#define MAX_SCORE 8

class CNumber;

class CScore :public CScene
{
public:
	CScore(OBJTYPE nPriority = OBJTYPE_NONE);
	~CScore();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void AddScore(int nValue);
	int CScore::GetScore(void) { return m_nScore; }
	
	static CScore *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
	CNumber *m_apNumber[MAX_SCORE];

	int m_nScore;
};
#endif
