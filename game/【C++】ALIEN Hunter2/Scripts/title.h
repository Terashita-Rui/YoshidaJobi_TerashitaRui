//�^�C�g���V�[��
//Auther:��������

#ifndef _TITLE_H_
#define _TITLE_H_

#include"main.h"
#include"scene.h"

#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

#define SELECT_COL D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) //�I�𒆂̐F(��)
#define DEFAULT_COL D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f) //�f�t�H�̐F(�����ۂ���)

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
		SELECT_GAME, //�Q�[���{�^��
		SELECT_OP, //��������{�^��
		SELECT_MAX
	}SELECT;

	CScene2D *m_apScene2D[SELECT_MAX];	//�I��
	CScene2D *m_pOp; //����������
	bool m_bOP_button; //���������ʂɍs���{�^��
	bool m_bGame_button; //�Q�[���@�ۃ{�^��
	int m_nSelect; //���̑I����
};
#endif // !_TITLE_H_
