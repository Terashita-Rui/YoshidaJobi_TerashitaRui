#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"
#include "scene.h"
#include "manager.h"

class CNumber
{
public:
	CNumber();
	~CNumber();
	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void CNumber::SetNumber(int nNumber);
	static HRESULT Load(void);
	static void Unload(void);
	static CNumber *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9   m_pVtxBuffer;
	D3DXVECTOR3				  m_pos;	        //ポリゴンの位置
	D3DXVECTOR2			      m_size;		    //ポリゴンのサイズ
	float m_fTexU;
	float m_fTexV;
};

#endif