//���ʂ̒e
//Auther:��������

#ifndef _BULLET_H_
#define _BULLET_H_

#include"main.h"
#include"scene2D.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

class CEnemy;

//�e�̑傫��
#define BULLET_WIDTH 15.0f
#define BULLET_HEIGHT 10.0f
#define BULLET_KINDS 3 //�e�̎��

class CBullet : public CScene2D
{
public:
	CBullet(OBJTYPE nPriority = OBJTYPE_NONE);
	~CBullet();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Collision(void);

	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static HRESULT Load(void);
	static void Unload(void);

protected:
	D3DXVECTOR3 m_pos; //�ʒu���
	D3DXVECTOR3 m_move; //�ړ����x�P(�g��Ȃ�����)
	float m_fSpeed; //�ړ����x�Q
	static LPDIRECT3DTEXTURE9 m_pTexture; //�e�N�X�`���̃|�C���^
	D3DXVECTOR3	m_size;					// �T�C�Y
	D3DXVECTOR3 m_EnemyPos; //�G��pos
	D3DXVECTOR3 m_Vector; //�e->�G�̕����x�N�g��
	float m_fLenght; //��������
	float m_fAngle; //����
	bool m_bUse; //�g�������ǂ���
private:
};

#endif