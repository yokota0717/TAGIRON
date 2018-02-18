#pragma once


//�L�[�{�[�h����
class Keyboard {
	unsigned int Key[256];  // �L�[�̓��͏�Ԋi�[�p�ϐ�

public:
	// �L�[�̓��͏�ԍX�V
	void update();
	// KeyCode�̃L�[�̓��͏�Ԃ��擾����
	int getKey(int KeyCode);
};
extern Keyboard keyboard;

//----------------------------------------------------------------------------------------

/*
PAD_INPUT_DOWN�@	// ���`�F�b�N�}�X�N(���L�[ or �e���L�[�̂Q�L�[)
PAD_INPUT_LEFT�@	// ���`�F�b�N�}�X�N(���L�[ or �e���L�[�̂S�L�[)
PAD_INPUT_RIGHT	// ���`�F�b�N�}�X�N(�E�L�[ or �e���L�[�̂U�L�[)
PAD_INPUT_UP�@	// ���`�F�b�N�}�X�N(��L�[ or �e���L�[�̂W�L�[)
PAD_INPUT_1�@	// 1�{�^���`�F�b�N�}�X�N(�y�L�[)
PAD_INPUT_2�@	// 2�{�^���`�F�b�N�}�X�N(�w�L�[)
PAD_INPUT_3�@	// 3�{�^���`�F�b�N�}�X�N(�b�L�[)
PAD_INPUT_4�@	// 4�{�^���`�F�b�N�}�X�N(�`�L�[)
PAD_INPUT_5�@	// 5�{�^���`�F�b�N�}�X�N(�r�L�[)
PAD_INPUT_6�@	// 6�{�^���`�F�b�N�}�X�N(�c�L�[)
PAD_INPUT_7�@	// 7�{�^���`�F�b�N�}�X�N(�p�L�[)
PAD_INPUT_8�@	// 8�{�^���`�F�b�N�}�X�N(�v�L�[)
PAD_INPUT_9�@	// 9�{�^���`�F�b�N�}�X�N(�d�r�b�L�[)
PAD_INPUT_10�@	// 10�{�^���`�F�b�N�}�X�N(�X�y�[�X�L�[)

#define PAD_INPUT_DOWN								(0x00000001)	// ���`�F�b�N�}�X�N
#define PAD_INPUT_LEFT								(0x00000002)	// ���`�F�b�N�}�X�N
#define PAD_INPUT_RIGHT								(0x00000004)	// ���`�F�b�N�}�X�N
#define PAD_INPUT_UP								(0x00000008)	// ���`�F�b�N�}�X�N
#define PAD_INPUT_A									(0x00000010)	// �`�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_B									(0x00000020)	// �a�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_C									(0x00000040)	// �b�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_X									(0x00000080)	// �w�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_Y									(0x00000100)	// �x�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_Z									(0x00000200)	// �y�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_L									(0x00000400)	// �k�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_R									(0x00000800)	// �q�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_START								(0x00001000)	// �r�s�`�q�s�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_M									(0x00002000)	// �l�{�^���`�F�b�N�}�X�N


typedef struct tagDINPUT_JOYSTATE
{
int						X ;								// �X�e�B�b�N�̂w���p�����[�^( -1000�`1000 )
int						Y ;								// �X�e�B�b�N�̂x���p�����[�^( -1000�`1000 )
int						Z ;								// �X�e�B�b�N�̂y���p�����[�^( -1000�`1000 )
int						Rx ;							// �X�e�B�b�N�̂w����]�p�����[�^( -1000�`1000 )
int						Ry ;							// �X�e�B�b�N�̂x����]�p�����[�^( -1000�`1000 )
int						Rz ;							// �X�e�B�b�N�̂y����]�p�����[�^( -1000�`1000 )
int						Slider[ 2 ] ;					// �X���C�_�[���
unsigned int			POV[ 4 ] ;						// �n�b�g�X�C�b�`�S��( 0xffffffff:���͂Ȃ� 0:�� 4500:�E�� 9000:�E 13500:�E�� 18000:�� 22500:���� 27000:�� 31500:���� )
unsigned char			Buttons[ 32 ] ;					// �{�^���R�Q��( �����ꂽ�{�^���� 128 �ɂȂ� )
} DINPUT_JOYSTATE ;

*/
//�p�b�h����
class GPad {
	enum PadType {
		one,
		two,
		three,
		four,
	};
	DINPUT_JOYSTATE input;		//���͏��
	unsigned int padNum;		//�ڑ�����Ă���p�b�h�̐�

	GPad(int);
	void update();
	unsigned int getPadNum();

private:
	unsigned int padID;
};

//----------------------------------------------------------------------------------------

//�}�E�X����
class Mouse {
public:
	int x, y;				//���W
	int wheel;				//�z�C�[���̏��
	unsigned int button[3];	//�{�^���̏��
	bool visible;			//�}�E�X�|�C���^�̕\���̗L��

	void update();			//�X�V����
};
extern Mouse mouse;