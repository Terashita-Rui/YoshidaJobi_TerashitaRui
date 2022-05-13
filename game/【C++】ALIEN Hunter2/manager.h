#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"

class CRenderer;
class CInputKeyborad;
class CPlayer;
class CEnemy;
class CScore;
class CNumber;
class CSound;
class CTitle;
class CGame;
class CResult;

class CManager
{
public:
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX
	} MODE;

	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CRenderer *GetRenderer(void);
	static CInputKeyborad *GetInputKeyborad(void);
	static CPlayer *GetPlayer(void);
	static CEnemy *GetEnemy(void);
	static void SetMode(MODE mode);
	static MODE GetMode(void);
	static CSound *GetSound(void);

private:
	static CRenderer *m_pRenderer;
	static CInputKeyborad *m_pInputKeyborad;

	static CPlayer *m_pPlayer;
	static CEnemy *m_pEnemy;
	static CScore *m_pScore;
	static CNumber *m_pNumber;
	static CSound *m_pSound;

	static CTitle *m_pTitle;
	static CGame *m_pGame;
	static CResult *m_pResult;
	static MODE m_mode;

};

#endif