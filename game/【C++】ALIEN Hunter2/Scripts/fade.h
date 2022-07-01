//��ʑJ�ڎ��̃t�F�[�h
//Auther:��������


#ifndef _FADE_H_
#define _FADE_H_
#include "main.h"
#include "manager.h"

class CFade
{
public:
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX
	} FADE;

	CFade();
	~CFade();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetFade(CManager::MODE modenext);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL; //���_�o�b�t�@�ւ̃|�C���^
	static CManager::MODE m_mode; //���[�h�擾
	D3DXCOLOR m_FadeColor; //�t�F�[�h���̐F
	static FADE m_fade;

};
#endif