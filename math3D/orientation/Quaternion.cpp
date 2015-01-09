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
