//タイトルシーン
//Auther:寺下琉生

#ifndef _TITLE_H_
#define _TITLE_H_

#include"main.h"
#include"scene.h"

#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

#define SELECT_COL D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) //選択中の色(白)
#define DEFAULT_COL D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f) //デフォの色(黒っぽい方)

class CScene2D;

class CTitle : public CScene
{
public:
	CTitle(OBJTYPE nPriority = OBJTYPE_NONE);
	~CTitle();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);

private:
	typedef enum
	{
		SELECT_GAME, //ゲームボタン
		SELECT_OP, //操作説明ボタン
		SELECT_MAX
	}SELECT;

	CScene2D *m_apScene2D[SELECT_MAX];	//選択中
	CScene2D *m_pOp; //操作説明画面
	bool m_bOP_button; //操作説明画面に行くボタン
	bool m_bGame_button; //ゲー無繊維ボタン
	int m_nSelect; //今の選択肢
};
#endif // !_TITLE_H_
