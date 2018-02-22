#pragma once
#include "DxLib.h"
#include "../define.h"
#include "../Object/Object.h"
#include "../Resource/Resource.h"
#include "../Figure/Vec.h"
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

	int pic;		//画像ハンドル

	void render() {
		DrawGraph(100, 100, pic, true);
	}
	void renderPause() {}
	void renderSleep() {}
	void renderDestroy() {}

};

	enum Color {
		Red,
		Blue,
		Green,
	};



class Tile :public Object {
public:
	Vec pos;
	int pic;		//画像ハンドル
	int num;		//数字０～９
	Color color;	//色　5は緑のみ

	Tile(int, Color, float, float);

	void update() {}
	void updatePause() {}
	void updateSleep() {}
	void updateDestroy() {}

	void render();
	void renderPause() {}
	void renderSleep() {}
	void renderDestroy() {}

};

class Question :public Object {
public:
	int id;

	void update() {}
	void updatePause() {}
	void updateSleep() {}
	void updateDestroy() {}

	void render() {}
	void renderPause() {}
	void renderSleep() {}
	void renderDestroy() {}
};