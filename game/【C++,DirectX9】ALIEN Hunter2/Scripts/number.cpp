#include "number.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"

#define TEXTURE_NAME "data/Texture/number000.png"

LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;

CNumber::CNumber()
{

}

CNumber::~CNumber()
{

}

HRESULT CNumber::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffer,
		NULL);

	VERTEX_2D *pVtx;  //頂点情報へのポインタ

					  //頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	m_pos = pos;
	m_size = D3DXVECTOR2(fWidth / 2, fHeight / 2);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuffer->Unlock();

	return S_OK;

}

void CNumber::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuffer != NULL)
	{
		m_pVtxBuffer->Release();
		m_pVtxBuffer = NULL;
	}
}

void CNumber::Update(void)
{

}

void CNumber::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ

	pDevice = CManager::GetRenderer()->GetDevice();  //デバイスを取得する

	pDevice->SetStreamSource(0, m_pVtxBuffer, 0, sizeof(VERTEX_2D));  //頂点バッファをデバイスのデータストリームに設定

	pDevice->SetFVF(FVF_VERTEX_2D); //頂点フォーマットの設定

									//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}

void CNumber::SetNumber(int nNumber)
{
	VERTEX_2D *pVtx;  //頂点情報へのポインタ

					  //頂点座標をロック
	m_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標を更新
	pVtx[0].tex = D3DXVECTOR2((nNumber * 0.1f) + 0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((nNumber * 0.1f) + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((nNumber * 0.1f) + 0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((nNumber * 0.1f) + 0.1f, 1.0f);

	//頂点バッファをアンロック
	m_pVtxBuffer->Unlock();
}

HRESULT CNumber::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME,
		&m_pTexture);

	return S_OK;
}

void CNumber::Unload(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

}

CNumber *CNumber::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CNumber *pNumber;
	pNumber = new CNumber;
	if (pNumber != NULL)
	{
		pNumber->Init(pos, fWidth, fHeight);
	}

	return pNumber;
}