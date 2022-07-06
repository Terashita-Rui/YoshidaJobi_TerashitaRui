//�Q�[���V�[��
//Auther:��������

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

#define SELECT_COL D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) //�I�𒆂̐F(��)
#define DEFAULT_COL D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f) //�f�t�H�̐F(�����ۂ���)

//�I�𒆂̒e�\���|���S����pos��size
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
		SELECT_NORMAL,		//�m�[�}���e
		SELECT_HOMING,		//�z�[�~���O�e
		SELECT_PENETRETION, //�ђʒe
		SELECT_MAX
	}SELECTBULLET;

	CScene2D *m_apScene2D[SELECT_MAX];	//�I�𒆂̒e
	int m_nCT[4]; //�G�������n�߂�N�[���^�C��
	int m_nTime[3]; //CT���Z

	int m_nSelect; //���I�𒆂̒e

	//static CBg *m_pBg;
	static CPlayer *m_pPlayer;
	static CScore *m_pScore;
	static CNumber *m_pNumber;
	static CEnemy *m_pEnemy;
	static CEnemy_h *m_pEnemy_h;

};

#endif
