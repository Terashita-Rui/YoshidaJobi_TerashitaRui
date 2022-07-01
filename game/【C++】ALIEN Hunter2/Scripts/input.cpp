#include"input.h"


LPDIRECTINPUT8 CInput::m_pInput = NULL;

CInput::CInput()
{
	m_pDevice = NULL;
}

CInput::~CInput()
{

}

HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr = S_FALSE;
	if (m_pInput == NULL)
	{
		hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL);
	}

	return hr;
}

void CInput::Uninit(void)
{
	// 入力デバイス(キーボードの開放)
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;

	}

	// DirectInputオブジェクトの開放
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

void CInput::Update(void)
{

}

CInputKeyborad::CInputKeyborad()
{
	//キー情報のクリア
	memset(&m_aKeyState[0], 0, sizeof(m_aKeyState));
	memset(&m_aKeyStateRelease[0], 0, sizeof(m_aKeyStateRelease));
	memset(&m_aKeyStateTrigger[0], 0, sizeof(m_aKeyStateTrigger));
}

CInputKeyborad::~CInputKeyborad()
{

}

HRESULT CInputKeyborad::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	// DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}

	// 入力デバイス(キーボード)の生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	// データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//デバイスへのアクセス権を獲得(入力制御開始)
	m_pDevice->Acquire();

	return S_OK;
}

void CInputKeyborad::Uninit(void)
{
	CInput::Uninit();
}

void CInputKeyborad::Update(void)
{
	BYTE aKeyState[MAX_KEY];
	int nCntKey;
	// キーボードの入力情報

	// 入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < 256; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey])&aKeyState[nCntKey];
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & m_aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey]; //キーボードの入力情報保存
		}
	}

	else
	{
		m_pDevice->Acquire(); // キーボードへのアクセス権を獲得
	}
}

bool CInputKeyborad::GetAnyKey(void)
{
	int nCntKey;
	for (nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
	{
		if ((m_aKeyStateTrigger[nCntKey] & 0x80) != 0 && (m_aKeyStateRelease[nCntKey] & 0x80) == 0)
		{
			return true;
		}
	}
	return false;
}

bool CInputKeyborad::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

bool CInputKeyborad::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}