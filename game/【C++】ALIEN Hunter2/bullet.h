//普通の弾

#ifndef _BULLET_H_
#define _BULLET_H_

#include"main.h"
#include"scene2D.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

class CEnemy;

//弾の大きさ
#define BULLET_WIDTH 15.0f
#define BULLET_HEIGHT 10.0f
#define BULLET_KINDS 3 //弾の種類

class CBullet : public CScene2D
{
public:
	CBullet(OBJTYPE nPriority = OBJTYPE_NONE);
	~CBullet();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Collision(void);

	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static HRESULT Load(void);
	static void Unload(void);

protected:
	D3DXVECTOR3 m_pos; //位置情報
	D3DXVECTOR3 m_move; //移動速度１(使わないかも)
	float m_fSpeed; //移動速度２
	static LPDIRECT3DTEXTURE9 m_pTexture; //テクスチャのポインタ
	D3DXVECTOR3	m_size;					// サイズ
	D3DXVECTOR3 m_EnemyPos; //敵のpos
	D3DXVECTOR3 m_Vector; //弾->敵の方向ベクトル
	float m_fLenght; //直線距離
	float m_fAngle; //向き
	bool m_bUse; //使ったかどうか
private:
};

#endif