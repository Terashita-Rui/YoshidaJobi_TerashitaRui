#include"main.h"
#include"scene2D.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define PLAYER_WIDTH (110.0f / 2)
#define PLAYER_HIGHT (100.0f / 2)

class CBullet;
class CBullet_p;
class CBullet_h;

class CPlayer : public CScene2D
{
public:
	CPlayer(OBJTYPE nPriority);
	~CPlayer();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャ
	D3DXVECTOR3 m_pos; //位置
	D3DXVECTOR3	m_size;					// サイズ
	D3DXVECTOR3 m_move;					//移動速度
	int m_nCT;							//弾クリエイトするクールタイム(bullet側でやるべき？)
	int m_nButtetNum;					//どの弾撃つかの管理に使う
	static CBullet *m_pBullet;
	static CBullet_p *m_pBullet_p;
	static CBullet_h *m_pBullet_h;
};