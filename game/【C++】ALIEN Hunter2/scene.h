#ifndef _SCENE_H
#define _SCENE_H

#include"main.h"
#define MAX_POLYGON 256

class CScene
{
public:
	typedef enum
	{
		PRIORITY_BG = 0,	//背景
		PRIORITY_EFFECT,	//エフェクト
		PRIORITY_BULLET,	//弾
		PRIORITY_ENEMY,		//敵
		PRIORITY_PLAYER,	//プレイヤー
		PRIORITY_UI,		//UI
		PRIORITY_MAX
	} PRIORITY;

	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,		//プレイヤー
		OBJTYPE_BULLET,		//弾
		OBJTYPE_ENEMY, //敵
		OBJTYPE_EXPLOSION,	//爆発
		OBJTYPE_UI, //UI
		OBJTYPE_MAX,
	} OBJTYPE;

	CScene(OBJTYPE nPriority);
	~CScene();
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	void SetObjType(OBJTYPE objType);
	OBJTYPE GetObjType(void);
	static CScene *GetScene(int nPriority,int nScene);
	void SetPos(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos(void);
	void SetSize(D3DXVECTOR3 size);
	D3DXVECTOR3 GetSize(void);

	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

protected:
	void Release(void);

private:
	static CScene *m_apScene[OBJTYPE_MAX][MAX_POLYGON];
	static int m_NumAll;
	int m_nID; //格納先の番号
	int m_nPriority; //優先順位
	OBJTYPE m_objType; //オブジェクトの種類
	D3DXVECTOR3 m_pos;						//ポリゴンの位置
	D3DXVECTOR3 m_size;
};

#endif