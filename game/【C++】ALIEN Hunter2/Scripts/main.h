//���C��
//Auther:��������

#ifndef _MAIN_H
#define _MAIN_H

#define DIRECTINPUT_VERSION 0x0800 //�x���΍�
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "d3dx9.h"	//�`��ɕK�v
#include"dinput.h" //DirectInput�֘A
#include"xaudio2.h" //XAudio2�֘A

//*****************************************************************************
// ���C�u�����t�@�C���̃����N
//*****************************************************************************
#pragma comment(lib,"d3d9.lib") //�`��ɕK�v
#pragma comment(lib,"d3dx9.lib") //[d3d9,lid]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib") //DirectX�R���|�l�[�g�g�p�ɕK�v
#pragma comment (lib, "winmm.lib")
#pragma comment(lib,"dinput8.lib") //���͏����ɕK�v

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int GetFPS(void);
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

#endif