//シーン2D
//Auther:寺下琉生

#ifndef _SCENE2D_H
#define _SCENE2D_H

#include"main.h"
#include"scene.h"

#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

class CInput;

typedef struct
{
	D3DXVECTOR3 pos; //頂点座標
	float rhw; //1.0fで固定
	D3DCOLOR col; //頂点カラー
	D3DXVECTOR2 tex; //テクスチャ座標
} VERTEX_2D;

class CScene2D : public CScene
{
public:
	typedef enum
	{
		//タイトルに使うテクスチャ
		TEXTYPE_TITLE_BG, //背景
		TEXTYPE_TITLE_LOGO, //タイトルロゴ
		TEXTYPE_TITLE_GAMEBUTTON, //ゲームに遷移するボタン
		TEXTYPE_TITLE_OP_BUTTON, //操作説明見るボタン
		TEXTYPE_TITLE_OP, //操作説明ボタン

	    //ゲームに使うテクスチャ
		TEXTYPE_GAME_NORMALBULLET,		//ノーマル弾選択
		TEXTYPE_GAME_HOMINGBULLET,		//ホーミング弾選択
		TEXTYPE_GAME_PENETRETIONBULLET, //貫通弾選択

		//リザルトに使うテクスチャ
		TEXTYPE_RESULT_BG, //リザルト背景
		TEXTYPE_MAX
	} TEX_TYPE; //テクスチャの種類

	CScene2D(OBJTYPE nPriority = OBJTYPE_NONE);
	~CScene2D();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	 void Uninit(void);
	 void Update(void);
	 void Draw(void);
	 void SetPos(D3DXVECTOR3 pos);
	 D3DXVECTOR3 GetPos(void);
	 void SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	 bool SetTex(int nPatternAnim);
	 D3DXVECTOR3 GetSize(void);
	 void SetSize(D3DXVECTOR3 size);
	 void SetColor(D3DXCOLOR col);
	 void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	 static CScene2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int ntype);
	 static HRESULT Load(void);
	 static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9		m_apTexture[TEXTYPE_MAX];	//y見込むテクスチャ
	LPDIRECT3DTEXTURE9		m_pTexture;	//テクスチャ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;	//ポリゴンの位置
	D3DXVECTOR3				m_size; //大きさ
	D3DXCOLOR m_col;	//色
};
#endif