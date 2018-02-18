#include "DxLib.h"

unsigned int Key[256];  // キーの入力状態格納用変数

// キーの入力状態更新
void Keyboard_Update() {
	char tmpKey[256];             // 現在のキーの入力状態を格納する
	GetHitKeyStateAll(tmpKey);  // 全てのキーの入力状態を得る
	for (int i = 0; i<256; i++) {
		if (tmpKey[i] != 0) { // i番のキーコードに対応するキーが押されていたら
			Key[i]++;   // 加算
		}
		else {              // 押されていなければ
			Key[i] = 0; // 0にする
		}
	}
}

// KeyCodeのキーの入力状態を取得する
int Keyboard_Get(int KeyCode) {
	return Key[KeyCode]; // KeyCodeの入力状態を返す
}
