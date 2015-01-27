#ifndef __Qauternion_H_
#define __Qauternion_H_


#include "Vector3D.h"
#include "EulerAngles.h"

class EulerAngles;

class Quaternion {
public:
	Quaternion static getDifference(const Quaternion& q1, const Quaternion& q2);

	Quaternion static fromMatrix(const Matrix3D& matrix);

	double static dotProduct(const Quaternion& q1, const Quaternion& q2);

	Quaternion(float const &theta, Vector3D const &v = Vector3D(0,0,0));

	Quaternion(double const &w, double const &x, double const &y, double const &z);

	Quaternion();

	double const *w() const {
		return &_w;
	}
	void w(double const &value);

	double const *x() const {
		return &_x;
	}
	void x(double const &value);

	double const *y() const {
		return &_y;
	}
	void y(double const &value);

	double const *z() const {
		return &_z;
	}
	void z(double const &value);

	void invert();

	Quaternion operator*(const Quaternion& q) const;

	Quaternion operator*(const double& scalar) const;

	Quaternion exp(double const &exponent) const;

	Quaternion slerp(const Quaternion&to, const float fraction) const;

	Matrix3D toMatrix() const;

	EulerAngles uprightToEulerAngles() const;

	EulerAngles objectToEulerAngles() const;

private:
	double _w;
	double _x;
	double _y;
	double _z;
};


#endif //__Qauternion_H_
