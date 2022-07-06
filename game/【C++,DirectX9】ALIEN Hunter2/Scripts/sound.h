//�e�T�E���h
//Auther:��������


#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

class CSound
{
public:
	CSound();
	~CSound();

	// �T�E���h�t�@�C��
	typedef enum
	{
		SOUND_GAME_BGM = 0,		//�Q�[��BGM
		SOUND_RESULT_BGM,		//���U���gBGM
		SOUND_TITLE_BGM,		//�^�C�g��BGM
		SOUND_EXPLOSION_SE,			//������
		SOUND_SELECT_SE,			//�I�����I��
		SOUND_SELECT_DECISION_SE,		//�I��������
		SOUND_SHOOT_SE, //�ˌ�
		SOUND_MAX,
	} SOUND;

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND label);
	void StopSound(SOUND label);
	void Stop(void);
private:
	//�p�����[�^�\����
	typedef struct
	{
		char *filename;		// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} PARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_MAX] = {};	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

	static PARAM	m_aParam[SOUND_MAX];
};

#endif