#include "BaseClass.h"
#include "DxLib.h"
#include "../define.h"

Tile::Tile(int n, Color c, float x, float y) :
	Object("Tile"),
	num(n),
	color(c),
	pos(Vec(x, y))
{
	switch (num) {
	case 0:
		pic = color == Red ? graFac->GetGraph("./resource/graph/Red0.png")
			: graFac->GetGraph("./resource/graph/Blue0.png");
		break;
	case 1:
		pic = color == Red ? graFac->GetGraph("./resource/graph/Red1.png")
			: graFac->GetGraph("./resource/graph/Blue1.png");
		break;
	case 2:
		pic = color == Red ? graFac->GetGraph("./resource/graph/Red2.png")
			: graFac->GetGraph("./resource/graph/Blue2.png");
		break;
	case 3:
		pic = color == Red ? graFac->GetGraph("./resource/graph/Red3.png")
			: graFac->GetGraph("./resource/graph/Blue3.png");
		break;
	case 4:
		pic = color == Red ? graFac->GetGraph("./resource/graph/Red4.png")
			: graFac->GetGraph("./resource/graph/Blue4.png");
		break;
	case 5:
		pic = color == Red ? graFac->GetGraph("./resource/graph/Red5.png")
			: graFac->GetGraph("./resource/graph/Blue5.png");
		break;
	case 6:
		pic = color == Red ? graFac->GetGraph("./resource/graph/Red6.png")
			: graFac->GetGraph("./resource/graph/Blue6.png");
		break;
	case 7:
		pic = color == Red ? graFac->GetGraph("./resource/graph/Red7.png")
			: graFac->GetGraph("./resource/graph/Blue7.png");
		break;
	case 8:
		pic = color == Red ? graFac->GetGraph("./resource/graph/Red8.png")
			: graFac->GetGraph("./resource/graph/Blue8.png");
		break;
	case 9:
		pic = color == Red ? graFac->GetGraph("./resource/graph/Red9.png")
			: graFac->GetGraph("./resource/graph/Blue9.png");
		break;
	}
}

void Tile::render() {
	//DrawGraphF(pos.x, pos.y, pic, true);
	DrawBox((int)pos.x, (int)pos.y, (int)pos.x + 60, (int)pos.y + 80, color==Red?red:blue, true);
	DrawFormatStringF(pos.x + 10, pos.y + 15, white, "%d", num);
}