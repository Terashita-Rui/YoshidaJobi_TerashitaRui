//�V�[��2D
//Auther:��������

#ifndef _SCENE2D_H
#define _SCENE2D_H

#include"main.h"
#include"scene.h"

#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

class CInput;

typedef struct
{
	D3DXVECTOR3 pos; //���_���W
	float rhw; //1.0f�ŌŒ�
	D3DCOLOR col; //���_�J���[
	D3DXVECTOR2 tex; //�e�N�X�`�����W
} VERTEX_2D;

class CScene2D : public CScene
{
public:
	typedef enum
	{
		//�^�C�g���Ɏg���e�N�X�`��
		TEXTYPE_TITLE_BG, //�w�i
		TEXTYPE_TITLE_LOGO, //�^�C�g�����S
		TEXTYPE_TITLE_GAMEBUTTON, //�Q�[���ɑJ�ڂ���{�^��
		TEXTYPE_TITLE_OP_BUTTON, //�����������{�^��
		TEXTYPE_TITLE_OP, //��������{�^��

	    //�Q�[���Ɏg���e�N�X�`��
		TEXTYPE_GAME_NORMALBULLET,		//�m�[�}���e�I��
		TEXTYPE_GAME_HOMINGBULLET,		//�z�[�~���O�e�I��
		TEXTYPE_GAME_PENETRETIONBULLET, //�ђʒe�I��

		//���U���g�Ɏg���e�N�X�`��
		TEXTYPE_RESULT_BG, //���U���g�w�i
		TEXTYPE_MAX
	} TEX_TYPE; //�e�N�X�`���̎��

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
	static LPDIRECT3DTEXTURE9		m_apTexture[TEXTYPE_MAX];	//y�����ރe�N�X�`��
	LPDIRECT3DTEXTURE9		m_pTexture;	//�e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;	//�|���S���̈ʒu
	D3DXVECTOR3				m_size; //�傫��
	D3DXCOLOR m_col;	//�F
};
#endif