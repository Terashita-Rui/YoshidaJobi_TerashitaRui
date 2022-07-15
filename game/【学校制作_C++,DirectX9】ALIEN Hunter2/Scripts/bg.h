#ifndef _BG_H_
#define _BG_H_

#include "main.h"
#include "scene.h"

#define MAX_BG (3)

class CScene2D;

class CBg : public CScene
{
public:
	typedef enum
	{
		TYPE_001,
		TYPE_002,
		TYPE_003,
		TYPE_MAX
	} TYPE;	//ポリゴンのテクスチャの種類

	CBg();	//デフォルトコンストラクタ
	~CBg();	//デストラクタ
	static CBg* Create(void);	//生成処理
	static HRESULT Load(void);		//テクスチャの読み込み
	static void Unload(void);		//テクスチャの解放
	HRESULT Init(void);	//初期化処理
	void Uninit(void);	//終了処理
	void Update(void);	//更新処理
	void Draw(void);	//描画処理

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];	//テクスチャへのポインタ
	CScene2D* m_apScene2D[MAX_BG];	//2Dポリゴン
	float m_aTopTexV[MAX_BG];	//テクスチャ座標のVの上
};

#endif // !_BG_H_