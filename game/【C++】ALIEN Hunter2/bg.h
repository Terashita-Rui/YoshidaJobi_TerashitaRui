#ifndef _BG_H_
#define _BG_H_

#include "main.h"
#include "scene.h"

#define MAX_BG (3)

class CScene2D;

class CBg : public CScene
{
public:
	typedef enum
	{
		TYPE_001,
		TYPE_002,
		TYPE_003,
		TYPE_MAX
	} TYPE;	//�|���S���̃e�N�X�`���̎��

	CBg();	//�f�t�H���g�R���X�g���N�^
	~CBg();	//�f�X�g���N�^
	static CBg* Create(void);	//��������
	static HRESULT Load(void);		//�e�N�X�`���̓ǂݍ���
	static void Unload(void);		//�e�N�X�`���̉��
	HRESULT Init(void);	//����������
	void Uninit(void);	//�I������
	void Update(void);	//�X�V����
	void Draw(void);	//�`�揈��

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];	//�e�N�X�`���ւ̃|�C���^
	CScene2D* m_apScene2D[MAX_BG];	//2D�|���S��
	float m_aTopTexV[MAX_BG];	//�e�N�X�`�����W��V�̏�
};

#endif // !_BG_H_