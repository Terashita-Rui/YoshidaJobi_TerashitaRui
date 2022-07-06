//爆発アニメーション
//Auther:寺下琉生


#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include"scene2D.h"

#define EXPLOSION_WIDTH 10.0f
#define EXPLOSION_HIGHT 10.0f

class CExplosion : public CScene2D
{
public:
	CExplosion(int nPriority = PRIORITY_EFFECT);
	~CExplosion();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static HRESULT Load(void);
	static void Unload(void);
	static CExplosion *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3	m_size;					// サイズ
	int m_nCountAnim; //アニメーションカウンター
	int m_nPatternAnim; //パターンナンバー
};

#endif