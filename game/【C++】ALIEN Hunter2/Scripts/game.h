//ゲームシーン
//Auther:寺下琉生

#ifndef _GAME_H_
#define _GAME_H_

#include"main.h"
#include"scene.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

class CScore;
class CPlayer;
class CNumber;
class CEnemy;
class CEnemy_h;
class CScene2D;

#define SELECT_COL D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) //選択中の色(白)
#define DEFAULT_COL D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f) //デフォの色(黒っぽい方)

//選択中の弾表示ポリゴンのposとsize
#define SELECT_BULLET_POS_X 200.0f
#define SELECT_BULLET_POS_Y 40.0f
#define SELECT_BULLET_SIZE_X 150.0f
#define SELECT_BULLET_SIZE_Y 30.0f

class CGame : public CScene
{
public:
	CGame(OBJTYPE nPriority = OBJTYPE_NONE);;
	~CGame();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScore *GetScore(void);

	//static CBg *GetBg(void);
	static CPlayer *GetPlayer(void);

private:
	typedef enum
	{
		SELECT_NORMAL,		//ノーマル弾
		SELECT_HOMING,		//ホーミング弾
		SELECT_PENETRETION, //貫通弾
		SELECT_MAX
	}SELECTBULLET;

	CScene2D *m_apScene2D[SELECT_MAX];	//選択中の弾
	int m_nCT[4]; //敵生成を始めるクールタイム
	int m_nTime[3]; //CT加算

	int m_nSelect; //今選択中の弾

	//static CBg *m_pBg;
	static CPlayer *m_pPlayer;
	static CScore *m_pScore;
	static CNumber *m_pNumber;
	static CEnemy *m_pEnemy;
	static CEnemy_h *m_pEnemy_h;

};

#endif
