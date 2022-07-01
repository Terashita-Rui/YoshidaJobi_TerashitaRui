#include"scene2D.h"
#include"renderer.h"
#include"manager.h"
#include"input.h"

//テクスチャ
#define TEXTURE_TITLE_BG "data/Texture/title/title.png"											//背景
#define TEXTURE_TITLE_LOGO "data/Texture/title/title_logo.png"									//タイトルロゴ
#define TEXTURE_TITLE_GAME "data/Texture/title/start_button.png"								//ゲームに遷移するボタン
#define TEXTURE_TITLE_OP_BUTTON "data/Texture/title/operation_button2.png"						//操作説明に移動するボタン
#define TEXTURE_TITLE_OP "data/Texture/title/operation.png"										//操作説明画面

#define TEXTURE_GAME_SELECTBULLET_NORMAL "data/Texture/game/select_bullet_normal.png"			//ノーマル弾選択
#define TEXTURE_GAME_SELECTBULLET_HOMING "data/Texture/game/select_bullet_homing.png"			//ホーミング弾選択
#define TEXTURE_GAME_SELECTBULLET_PENETRETION "data/Texture/game/select_bullet_penetration.png" //貫通弾選択

#define TEXTURE_RESULT_BG "data/Texture/result/rankingBG.png"									//リザルト背景

LPDIRECT3DTEXTURE9 CScene2D::m_apTexture[TEXTYPE_MAX] = {};

CScene2D::CScene2D(OBJTYPE nPriority) : CScene::CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

CScene2D::~CScene2D()
{

}

HRESULT CScene2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice(); //デバイスを取得する

	m_pos = pos;
	m_size = size;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);
	VERTEX_2D *pVtx; //頂点情報のポインタ

					 //頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

void CScene2D::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//リリースを呼ぶとm_pVtxBuffがデリートされるから最後にやる
	Release();
}

void CScene2D::Update(void)
{

}

void CScene2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice(); //デバイスを取得する
													//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D); //頂点フォーマットの設定
	pDevice->SetTexture(0, m_pTexture);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); //ポリゴンの描画 
}

CScene2D *CScene2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int ntype)
{
	CScene2D *pScene2D;
	pScene2D = new CScene2D;

	if (pScene2D != NULL)
	{
		pScene2D->m_pTexture = m_apTexture[ntype];
		pScene2D->Init(pos, size);
	}

	return pScene2D;
}

void CScene2D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

D3DXVECTOR3 CScene2D::GetPos(void)
{
	return m_pos;
}

void CScene2D::SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;
	m_pos = pos;
	m_size = size;
	CScene::SetPos(m_pos);
	CScene::SetSize(m_size);

	// 位置を更新
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_pos.x - size.x, m_pos.y - size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + size.x, m_pos.y - size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - size.x, m_pos.y + size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + size.x, m_pos.y + size.y, 0.0f);

	m_pVtxBuff->Unlock();
}

bool CScene2D::SetTex(int nPatternAnim)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	// 位置を更新
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nPatternAnim * 0.125f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(nPatternAnim * 0.125f + 0.125f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(nPatternAnim * 0.125f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(nPatternAnim * 0.125f + 0.125f, 1.0f);

	m_pVtxBuff->Unlock();

	return true;
}

D3DXVECTOR3 CScene2D::GetSize(void)
{
	return m_size;
}

void CScene2D::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

void CScene2D::SetColor(D3DXCOLOR col)
{
	m_col = col;

	//頂点バッファの更新
	if (m_pVtxBuff != NULL)
	{
		VERTEX_2D *pVtx;
		//頂点バッファのロック
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		// 頂点情報を設定
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;

		//頂点バッファをアンロックする
		m_pVtxBuff->Unlock();
	}
}

void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	// テクスチャの割り当て
	m_pTexture = pTexture;
}

HRESULT CScene2D::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	//タイトル
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TITLE_BG,
		&m_apTexture[TEXTYPE_TITLE_BG]);
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TITLE_LOGO,
		&m_apTexture[TEXTYPE_TITLE_LOGO]);
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TITLE_GAME,
		&m_apTexture[TEXTYPE_TITLE_GAMEBUTTON]);
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TITLE_OP_BUTTON,
		&m_apTexture[TEXTYPE_TITLE_OP_BUTTON]);
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TITLE_OP,
		&m_apTexture[TEXTYPE_TITLE_OP]);

	//ゲーム
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GAME_SELECTBULLET_NORMAL,
		&m_apTexture[TEXTYPE_GAME_NORMALBULLET]);
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GAME_SELECTBULLET_HOMING,
		&m_apTexture[TEXTYPE_GAME_HOMINGBULLET]);
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GAME_SELECTBULLET_PENETRETION,
		&m_apTexture[TEXTYPE_GAME_PENETRETIONBULLET]);

	//リザルト
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_RESULT_BG,
		&m_apTexture[TEXTYPE_RESULT_BG]);

	return S_OK;
}

void CScene2D::Unload(void)
{
	for (int nCnt = 0; nCnt < TEXTYPE_MAX; nCnt++)
	{
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;

		}
	}
}