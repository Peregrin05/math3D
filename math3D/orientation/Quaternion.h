#ifndef __Qauternion_H_
#define __Qauternion_H_


#include "Vector3D.h"

class Quaternion {
public:
	Quaternion static getDifference(Quaternion& q1, Quaternion& q2);

	Quaternion static fromMatrix(Matrix3D& matrix);

	double static dotProduct(Quaternion& q1, Quaternion& q2);

	Quaternion(float const &theta = 0, Vector3D const &v = Vector3D(0,0,0));

	Quaternion(double const &w, double const &x = 0, double const &y = 0, double const &z = 0);

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

	Quaternion exp(float &exponent) const;

	Quaternion slerp(Quaternion&to, float fraction) const;

	Matrix3D toMatrix() const;

private:
	double _w;
	double _x;
	double _y;
	double _z;
};


#endif //__Qauternion_H_
