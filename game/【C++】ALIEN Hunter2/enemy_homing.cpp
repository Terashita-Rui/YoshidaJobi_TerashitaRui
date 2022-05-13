#include"enemy_homing.h"
#include"renderer.h"
#include"manager.h"
#include"explosion.h"
#include"score.h"
#include"fade.h"
#include"score.h"
#include"game.h"

#define TEXTURE_NAME "data/Texture/enemy/enemy001.png"

LPDIRECT3DTEXTURE9 CEnemy_h::m_pTexture = NULL;

CEnemy_h::CEnemy_h(OBJTYPE nPriority) : CScene2D(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bUse = false;
	m_move = D3DXVECTOR3(6.0f, 0.0f, 0.0f);
	m_fSpeed = 4.0f;
}

CEnemy_h::~CEnemy_h()
{

}

HRESULT CEnemy_h::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_pos = pos;
	m_size = size;
	CScene2D::Init(pos, size);
	SetObjType(CScene::OBJTYPE_ENEMY);
	return S_OK;
}

void CEnemy_h::Uninit(void)
{
	CScene2D::Uninit();
}

void CEnemy_h::Update(void)
{
	for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	{
		CScene *pScene;
		//objにプレイヤー指定
		pScene = CScene::GetScene(OBJTYPE_PLAYER, nCntScene);
		if (pScene != NULL)
		{
			CScene::OBJTYPE objType;
			objType = pScene->GetObjType();

			//objがプレイヤーなら
			if (objType == CScene::OBJTYPE_PLAYER)
			{
				m_PlayerPos = pScene->GetPos();
				m_Vector = m_PlayerPos - m_pos;
				m_fLenght = sqrt((m_Vector.x*m_Vector.x) + (m_Vector.y*m_Vector.y));
				m_fAngle = atan2(m_Vector.x, m_Vector.y);
			}
		}
	}
	//情報渡す
	SetPosition(m_pos, m_size);

	//弾画面外行ったら消す
	if (m_pos.x > SCREEN_WIDTH ||
		m_pos.x < 0 ||
		m_pos.y > SCREEN_HEIGHT ||
		m_pos.y < 0)
	{

		Uninit();
	}
	//pos取得
	m_pos = GetPos();

	//移動
	m_pos.x -= m_fSpeed;
	m_pos.y += cosf(m_fAngle)*m_fSpeed;

	//当たり判定
	Collision();
}

void CEnemy_h::Draw(void)
{
	CScene2D::Draw();
}

bool CEnemy_h::Collision(void)
{
	for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	{
		CScene *pScene;
		pScene = CScene::GetScene(OBJTYPE_PLAYER, nCntScene);

		if (pScene != NULL)
		{
			CScene::OBJTYPE objType;
			objType = pScene->GetObjType();

			//objがプレイヤーなら
			if (objType == CScene::OBJTYPE_PLAYER)
			{
				//objの各情報
				D3DXVECTOR3 Pos = pScene->GetPos();
				D3DXVECTOR3 Size = pScene->GetSize();

				//当たり判定取る＋当たったら
				if (m_pos.x + m_size.x > Pos.x - Size.x &&
					m_pos.x - m_size.x < Pos.x + Size.x &&
					m_pos.y + m_size.y > Pos.y - Size.y &&
					m_pos.y - m_size.y < Pos.y + Size.y)
				{
					//爆発
					CExplosion::Create(Pos, D3DXVECTOR3(EXPLOSION_WIDTH, EXPLOSION_HIGHT, 0.0f));
					//プレイヤー消す
					pScene->Uninit();
					CFade::SetFade(CManager::MODE_RESULT);
					m_bUse = true;
					Uninit();
					return m_bUse;
					break;
				}
			}
		}
	}
}

//生成
CEnemy_h *CEnemy_h::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// クラスの生成
	CEnemy_h *pEnemy_h;
	pEnemy_h = new CEnemy_h(OBJTYPE_ENEMY);

	// ヌルチェック
	if (pEnemy_h != NULL)
	{
		// 初期化処理
		pEnemy_h->Init(pos, size);
		pEnemy_h->BindTexture(m_pTexture);
	}

	pEnemy_h->m_pos = pos;
	pEnemy_h->m_size = size;

	return pEnemy_h;
}

HRESULT CEnemy_h::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME,
		&m_pTexture);

	return S_OK;
}

void CEnemy_h::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}