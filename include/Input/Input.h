#pragma once


//キーボード入力
class Keyboard {
	unsigned int Key[256];  // キーの入力状態格納用変数

public:
	// キーの入力状態更新
	void update();
	// KeyCodeのキーの入力状態を取得する
	int getKey(int KeyCode);
};
extern Keyboard keyboard;

//----------------------------------------------------------------------------------------

/*
PAD_INPUT_DOWN　	// ↓チェックマスク(下キー or テンキーの２キー)
PAD_INPUT_LEFT　	// ←チェックマスク(左キー or テンキーの４キー)
PAD_INPUT_RIGHT	// →チェックマスク(右キー or テンキーの６キー)
PAD_INPUT_UP　	// ↑チェックマスク(上キー or テンキーの８キー)
PAD_INPUT_1　	// 1ボタンチェックマスク(Ｚキー)
PAD_INPUT_2　	// 2ボタンチェックマスク(Ｘキー)
PAD_INPUT_3　	// 3ボタンチェックマスク(Ｃキー)
PAD_INPUT_4　	// 4ボタンチェックマスク(Ａキー)
PAD_INPUT_5　	// 5ボタンチェックマスク(Ｓキー)
PAD_INPUT_6　	// 6ボタンチェックマスク(Ｄキー)
PAD_INPUT_7　	// 7ボタンチェックマスク(Ｑキー)
PAD_INPUT_8　	// 8ボタンチェックマスク(Ｗキー)
PAD_INPUT_9　	// 9ボタンチェックマスク(ＥＳＣキー)
PAD_INPUT_10　	// 10ボタンチェックマスク(スペースキー)

#define PAD_INPUT_DOWN								(0x00000001)	// ↓チェックマスク
#define PAD_INPUT_LEFT								(0x00000002)	// ←チェックマスク
#define PAD_INPUT_RIGHT								(0x00000004)	// →チェックマスク
#define PAD_INPUT_UP								(0x00000008)	// ↑チェックマスク
#define PAD_INPUT_A									(0x00000010)	// Ａボタンチェックマスク
#define PAD_INPUT_B									(0x00000020)	// Ｂボタンチェックマスク
#define PAD_INPUT_C									(0x00000040)	// Ｃボタンチェックマスク
#define PAD_INPUT_X									(0x00000080)	// Ｘボタンチェックマスク
#define PAD_INPUT_Y									(0x00000100)	// Ｙボタンチェックマスク
#define PAD_INPUT_Z									(0x00000200)	// Ｚボタンチェックマスク
#define PAD_INPUT_L									(0x00000400)	// Ｌボタンチェックマスク
#define PAD_INPUT_R									(0x00000800)	// Ｒボタンチェックマスク
#define PAD_INPUT_START								(0x00001000)	// ＳＴＡＲＴボタンチェックマスク
#define PAD_INPUT_M									(0x00002000)	// Ｍボタンチェックマスク


typedef struct tagDINPUT_JOYSTATE
{
int						X ;								// スティックのＸ軸パラメータ( -1000～1000 )
int						Y ;								// スティックのＹ軸パラメータ( -1000～1000 )
int						Z ;								// スティックのＺ軸パラメータ( -1000～1000 )
int						Rx ;							// スティックのＸ軸回転パラメータ( -1000～1000 )
int						Ry ;							// スティックのＹ軸回転パラメータ( -1000～1000 )
int						Rz ;							// スティックのＺ軸回転パラメータ( -1000～1000 )
int						Slider[ 2 ] ;					// スライダー二つ
unsigned int			POV[ 4 ] ;						// ハットスイッチ４つ( 0xffffffff:入力なし 0:上 4500:右上 9000:右 13500:右下 18000:下 22500:左下 27000:左 31500:左上 )
unsigned char			Buttons[ 32 ] ;					// ボタン３２個( 押されたボタンは 128 になる )
} DINPUT_JOYSTATE ;

*/
//パッド入力
class GPad {
	enum PadType {
		one,
		two,
		three,
		four,
	};
	DINPUT_JOYSTATE input;		//入力情報
	unsigned int padNum;		//接続されているパッドの数

	GPad(int);
	void update();
	unsigned int getPadNum();

private:
	unsigned int padID;
};

//----------------------------------------------------------------------------------------

//マウス入力
class Mouse {
public:
	int x, y;				//座標
	int wheel;				//ホイールの状態
	unsigned int button[3];	//ボタンの状態
	bool visible;			//マウスポインタの表示の有無

	void update();			//更新処理
};
extern Mouse mouse;