#ifndef __Qauternion_H_
#define __Qauternion_H_


#include "../core/Matrix3D.h"
#include "EulerAngles.h"

class EulerAngles;

class Quaternion {
public:
	Quaternion static getDifference(const Quaternion& q1, const Quaternion& q2);

	Quaternion static fromMatrix(const Matrix3D& matrix);

	float static dotProduct(const Quaternion& q1, const Quaternion& q2);

	Quaternion(float theta, Vector3D const &v = Vector3D(0,0,0));

	Quaternion(float w, float x, float y, float z);

	Quaternion();

	float w() const {
		return _w;
	}
	void w(float value);

	float x() const {
		return _x;
	}
	void x(float value);

	float y() const {
		return _y;
	}
	void y(float value);

	float z() const {
		return _z;
	}
	void z(float value);

	void invert();

	Quaternion operator*(const Quaternion& q) const;

	Quaternion operator*(float scalar) const;

	Quaternion exp(float exponent) const;

	Quaternion slerp(const Quaternion&to, float fraction) const;

	Matrix3D toMatrix() const;

	EulerAngles uprightToEulerAngles() const;

	EulerAngles objectToEulerAngles() const;

private:
	float _w;
	float _x;
	float _y;
	float _z;
};


#endif //__Qauternion_H_
