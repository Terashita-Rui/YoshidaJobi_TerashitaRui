//ホーミング敵
//Auther:寺下琉生


#ifndef _ENEMY_HOMING_H_
#define _ENEMY_HOMING_H_

#include"scene2D.h"

class CEnemy_h : public CScene2D
{
public:
	CEnemy_h(OBJTYPE nPriority = OBJTYPE_NONE);
	~CEnemy_h();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Collision(void);

	static CEnemy_h *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture; //テクスチャのポインタ
	D3DXVECTOR3 m_pos; //位置情報
	D3DXVECTOR3 m_move; //移動速度１(使わないかも)
	float m_fSpeed; //移動速度２
	D3DXVECTOR3	m_size;					// サイズ
	D3DXVECTOR3 m_PlayerPos; //プレイヤーのpos
	D3DXVECTOR3 m_Vector; //弾->敵の方向ベクトル
	float m_fLenght; //直線距離
	float m_fAngle; //向き
	bool m_bUse; //使ったかどうか
};
#endif