#pragma once
#include "Vec.h"
#include <math.h>

struct Box2D {				//�l�p�`�\����
	float	x, y, w, h;		//����̍��W�A���A����

	Box2D() :x(0.0f), y(0.0f), w(0.0f), h(0.0f) {}
	Box2D(float x, float y, float w, float h) :x(x), y(y), w(w), h(h) {}
	~Box2D(){}
	void Offset(Vec v){							//�������x�N�g��
		x += v.x;
		y += v.y;
	}
	void Offset(float vx, float vy)  {			//������x,y
		x += vx;
		y += vy;
	}
	Box2D OffsetCopy(float vx, float vy) const {	//x,y�������ɂ���Box2D��Ԃ�
		return Box2D(x + vx, y + vy, w, h);
	}
	Box2D OffsetCopy(const Vec& v)const{
		return Box2D(x + v.x, y + v.y, w, h);
	}
	bool Hit(const Box2D& b) const{		//��`���m�̓����蔻��
		if (x	< b.x + b.w	&&
			b.x < x + w		&&
			y	< b.y + b.h	&&
			b.h < y + h		) {
			return true;
		}
		return false;
	}
	bool Hit(const Vec& b) const {		//��`�ƃx�N�g���̓����蔻��
		if (x	< b.x	&&
			b.x < x + w	&&
			y	< b.y	&&
			b.y < y + h	) {
			return true;
		}
		return false;
	}
};

struct Circle {
	float x, y, z;		//���S���W
	float r;			//���a

	Circle() :x(0.0f), y(0.0f), z(0.0f), r(0.0f) {};
	Circle(float x, float y, float z, float r) :x(x), y(y), z(z), r(r) {};
	~Circle() {};

	void Offset(Vec v) {							//�������x�N�g��
		x += v.x;
		y += v.y;
		z += v.z;
	}
	void Offset(float vx, float vy, float vz = 0.0f) {			//������x,y,z
		x += vx;
		y += vy;
		z = vz;
	}
	Circle OffsetCopy(float vx, float vy, float vz = 0.0f) const {	//x,y�������ɂ���Circle��Ԃ�
		return Circle(x + vx, y + vy, z + vz, r);
	}
	Circle OffsetCopy(const Vec& v)const {
		return Circle(x + v.x, y + v.y, z + v.z, r);
	}
	bool Hit(const Circle& c) const {
		//���S�Ԃ̋�������̔��a�̘a��菬����������true
		float mx = powf(x - c.x, 2.0f);
		float my = powf(y - c.y, 2.0f);
		float mz = powf(z - c.z, 2.0f);
		if (powf(mx + my + mz, 0.5f) <= (r + c.r)) return true;
		return false;
	}
	bool Hit(const Vec& v) const {
		float mx = powf(x - v.x, 2.0f);
		float my = powf(y - v.y, 2.0f);
		float mz = powf(z - v.z, 2.0f);
		if (powf(mx + my + mz, 0.5f) <= r) return true;
		return false;
	}

};

struct Triangle {
	Vec v1, v2, v3;		//3���_

	Triangle(Vec v1, Vec v2, Vec v3) :
		v1(v1), v2(v2), v3(v3)
	{}

};

struct Orval {
	float x, y;		//���S���W
	float lr, sr;	//�����A�Z��	 long radius,shot radius
	float angle;	//������x������̌X��

	Orval(float x,float y,float lr,float sr,float ang):
		x(x),y(y),
		lr(lr),sr(sr),
		angle(ang)
	{}
};