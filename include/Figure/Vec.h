#pragma once

//�x�N�g���N���X
//�f�t�H���g������z=0.0f�Ȃ̂�2�����ł��g����ˁI
//2�����x�N�g���̊O�ς̓X�J���[�ɂȂ��B�߂�ǂ��ˁB

class Vec {
public:
	float x, y, z;		//���W

	Vec(float x = 0.0f, float y = 0.0f, float z = 0.0f):
		x(x),
		y(y),
		z(z)
	{}
	~Vec() {};

	Vec Normalize();											//�x�N�g���𐳋K��
	static const Vec RotateVecDegree(Vec, float);				//�x�N�g����x���@�ŉ�]����
	static const Vec RotateVecRadian(Vec, float);				//�x�N�g�����ʓx�@�ŉ�]����
	static const float GetDotVec(Vec v1, Vec v2);				//2�̃x�N�g���̓��ς�Ԃ�
	static const float GetCrossVec2(Vec v1, Vec v2);			//2�̃x�N�g���̊O�ς�Ԃ�(2����)
	static const Vec GetCrossVec3(Vec v1, Vec v2);				//2�̃x�N�g���̊O�ς�Ԃ�(3����)
	static const float GetVecLen(Vec v);						//�x�N�g���̒����𓾂�
	static const Vec GetUnitVec(Vec v);							//���K�����ꂽ�x�N�g���𓾂�
	static const Vec VecScale(Vec v, float n);					//�x�N�g����n�{����
	static const Vec GetUnitNormVec2Left(Vec v);				//2�����x�N�g���̒P�ʖ@���x�N�g���𓾂� v1�~v2 �x�N�g���̍����̕� (��:���w�̍��W�n)
	static const Vec GetUnitNormVec2Right(Vec v);				//2�����x�N�g���̒P�ʖ@���x�N�g���𓾂� v1�~v2 �x�N�g���̉E���̕� (��:���w�̍��W�n)
	static const Vec GetUnitNormVec3(Vec v1, Vec v2);			//3�������ʂ̒P�ʖ@���x�N�g���𓾂�(��:���w�̍��W�n) v1,v2�͕��ʏ�ɑ��݂���x�N�g��

	//�I�y���[�^��`
	const Vec& operator = (const Vec& v) { x = v.x; y = v.y; z = v.z; return *this; }
	const Vec& operator + (const Vec& v) const { return Vec(x + v.x, y + v.y, z + v.z); }
	const Vec& operator - (const Vec& v) const { return Vec(x - v.x, y - v.y, z - v.z); }
	const Vec& operator * (const float n) const { return Vec(x*n, y*n, z*n); }
	const Vec& operator += (const Vec& v) { return Vec(x += v.x, y += v.y, z += v.z); }
	const Vec& operator -= (const Vec& v) { return Vec(x -= v.x, y -= v.y, z -= v.z); }
	const Vec& operator *= (const float n) { return Vec(x *= n, y *= n, z *= n); }
	const Vec& operator /= (const float n) { return Vec(x /= n, y /= n, z /= n); }

};