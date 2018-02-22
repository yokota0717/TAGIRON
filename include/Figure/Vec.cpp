#define _USE_MATH_DEFINES
#include "DxLib.h"
#include "Vec.h"
#include <math.h>
#include <iostream>


Vec Vec::Normalize() {
	float len = GetVecLen(*this);
	if (len == 0) return *this;
	return Vec(x /= len, y /= len);
}

const Vec Vec::RotateVecDegree(Vec v, float deg) {
	float rad = (deg / 180) * (float)M_PI;
	float tempX = v.x;
	float tempY = v.y;
	v.x = float(tempX*cos(rad) - tempY*sin(rad));
	v.y = float(tempX*sin(rad) + tempY*cos(rad));
	return v;
}

const Vec Vec::RotateVecRadian(Vec v, float rad) {
	float tempX = v.x;
	float tempY = v.y;
	v.x = float(tempX*cos(rad) - tempY*sin(rad));
	v.y = float(tempX*sin(rad) + tempY*cos(rad));
	return v;
}

const float Vec::GetDotVec(Vec v1, Vec v2) {
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

const float Vec::GetCrossVec2(Vec v1, Vec v2) {
	return (v1.x*v2.y) - (v1.y*v2.x);
}

const Vec Vec::GetCrossVec3(Vec v1, Vec v2) {
	Vec Result;
	Result.x = v1.y*v2.z - v1.z*v2.y;
	Result.y = v1.z*v2.x - v1.x*v2.z;
	Result.z = v1.x*v2.y - v1.y*v2.x;
	return Result;
}

const float Vec::GetVecLen(Vec v) {
	return std::pow(v.x*v.x + v.y*v.y + v.z*v.z, 0.5f);
}

const Vec Vec::GetUnitVec(Vec v) {
	float len = GetVecLen(v);
	Vec Result = v;
	Result.x /= len;
	Result.y /= len;
	Result.z /= len;
	return Result;
}

const Vec Vec::VecScale(Vec v, float n) {
	Vec Result;
	Result.x *= n;
	Result.y *= n;
	Result.z *= n;
	return Result;
}

const Vec Vec::GetUnitNormVec2Left(Vec v) {	//ç∂âÒÇËÇ…90ìxâÒì]ÇµÇƒÇÈÇæÇØÇ‚Ç≈Åô
	Vec Result = v;
	float tmpx = Result.x;
	Result.x = Result.y;
	Result.y = (-1)*tmpx;
	Result = GetUnitVec(Result);
	return Result;
}

const Vec Vec::GetUnitNormVec2Right(Vec v) {	//Ç±Ç¡ÇøÇÕâEâÒÇËÇ‚Ç≈Åô
	Vec Result = v;
	float tmpx = Result.x;
	Result.x = (-1)*Result.y;
	Result.y = tmpx;
	Result = GetUnitVec(Result);
	return Result;
}

const Vec Vec::GetUnitNormVec3(Vec v1, Vec v2) {
	Vec Result = GetCrossVec3(v1, v2);
	Result = GetUnitVec(Result);
	return Result;
}