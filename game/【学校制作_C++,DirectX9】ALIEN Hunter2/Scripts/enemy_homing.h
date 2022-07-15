//�z�[�~���O�G
//Auther:��������


#ifndef _ENEMY_HOMING_H_
#define _ENEMY_HOMING_H_

#include"scene2D.h"

class CEnemy_h : public CScene2D
{
public:
	CEnemy_h(OBJTYPE nPriority = OBJTYPE_NONE);
	~CEnemy_h();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Collision(void);

	static CEnemy_h *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture; //�e�N�X�`���̃|�C���^
	D3DXVECTOR3 m_pos; //�ʒu���
	D3DXVECTOR3 m_move; //�ړ����x�P(�g��Ȃ�����)
	float m_fSpeed; //�ړ����x�Q
	D3DXVECTOR3	m_size;					// �T�C�Y
	D3DXVECTOR3 m_PlayerPos; //�v���C���[��pos
	D3DXVECTOR3 m_Vector; //�e->�G�̕����x�N�g��
	float m_fLenght; //��������
	float m_fAngle; //����
	bool m_bUse; //�g�������ǂ���
};
#endif