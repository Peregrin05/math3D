//
// Created by Islam Aliev on 27/12/14.
// Copyright (c) 2014 me. All rights reserved.
//

#include <math.h>
#include "Quaternion.h"

Quaternion::Quaternion(float theta, Vector3D const &v) {
	float halfTheta = theta / 2;
	_w = cosf(halfTheta);
	float sinTheta = sinf(halfTheta);
	_x = sinTheta * v.x();
	_y = sinTheta * v.y();
	_z = sinTheta * v.z();
}

Quaternion::Quaternion(float w, float x, float y, float z): _w(w), _x(x), _y(y), _z(z) {}

Quaternion::Quaternion(): Quaternion(1, 0, 0, 0) {}

void Quaternion::w(float value) {
	_w = value;
}

void Quaternion::x(float value) {
	_x = value;
}

void Quaternion::y(float value) {
	_y = value;
}

void Quaternion::z(float value) {
	_z = value;
}

void Quaternion::invert() {
	_x *= -1;
	_y *= -1;
	_z *= -1;
}

Quaternion Quaternion::operator*(const Quaternion &q) const {
	float w = _w * q._w - _x * q._x - _y * q._y - _z * q._z;
	float x = _w * q._x + _x * q._w + _y * q._z - _z * q._y;
	float y = _w * q._y + _y * q._w + _z * q._x - _x * q._z;
	float z = _w * q._z + _z * q._w + _x * q._y - _y * q._x;

	return Quaternion(w, x, y, z);
}

Quaternion Quaternion::operator*(float scalar) const {
	return Quaternion(_w * scalar, _x * scalar, _y * scalar, _z * scalar);
}

Quaternion Quaternion::getDifference(const Quaternion &q1, const Quaternion &q2) {
	Quaternion inverse = q1;
	inverse.invert();
	return q2 * inverse;
}

float Quaternion::dotProduct(const Quaternion &q1, const Quaternion &q2) {
	return q1._w * q2._w + q1._x * q2._x + q1._y * q2._y + q1._z * q2._z;
}

Quaternion Quaternion::exp(float exponent) const {
	Quaternion expQuaternion = *this;
	if (fabs(_w) < 0.9999f) {
		float alpha = acosf(_w);
		float newAlpha = alpha * exponent;
		expQuaternion._w = cosf(newAlpha);

		float mult = sinf(newAlpha) / sinf(alpha);
		expQuaternion._x *= mult;
		expQuaternion._y *= mult;
		expQuaternion._z *= mult;
	}
	return expQuaternion;
}

Quaternion Quaternion::slerp(const Quaternion &to, float fraction) const {
	float w = to._w;
	float x = to._x;
	float y = to._y;
	float z = to._z;

	// Compute the "cosine of the angle" between the quaternions, using the dot product
	float cosOmega = _w * w + _x * x + _y * y + _z * z;

	// if negative dot, negate one of the input quaternions, to take the shorter 4D "arc"
	if (cosOmega < 0.0f) {
		 w = -w;
		 x = -x;
		 y = -y;
		 z = -z;
	}

	// Check if they are very close together, to protect against divide-by-zero
	float k0, k1;
	if (cosOmega > 0.9999f) {
		// Very close - just use linear interpolation
		k0 = 1.0f - fraction;
		k1 = fraction;
	} else {
		// Compute the sin of the angle using the trig identity sin * 2(omega) + cos * 2(omega) = 1
		float sinOmega = sqrtf(1.0f - cosOmega * cosOmega);

		// Compute the angle from its sin and cosine
		float omega = atan2f(sinOmega, cosOmega);

		// Compute inverse of denominator, so we only have to divide once
		float oneOverSinOmega = 1.0f / sinOmega;

		// Compute interpolation parameters
		k0 = sinf((1.0f - fraction) * omega) * oneOverSinOmega;
		k1 = sinf(fraction * omega) * oneOverSinOmega;
	}

	// interpolate
	w = _w * k0 + w * k1;
	x = _x * k0 + x * k1;
	y = _y * k0 + y * k1;
	z = _z * k0 + z * k1;

	return Quaternion (w, x, y, z);
}

Matrix3D Quaternion::toMatrix() const {
	float qx2 = _x * _x;
	float qy2 = _y * _y;
	float qz2 = _z * _z;
	float x1 = 1 - 2 * qy2 - 2 * qz2;
	float y1 = 2 * _x * _y + 2 * _w * _z;
	float z1 = 2 * _x * _z - 2 * _w * _y;
	float x2 = 2 * _x * _y - 2 * _w * _z;
	float y2 = 1 - 2 * qx2 - 2 * qz2;
	float z2 = 2 * _y * _z + 2 * _w * _x;
	float x3 = 2 * _x * _z + 2 * _w * _y;
	float y3 = 2 * _y * _z - 2 * _w * _x;
	float z3 = 1 - 2 * qx2 - 2 * qy2;
	return Matrix3D(x1, y1, z1, x2, y2, z2, x3, y3, z3);
}

Quaternion Quaternion::fromMatrix(const Matrix3D &matrix) {
	float x1 = matrix.x1();
	float y1 = matrix.y1();
	float z1 = matrix.z1();
	float x2 = matrix.x2();
	float y2 = matrix.y2();
	float z2 = matrix.z2();
	float x3 = matrix.x3();
	float y3 = matrix.y3();
	float z3 = matrix.z3();

	// output quaternion
	float qw, qx, qy, qz;

	// determine which of w, x, y or z has the largest absolute value
	float fourWSquareMinus1 = x1 + y2 + z3;
	float fourXSquareMinus1 = x1 - y2 - z3;
	float fourYSquareMinus1 = y2 - x1 - z3;
	float fourZSquareMinus1 = z3 - x1 - y2;

	int biggestIndex = 0;
	float fourBiggestSquareMinus1 = fourWSquareMinus1;
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
	float biggestVal = sqrtf(fourBiggestSquareMinus1 + 1) * 0.5f;
	float mult = 0.25f / biggestVal;

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

EulerAngles Quaternion::uprightToEulerAngles() const {
	float h, p, b;

	// extract sin(pitch)
	float sp = -2 * (_y * _z - _w * _x);

	// Check for Gimbal lock, giving slight tolerance for numerical imprecision
	if (fabs(sp) > 0.9999f) {
		// looking straight up tor down
		p = 1.570796f * sp; // pi / 2
		// compute heading, slam bank to zero
		h = atan2f(-_x * _z + _w * _y, 0.5f - _y * _y - _z * _z);
		b = 0;
	} else {
		// compute angles
		p = asinf(sp);
		h = atan2f(_x * _z + _w * _y, 0.5f - _x * _x - _y * _y);
		b = atan2f(_x * _y + _w * _z, 0.5f - _x * _x - _z * _z);
	}
	float toGrads = (float) (180 / M_PI);
	return EulerAngles(h * toGrads, p * toGrads, b * toGrads);
}

EulerAngles Quaternion::objectToEulerAngles() const {
	float h, p, b;

	// extract sin(pitch)
	float sp = -2 * (_y * _z + _w * _x);

	// Check for Gimbal lock, giving slight tolerance for numerical imprecision
	if (fabs(sp) > 0.9999f) {
		// looking straight up tor down
		p = 1.570796f * sp; // pi / 2
		// compute heading, slam bank to zero
		h = atan2f(-_x * _z - _w * _y, 0.5f - _y * _y - _z * _z);
		b = 0;
	} else {
		// compute angles
		p = asinf(sp);
		h = atan2f(_x * _z - _w * _y, 0.5f - _x * _x - _y * _y);
		b = atan2f(_x * _y - _w * _z, 0.5f - _x * _x - _z * _z);
	}
	float toGrads = (float) (180 / M_PI);
	return EulerAngles(h * toGrads, p * toGrads, b * toGrads);
}
