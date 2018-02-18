#pragma once
#include "DxLib.h"
#include "../define.h"
#include "../Object/Object.h"
#include "../Resource/Resource.h"
#include <string>


extern GraphFactory* graFac;

class Scene :public Object {
public:
	Scene() :
		Object("Scene") {};

	void update() {}
	void updatePause() {}
	void updateSleep() {}
	void updateDestroy() {}

	void render() {}
	void renderPause() {}
	void renderSleep() {}
	void renderDestroy() {}
};

class Text :public Object {
public:
	Text(std::string txt) :
		Object("Text"),
		text(txt)
	{};

	void update() {}
	void updatePause() {}
	void updateSleep() {}
	void updateDestroy() {}

	void render() {
		DrawFormatString(100, 100, white, text.c_str());
	}
	void renderPause() {}
	void renderSleep() {}
	void renderDestroy() {}

	std::string text;
};


class test :public Object {
public:
	test(std::string fileName) :
		Object("Actor"),
		pic(graFac->GetGraph(fileName.c_str()))
	{}

	int pic;		//‰æ‘œƒnƒ“ƒhƒ‹

	void render() {
		DrawGraph(100, 100, pic, true);
	}
	void renderPause() {}
	void renderSleep() {}
	void renderDestroy() {}

};
