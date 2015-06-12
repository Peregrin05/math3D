#include <math.h>
#include "EulerAngles.h"

EulerAngles::EulerAngles(float heading, float pitch, float bank) : _heading(heading), _pitch(pitch), _bank(bank) {};

void EulerAngles::heading(float value) {
	_heading = value;
}

void EulerAngles::pitch(float value) {
	_pitch = value;
}

void EulerAngles::bank(float value) {
	_bank = value;
}

bool EulerAngles::isCanonical() const {
	if (_heading <= -180) {
		return false;
	}
	if (_heading > 180) {
		return false;
	}
	if (_pitch < -90) {
		return false;
	}
	if (_pitch > 90) {
		return false;
	}
	if (_bank <= -180) {
		return false;
	}
	if (_bank > 180) {
		return false;
	}
	// check for Gimbal lock
    return !((_pitch == 90 || _pitch == -90) && _bank != 0);
}

void EulerAngles::canonize() {
	_pitch = _wrap180(_pitch);

	if (_pitch == 90 || _pitch == -90) { // Gimbal lock
		if (_pitch == 90) {
			_heading += _bank;
		} else {
			_heading -= _bank;
		}
		_bank = 0;
	} else {
		if (_pitch > 90) {
			_pitch = 180 - _pitch;
			_heading += 180;
			_bank += 180;
		} else if (_pitch < -90) {
			_pitch = -180 - _pitch;
			_heading += 180;
			_bank += 180;
		}
		_bank = _wrap180(_bank);
		if (_bank == -180) {
			_bank = 180;
		}
	}

	_heading = _wrap180(_heading);
	if (_heading == -180) {
		_heading = 180;
	}
}

float EulerAngles::_wrap180(float theta) {
	// Check if already in range
	if (theta > HALF_CIRCLE || theta <= -HALF_CIRCLE) {
		// out of range. Determine how many "revolutions" we need to add
		float revolutions = floorf((theta + HALF_CIRCLE) / FULL_CIRCLE);
		theta -= revolutions * FULL_CIRCLE;
	}
	return theta;
}

Matrix3D EulerAngles::toUprightMatrix() const {
	float h = (float) (_heading * M_PI / 180);
	float p = (float) (_pitch * M_PI / 180);
	float b = (float) (_bank * M_PI / 180);

	float ch = cosf(h);
	float sh = sinf(h);
	float cp = cosf(p);
	float sp = sinf(p);
	float cb = cosf(b);
	float sb = sinf(b);

	float x1 = ch * cb + sh * sp * sb;
	float y1 = sb * cp;
	float z1 = -sh * cb + ch * sp * sb;
	float x2 = -ch * sb + sh * sp * cb;
	float y2 = cb * cp;
	float z2 = sb * sh + ch * sp * cb;
	float x3 = sh * cp;
	float y3 = -sp;
	float z3 = ch * cp;

	return Matrix3D(x1, y1, z1, x2, y2, z2, x3, y3, z3);
}

Matrix3D EulerAngles::toObjectMatrix() const {
	float h = (float) (_heading * M_PI / 180);
	float p = (float) (_pitch * M_PI / 180);
	float b = (float) (_bank * M_PI / 180);

	float ch = cosf(h);
	float sh = sinf(h);
	float cp = cosf(p);
	float sp = sinf(p);
	float cb = cosf(b);
	float sb = sinf(b);

	float x1 = ch * cb + sh * sp * sb;
	float y1 = -ch * sb + sh * sp * cb;
	float z1 = sh * cp;
	float x2 = sb * cp;
	float y2 = cb * cp;
	float z2 = -sp;
	float x3 = -sh * cb + ch * sp * sb;
	float y3 = sb * sh + ch * sp * cb;
	float z3 = ch * cp;

	return Matrix3D(x1, y1, z1, x2, y2, z2, x3, y3, z3);
}

EulerAngles EulerAngles::fromUprightMatrix(const Matrix3D &matrix) {
	// We will compute the Euler angle values in radians and store them here:
	float h, p, b;

	// Extract pitch from y3, being careful for domain errors with asin().
	// We could have values slightly out of range due to floating point arithmetic
	float sp = -matrix.y3();

	if (sp <= -1.0f) {
		p = (float) (-M_PI / 2);
	} else if (sp >= 1.0f) {
		p = (float) (M_PI / 2);
	} else {
		p = asinf(sp);
	}

	// Check for the Gimbal lock case, giving a slight tolerance for numerical imprecision
	if (fabsf(sp) > 0.9999f) {
		// We are looking straight up or down. 
		// Slam bank to zero and just set heading
		b = 0.0f;
		h = atan2f(-matrix.z1(), matrix.x1());
	} else {
		// Compute heading from z1 and z3
		h = atan2f(matrix.x3(), matrix.z3());
		// Compute bank from x1 and y2
		b = atan2f(matrix.y1(), matrix.y2());
	}
	float toGradMult = (float) (180 / M_PI);
	return EulerAngles(h * toGradMult, p * toGradMult, b * toGradMult);
}

EulerAngles EulerAngles::fromObjectMatrix(const Matrix3D &matrix) {
	// We will compute the Euler angle values in radians and store them here:
	float h, p, b;

	// Extract pitch from y3, being careful for domain errors with asin().
	// We could have values slightly out of range due to floating point arithmetic
	float sp = -matrix.z2();

	if (sp <= -1.0f) {
		p = (float) (-M_PI / 2);
	} else if (sp >= 1.0f) {
		p = (float) (M_PI / 2);
	} else {
		p = (float) asin(sp);
	}

	// Check for the Gimbal lock case, giving a slight tolerance for numerical imprecision
	if (fabs(sp) > 0.9999f) {
		// We are looking straight up or down.
		// Slam bank to zero and just set heading
		b = 0.0f;
		h = atan2f(-matrix.z1(), matrix.x1());
	} else {
		// Compute heading from z1 and z3
		h = atan2f(matrix.x3(), matrix.z3());
		// Compute bank from x1 and y2
		b = atan2f(matrix.y1(), matrix.y2());
	}
	float toGradMult = (float) (180 / M_PI);
	return EulerAngles(h * toGradMult, p * toGradMult, b * toGradMult);
}

Quaternion EulerAngles::toUprightQuaternion() const {
	float h = (float) (_heading * M_PI / 180);
	float p = (float) (_pitch * M_PI / 180);
	float b = (float) (_bank * M_PI / 180);
	float ch = cosf(h / 2);
	float cp = cosf(p / 2);
	float cb = cosf(b / 2);
	float sh = sinf(h / 2);
	float sp = sinf(p / 2);
	float sb = sinf(b / 2);
	float w = ch * cp * cb + sh * sp * sb;
	float x = ch * sp * cb + sh * cp * sb;
	float y = sh * cp * cb - ch * sp * sb;
	float z = ch * cp * sb - sh * sp * cb;
	return Quaternion(w, x, y, z);
}

Quaternion EulerAngles::toObjectQuaternion() const {
	float h = (float) (_heading * M_PI / 180);
	float p = (float) (_pitch * M_PI / 180);
	float b = (float) (_bank * M_PI / 180);
	float ch = cosf(h / 2);
	float cp = cosf(p / 2);
	float cb = cosf(b / 2);
	float sh = sinf(h / 2);
	float sp = sinf(p / 2);
	float sb = sinf(b / 2);
	float w = ch * cp * cb + sh * sp * sb;
	float x = -ch * sp * cb - sh * cp * sb;
	float y = ch * sp * sb - sh * cp * cb;
	float z = sh * sp * cb - ch * cp * sb;
	return Quaternion(w, x, y, z);
}
