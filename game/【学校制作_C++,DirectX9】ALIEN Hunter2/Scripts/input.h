//�L�[�{�[�h����
//Auther:��������

#ifndef _INPUT_H_
#define _INPUT_H_

#include"main.h"

#define MAX_KEY 256 //�L�[�̍ő吔

class CInput
{
public:
	CInput();
	virtual ~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:
	//�h���N���X�Ŏg���Ƃ킩�肫���Ă�Ȃ�protectd�ɂ��Ă������H
	LPDIRECTINPUTDEVICE8 m_pDevice; 
	static LPDIRECTINPUT8 m_pInput; 
};

class CInputKeyborad : public CInput
{
public:
	CInputKeyborad();
	~CInputKeyborad();
	 HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	 void Uninit(void);
	 void Update(void);
	 bool GetAnyKey(void);
	 bool GetPress(int nKey);
	 bool GetTrigger(int nkey);
	 bool GetRelease(int nKey);
	 bool GetKey(int nKey);


private:
	BYTE m_aKeyState[MAX_KEY]; //�L�[�{�[�h�̓��͏��
	BYTE m_aKeyStateTrigger[MAX_KEY]; //���Ɠ���
	BYTE m_aKeyStateRelease[MAX_KEY]; //���Ɠ���

};
#endif // ! _INPUT_H_
