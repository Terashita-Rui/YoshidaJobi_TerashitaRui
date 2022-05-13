#ifndef _MAIN_H
#define _MAIN_H

#define DIRECTINPUT_VERSION 0x0800 //警告対策
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "d3dx9.h"	//描画に必要
#include"dinput.h" //DirectInput関連
#include"xaudio2.h" //XAudio2関連

//*****************************************************************************
// ライブラリファイルのリンク
//*****************************************************************************
#pragma comment(lib,"d3d9.lib") //描画に必要
#pragma comment(lib,"d3dx9.lib") //[d3d9,lid]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib") //DirectXコンポネート使用に必要
#pragma comment (lib, "winmm.lib")
#pragma comment(lib,"dinput8.lib") //入力処理に必要

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int GetFPS(void);
//*****************************************************************************
// 構造体定義
//*****************************************************************************

#endif