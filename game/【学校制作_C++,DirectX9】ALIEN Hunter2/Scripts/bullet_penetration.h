//貫通弾
//Auther:寺下琉生

#ifndef _BULLET_PENETRATION_H_
#define _BULLET_PENETRATION_H_

#include"main.h"
#include"scene2D.h"
#include"bullet.h"

//弾の大きさ
#define BULLET_WIDTH 15.0f
#define BULLET_HEIGHT 10.0f

//「CBullet_penetration」っていちいち打つの面倒だから「CBullet_p」にした
class CBullet_p : public CBullet
{
public:
	CBullet_p(OBJTYPE nPriority = OBJTYPE_NONE);
	~CBullet_p();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Collision(void);

	static CBullet_p *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture; //テクスチャのポインタ
};

#endif#pragma once
