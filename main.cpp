#include "DxLib.h"
#include "./include/Object/Object.h"
#include "./include/define.h"
#include "./include/Input/Input.h"
#include "./include/Resource/Resource.h"
#include "./include/BaseClass/BaseClass.h"
#include <string.h>


//-------------------------------------------------------------------------------------------------------------------
//���C�����[�v�̏������܂Ƃ߂�
int ProcessLoop() {
	if (ScreenFlip() != 0) return -1;
	if (ProcessMessage() != 0) return -1;
	if (ClearDrawScreen() != 0) return -1;
	return 0;
}
//-------------------------------------------------------------------------------------------------------------------
//�������֘A���܂Ƃ߂�
void DXinit() {
	SetOutApplicationLogValidFlag(FALSE);			//���O����
	SetMainWindowText("TAGIRON");					//�E�C���h�E�^�C�g����ύX
	SetGraphMode(800, 600, 16);						//��ʉ𑜓x�A�F�[�x�o�b�t�@�H�ύX
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);		//��ʃT�C�Y�ύX
	ChangeWindowMode(TRUE);							//�E�B���h�E���[�h�ύX
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);		//������
	DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);	//����ʐݒ�
}
//-------------------------------------------------------------------------------------------------------------------






//root�I�u�W�F�N�g
Object* root = new Object("Root");
int Object::uid_ = 0;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	DXinit();

	graFac = new GraphFactory();
	//�V�[��
	Object* title = new Scene();
	Object* game = new Scene();
	//�e�L�X�g
	Object* play = new Text("GAME");

	Object* logo = new test("./resource/graph/logo.png");

	title->insertAsChild(logo);
	game->insertAsChildPause(play);


	root->insertAsChild(title);
	root->insertAsChildPause(game);


	while (ProcessLoop() == 0) {

		root->updateWithChildren();
		root->renderWithChildren();



		
		keyboard.update();
		//�V�[���ڍs
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
		//�G�X�P�[�v
		if (keyboard.getKey(KEY_INPUT_ESCAPE) == 1) 
			break;
	};

	DxLib_End(); // DX���C�u�����I������
	return 0;
}