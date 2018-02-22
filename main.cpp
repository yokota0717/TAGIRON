#include "DxLib.h"
#include "./include/Object/Object.h"
#include "./include/define.h"
#include "./include/Input/Input.h"
#include "./include/Resource/Resource.h"
#include "./include/BaseClass/BaseClass.h"
#include <string.h>


//-------------------------------------------------------------------------------------------------------------------
//メインループの処理をまとめる
int ProcessLoop() {
	if (ScreenFlip() != 0) return -1;
	if (ProcessMessage() != 0) return -1;
	if (ClearDrawScreen() != 0) return -1;
	return 0;
}
//-------------------------------------------------------------------------------------------------------------------
//初期化関連をまとめる
void DXinit() {
	SetOutApplicationLogValidFlag(FALSE);			//ログ消し
	SetMainWindowText("TAGIRON");					//ウインドウタイトルを変更
	SetGraphMode(800, 600, 16);						//画面解像度、色深度バッファ？変更
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);		//画面サイズ変更
	ChangeWindowMode(TRUE);							//ウィンドウモード変更
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);		//初期化
	DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);	//裏画面設定
}
//-------------------------------------------------------------------------------------------------------------------






//rootオブジェクト
Object* root = new Object("Root");
int Object::uid_ = 0;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	DXinit();

	graFac = new GraphFactory();
	//シーン
	Object* title = new Scene();
	Object* game = new Scene();
	//テキスト
	Object* play = new Text("GAME");
	Object* logo = new test("./resource/graph/logo.png");

	Object* tiles[5];
	for (int i = 0; i < 5; ++i) {
		tiles[i] = new Tile(i, Red, 100.0f + 80 * i, 470.0f);
		game->insertAsChildPause(tiles[i]);
	}

	title->insertAsChild(logo);
	game->insertAsChildPause(play);


	root->insertAsChild(title);
	root->insertAsChildPause(game);


	//メインループ
	while (ProcessLoop() == 0) {

		root->updateWithChildren();
		root->renderWithChildren();



		
		keyboard.update();
		//シーン移行
		if (keyboard.getKey(KEY_INPUT_RETURN) == 1) {
			if (title->isRunning()) {
				title->pauseAll();
				game->runAll();
			}
			else if (game->isRunning()) {
				game->pauseAll();
				title->runAll();
			}
		}
		//エスケープ
		if (keyboard.getKey(KEY_INPUT_ESCAPE) == 1) 
			break;
	};

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}