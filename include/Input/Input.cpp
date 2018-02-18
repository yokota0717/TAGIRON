#include "DxLib.h"
#include "./Input.h"


//----------------------------------------------------------------------------------------
// キーの入力状態更新
void Keyboard::update() {
	char tmpKey[256];				// 現在のキーの入力状態を格納する
	GetHitKeyStateAll(tmpKey);		// 全てのキーの入力状態を得る
	for (int i = 0; i<256; i++) {
		if (tmpKey[i] != 0) {		// i番のキーコードに対応するキーが押されていたら
			Key[i]++;				// 加算
		}
		else {						// 押されていなければ
			Key[i] = 0;				// 0にする
		}
	}
}
// KeyCodeのキーの入力状態を取得する
int Keyboard::getKey(int KeyCode) {
	return Key[KeyCode];			// KeyCodeの入力状態を返す
}
Keyboard keyboard;

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

GPad::GPad(int id):
	padID(id)
{}

void GPad::update() {
	// 入力状態を取得
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