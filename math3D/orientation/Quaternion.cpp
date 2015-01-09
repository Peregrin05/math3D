//
// Created by Islam Aliev on 27/12/14.
// Copyright (c) 2014 me. All rights reserved.
//

#include <math.h>
#include "Quaternion.h"

Quaternion::Quaternion(float const &theta, Vector3D const &v) {
	float halfTheta = theta / 2;
	_w = cos(halfTheta);
	double sinTheta = sin(halfTheta);
	_x = sinTheta * *v.x();
	_y = sinTheta * *v.y();
	_z = sinTheta * *v.z();
}

Quaternion::Quaternion(double const &w, double const &x, double const &y, double const &z): _w(w), _x(x), _y(y), _z(z) {}

Quaternion::Quaternion(): Quaternion(1, 0, 0, 0) {}

void Quaternion::w(double const &value) {
	_w = value;
}

void Quaternion::x(double const &value) {
	_x = value;
}

void Quaternion::y(double const &value) {
	_y = value;
}

void Quaternion::z(double const &value) {
	_z = value;
}

void Quaternion::invert() {
	_x *= -1;
	_y *= -1;
	_z *= -1;
}

Quaternion Quaternion::operator*(const Quaternion &q) const {
	double w = _w * q._w - _x * q._x - _y * q._y - _z * q._z;
	double x = _w * q._x + _x * q._w + _y * q._z - _z * q._y;
	double y = _w * q._y + _y * q._w + _z * q._x - _x * q._z;
	double z = _w * q._z + _z * q._w + _x * q._y - _y * q._x;

	return Quaternion(w, x, y, z);
}

Quaternion Quaternion::operator*(const double &scalar) const {
	return Quaternion(_w * scalar, _x * scalar, _y * scalar, _z * scalar);
}

Quaternion Quaternion::getDifference(Quaternion &q1, Quaternion &q2) {
	Quaternion inverse = q1;
	inverse.invert();
	return q2 * inverse;
}

double Quaternion::dotProduct(Quaternion &q1, Quaternion &q2) {
	return q1._w * q2._w + q1._x * q2._x + q1._y * q2._y + q1._z * q2._z;
}

Quaternion Quaternion::exp(float &exponent) const {
	Quaternion expQuaternion = *this;
	if (fabs(_w) < 0.9999f) {
		double alpha = acos(_w);
		double newAlpha = alpha * exponent;
		expQuaternion._w = cos(newAlpha);

		double mult = sin(newAlpha) / sin(alpha);
		expQuaternion._x *= mult;
		expQuaternion._y *= mult;
		expQuaternion._z *= mult;
	}
	return expQuaternion;
}

Quaternion Quaternion::slerp(Quaternion &to, float fraction) const {
	double w = to._w;
	double x = to._x;
	double y = to._y;
	double z = to._z;

	// Compute the "cosine of the angle" between the quaternions, using the dot product
	double cosOmega = _w * w + _x * x + _y * y + _z * z;

	// if negative dot, negate one of the input quaternions, to take the shorter 4D "arc"
	if (cosOmega < 0.0f) {
		 w = -w;
		 x = -x;
		 y = -y;
		 z = -z;
	}

	// Check if they are very close together, to protect against divide-by-zero
	double k0, k1;
	if (cosOmega > 0.9999f) {
		// Very close - just use linear interpolation
		k0 = 1 - fraction;
		k1 = fraction;
	} else {
		// Compute the sin of the angle using the trig identity sin * 2(omega) + cos * 2(omega) = 1
		double sinOmega = sqrt(1 - cosOmega * cosOmega);

		// Compute the angle from its sin and cosine
		double omega = atan2(sinOmega, cosOmega);

		// Compute inverse of denominator, so we only have to divide once
		double oneOverSinOmega = 1 / sinOmega;

		// Compute interpolation parameters
		k0 = sin((1 - fraction) * omega) * oneOverSinOmega;
		k1 = sin(1 * omega) * oneOverSinOmega;
	}

	// interpolate
	w = _w * k0 + w * k1;
	x = _x * k0 + x * k1;
	y = _y * k0 + y * k1;
	z = _z * k0 + z * k1;

	return Quaternion (w, x, y, z);
}

Matrix3D Quaternion::toMatrix() const {
	double qx2 = _x * _x;
	double qy2 = _y * _y;
	double qz2 = _z * _z;
	double x1 = 1 - 2 * qy2 - 2 * qz2;
	double y1 = 2 * _x * _y + 2 * _w * _z;
	double z1 = 2 * _x * _z - 2 * _w * _y;
	double x2 = 2 * _x * _y - 2 * _w * _z;
	double y2 = 1 - 2 * qx2 - 2 * qz2;
	double z2 = 2 * _y * _z + 2 * _w * _x;
	double x3 = 2 * _x * _z + 2 * _w * _y;
	double y3 = 2 * _y * _z - 2 * _w * _x;
	double z3 = 1 - 2 * qx2 - 2 * qy2;
	return Matrix3D(x1, y1, z1, x2, y2, z2, x3, y3, z3);
}

Quaternion Quaternion::fromMatrix(Matrix3D &matrix) {
	double x1 = *matrix.x1();
	double y1 = *matrix.y1();
	double z1 = *matrix.z1();
	double x2 = *matrix.x2();
	double y2 = *matrix.y2();
	double z2 = *matrix.z2();
	double x3 = *matrix.x3();
	double y3 = *matrix.y3();
	double z3 = *matrix.z3();

	// output quaternion
	double qw, qx, qy, qz;

	// determine which of w, x, y or z has the largest absolute value
	double fourWSquareMinus1 = x1 + y2 + z3;
	double fourXSquareMinus1 = x1 - y2 - z3;
	double fourYSquareMinus1 = y2 - x1 - z3;
	double fourZSquareMinus1 = z3 - x1 - y2;

	int biggestIndex = 0;
	double fourBiggestSquareMinus1 = fourWSquareMinus1;
	if (fourXSquareMinus1 > fourBiggestSquareMinus1) {
		fourBiggestSquareMinus1 = fourXSquareMinus1;
		biggestIndex = 1;
	}
	if (fourYSquareMinus1 > fourBiggestSquareMinus1) {
		fourBiggestSquareMinus1 = fourYSquareMinus1;
		biggestIndex = 2;
	}
	if (fourZSquareMinus1 > fourBiggestSquareMinus1) {
		fourBiggestSquareMinus1 = fourZSquareMinus1;
		biggestIndex = 3;
	}

	// perform square root and division
	double biggestVal = sqrt(fourBiggestSquareMinus1 + 1) * 0.5;
	double mult = 0.25 / biggestVal;

	// apply table to compute quaternion values
	switch (biggestIndex) {
		case 1:
			qx = biggestVal;
			qw = (z2 - y3) * mult;
			qy = (y1 + x2) * mult;
			qz = (x3 + z1) * mult;
			break;
		case 2:
			qy = biggestVal;
			qw = (x3 - z1) * mult;
			qx = (y1 + x2) * mult;
			qz = (z2 + y3) * mult;
			break;
		case 3:
			qz = biggestVal;
			qw = (y1 - x2) * mult;
			qx = (x3 + z1) * mult;
			qy = (z2 + y3) * mult;
			break;
		default:
			qw = biggestVal;
			qx = (z2 - y2) * mult;
			qy = (x3 - z1) * mult;
			qz = (y1 - x2) * mult;
			break;
	}
	return Quaternion(qw, qx, qy, qz);
}
