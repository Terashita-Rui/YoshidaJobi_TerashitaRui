#include"scene.h"
#include"scene2D.h"
#include"renderer.h"

CScene *CScene::m_apScene[OBJTYPE_MAX][MAX_POLYGON] = {};
int CScene::m_NumAll = 0;

CScene::CScene(OBJTYPE nPriority)
{
	int nCntScene;

	for (nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	{
		if (m_apScene[nPriority][nCntScene] == NULL)
		{
			m_apScene[nPriority][nCntScene] = this;

			//Ž©•ª‚Ì”Ô†‚ðÝ’è
			m_nID = nCntScene;
			m_nPriority = nPriority;
			m_objType = OBJTYPE_NONE;
			m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_NumAll++;
			break;
		}
	}
}

CScene::~CScene()
{

}

void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}

CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}

void CScene::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

D3DXVECTOR3 CScene::GetPos(void)
{
	return m_pos;
}

D3DXVECTOR3 CScene::GetSize(void)
{
	return m_size;
}

void CScene::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

CScene *CScene::GetScene(int nPriority, int nScene)
{
	return m_apScene[nPriority][nScene];
}

void CScene::ReleaseAll(void)
{
	//for‰ñ‚·•Ï”
	int nCntPriority;
	int nCntScene;

	for (nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				m_apScene[nCntPriority][nCntScene]->Uninit();
			}
		}
	}
}

void CScene::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < OBJTYPE_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				m_apScene[nCntPriority][nCntScene]->Update();
			}

		}
	}
}

void CScene::DrawAll(void)
{
	for (int nCntPriority = 0; nCntPriority < OBJTYPE_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				m_apScene[nCntPriority][nCntScene]->Draw();
			}
		}
	}
}

void CScene::Release(void)
{
	if (m_apScene[m_nPriority][m_nID] != NULL)
	{
		int nID = m_nID;
		int nPriority = m_nPriority;

		//delete m_apScene[nPriority][nID];
		m_apScene[nPriority][nID] = NULL;
		m_NumAll--;
	}
}