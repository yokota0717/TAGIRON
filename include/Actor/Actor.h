#pragma once
#include "DxLib.h"
#include "../Object/Object.h"


class Tile :public Object {
public:
	Tile():
		Object("Tile")
	{}

	void update() {}
	void updatePause() {}
	void updateSleep() {}
	void updateDestroy() {}

	void render() {}
	void renderPause() {}
	void renderSleep() {}
	void renderDestroy() {}
};