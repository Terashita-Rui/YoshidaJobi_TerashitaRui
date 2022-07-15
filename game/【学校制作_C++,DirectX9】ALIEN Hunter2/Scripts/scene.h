//�e�V�[��
//Auther:��������


#ifndef _SCENE_H
#define _SCENE_H

#include"main.h"
#define MAX_POLYGON 256

class CScene
{
public:
	typedef enum
	{
		PRIORITY_BG = 0,	//�w�i
		PRIORITY_EFFECT,	//�G�t�F�N�g
		PRIORITY_BULLET,	//�e
		PRIORITY_ENEMY,		//�G
		PRIORITY_PLAYER,	//�v���C���[
		PRIORITY_UI,		//UI
		PRIORITY_MAX
	} PRIORITY;

	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,		//�v���C���[
		OBJTYPE_BULLET,		//�e
		OBJTYPE_ENEMY, //�G
		OBJTYPE_EXPLOSION,	//����
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
	int m_nID; //�i�[��̔ԍ�
	int m_nPriority; //�D�揇��
	OBJTYPE m_objType; //�I�u�W�F�N�g�̎��
	D3DXVECTOR3 m_pos;						//�|���S���̈ʒu
	D3DXVECTOR3 m_size;
};

#endif