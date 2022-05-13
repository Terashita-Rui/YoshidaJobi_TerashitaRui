#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

class CSound
{
public:
	CSound();
	~CSound();

	// サウンドファイル
	typedef enum
	{
		SOUND_GAME_BGM = 0,		//ゲームBGM
		SOUND_RESULT_BGM,		//リザルトBGM
		SOUND_TITLE_BGM,		//タイトルBGM
		SOUND_EXPLOSION_SE,			//爆発音
		SOUND_SELECT_SE,			//選択肢選択
		SOUND_SELECT_DECISION_SE,		//選択肢決定
		SOUND_SHOOT_SE, //射撃
		SOUND_MAX,
	} SOUND;

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND label);
	void StopSound(SOUND label);
	void Stop(void);
private:
	//パラメータ構造体
	typedef struct
	{
		char *filename;		// ファイル名
		int nCntLoop;		// ループカウント
	} PARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_MAX] = {};	// ソースボイス
	BYTE *m_apDataAudio[SOUND_MAX] = {};					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_MAX] = {};					// オーディオデータサイズ

	static PARAM	m_aParam[SOUND_MAX];
};

#endif