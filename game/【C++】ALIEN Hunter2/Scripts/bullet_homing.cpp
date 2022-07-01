#include"bullet_homing.h"
#include"manager.h"
#include"renderer.h"
#include"explosion.h"
#include"scene.h"
#include"enemy.h"
#include"player.h"

#define TEXTURE_NAME "data/Texture/bullet/bullet002.png"

LPDIRECT3DTEXTURE9 CBullet_h::m_pTexture = NULL;

CBullet_h::CBullet_h(OBJTYPE nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bUse = false;
	m_move = D3DXVECTOR3(6.0f, 0.0f, 0.0f);
	m_fSpeed = 6.0f;
}

CBullet_h::~CBullet_h()
{

}

HRESULT CBullet_h::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_size = size;
	m_pos = pos;
	CScene2D::Init(pos, size);
	SetObjType(CScene::OBJTYPE_BULLET);

	return S_OK;
}

void CBullet_h::Uninit(void)
{
	CScene2D::Uninit();
}

void CBullet_h::Update(void)
{
	for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	{
		CScene *pScene;
		pScene = CScene::GetScene(OBJTYPE_ENEMY, nCntScene);
		if (pScene != NULL)
		{
			CScene::OBJTYPE objType;
			objType = pScene->GetObjType();

			//objが敵なら           　↓敵
			if (objType == CScene::OBJTYPE_ENEMY)
			{
				//追尾に必要な情報を取得＆作成＆更新
				m_EnemyPos = pScene->GetPos();
				m_Vector = m_EnemyPos - m_pos;
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
	m_pos.x += m_fSpeed;

	//弾が敵の一定範囲内に入ったら追尾
	if (m_fLenght <= 250)
	{
		m_pos.y += cosf(m_fAngle)*m_fSpeed;
	}

	//当たり判定
	Collision();
}

void CBullet_h::Draw(void)
{
	CScene2D::Draw();
}


//生成
CBullet_h *CBullet_h::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// クラスの生成
	CBullet_h *pBullet_h;
	pBullet_h = new CBullet_h(OBJTYPE_BULLET);

	// ヌルチェック
	if (pBullet_h != NULL)
	{
		// 初期化処理
		pBullet_h->Init(pos, size);
		pBullet_h->BindTexture(m_pTexture);
	}

	pBullet_h->m_pos = pos;
	pBullet_h->m_size = size;

	return pBullet_h;
}

HRESULT CBullet_h::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME,
		&m_pTexture);

	return S_OK;
}

void CBullet_h::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}