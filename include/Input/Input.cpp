#include "DxLib.h"
#include "./Input.h"


//----------------------------------------------------------------------------------------
// �L�[�̓��͏�ԍX�V
void Keyboard::update() {
	char tmpKey[256];				// ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll(tmpKey);		// �S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i<256; i++) {
		if (tmpKey[i] != 0) {		// i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			Key[i]++;				// ���Z
		}
		else {						// ������Ă��Ȃ����
			Key[i] = 0;				// 0�ɂ���
		}
	}
}
// KeyCode�̃L�[�̓��͏�Ԃ��擾����
int Keyboard::getKey(int KeyCode) {
	return Key[KeyCode];			// KeyCode�̓��͏�Ԃ�Ԃ�
}
Keyboard keyboard;

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

GPad::GPad(int id):
	padID(id)
{}

void GPad::update() {
	// ���͏�Ԃ��擾
	GetJoypadDirectInputState(DX_INPUT_PAD1, &input);
}

unsigned int GPad::getPadNum() {
	return GetJoypadNum();
}

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

void Mouse::update() {
	if (GetMousePoint(&x, &y) == -1)
		return;
	int input = GetMouseInput();
	for (int i = 0; i < 3; ++i) {
		if ((button[i] & input) != 0)
			button[i]++;
		else
			button[i] = 0;
	}
	wheel = GetMouseWheelRotVol();
}
Mouse mouse;
//----------------------------------------------------------------------------------------