#include <math.h>
#include "EulerAngles.h"

float _wrap180(float theta);

const static double pi = 180;
const static double pi2 = 360;

EulerAngles::EulerAngles(float const &heading, float const &pitch, float const &bank) : _heading(heading), _pitch(pitch), _bank(bank) {};

void EulerAngles::heading(float const &value) {
	_heading = value;
}

void EulerAngles::pitch(float const &value) {
	_pitch = value;
}

void EulerAngles::bank(float const &value) {
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
	if ((_pitch == 90 || _pitch == -90) && _bank != 0) {
		return false;
	}
	return true;
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

float _wrap180(float theta) {
	// Check if already in range
	if (theta > pi || theta <= -pi) {
		// out of range. Determine how many "revolutions" we need to add
		double revolutions = floor((theta + pi) / pi2);
		theta -= revolutions * pi2;
	}
	return theta;
}

Matrix3D EulerAngles::toUprightMatrix() {
	double h = _heading * M_PI / 180;
	double p = _heading * M_PI / 180;
	double b = _heading * M_PI / 180;

	double ch = cos(h);
	double sh = sin(h);
	double cp = cos(p);
	double sp = sin(p);
	double cb = cos(b);
	double sb = sin(b);

	double x1 = ch * cb + sh * sp * sb;
	double y1 = sb * cp;
	double z1 = -sh * cb + ch * sp * sb;
	double x2 = -ch * sb + sh * sp * cb;
	double y2 = cb * cp;
	double z2 = sb * sh + ch * sp * cb;
	double x3 = sh * cp;
	double y3 = -sp;
	double z3 = ch * cp;

	return Matrix3D(x1, y1, z1, x2, y2, z2, x3, y3, z3);
}

Matrix3D EulerAngles::toObjectMatrix() {
	double h = _heading * M_PI / 180;
	double p = _heading * M_PI / 180;
	double b = _heading * M_PI / 180;

	double ch = cos(h);
	double sh = sin(h);
	double cp = cos(p);
	double sp = sin(p);
	double cb = cos(b);
	double sb = sin(b);

	double x1 = ch * cb + sh * sp * sb;
	double y1 = -ch * sb + sh * sp * cb;
	double z1 = sh * cp;
	double x2 = sb * cp;
	double y2 = cb * cp;
	double z2 = -sp;
	double x3 = -sh * cb + ch * sp * sb;
	double y3 = sb *sh + sh * sp * cb;
	double z3 = ch * cp;

	return Matrix3D(x1, y1, z1, x2, y2, z2, x3, y3, z3);
}

EulerAngles EulerAngles::fromMatrix(Matrix3D &matrix) {
	float x1, y1, z1, y2, x3, y3, z3;

	// We will compute the Euler angle values in radians and store them here:
	float h, p, b;

	// Extract pitch from y3, being careful for domain errors with asin().
	// We could have values slightly out of range due to floating point arithmetic
	float sp = -y3;

	if (sp <= -1.0f) {
		p = -M_PI / 2;
	} else if (sp >= 1.0f) {
		p = M_PI / 2;
	} else {
		p = asin(sp);
	}

	// Check for the Gimbal lock case, giving a slight tolerance for numerical imprecision
	if (fabs(sp) > 0.9999f) {
		// We are looking straight up or down. 
		// Slam bank to zero and just set heading
		b = 0.0f;
		h = atan2(-z1, x1);
	} else {
		// Compute heading from z1 and z3
		h = atan2(x3, z3);
		// Compute bank from x1 and y2
		b = atan2(y1, y2);
	}
	return EulerAngles(h, p, b);
}

Quaternion EulerAngles::toUprightQuaternion() const {
	double h = _heading * M_PI / 180;
	double p = _pitch * M_PI / 180;
	double b = _bank * M_PI / 180;
	double ch = cos(h / 2);
	double cp = cos(p / 2);
	double cb = cos(b / 2);
	double sh = sin(h / 2);
	double sp = sin(p / 2);
	double sb = sin(b / 2);
	double w = ch * cp * cb + sh * sp * sb;
	double x = ch * sp * cb + sh * cp * sb;
	double y = sh * cp * cb - ch * sp * sb;
	double z = ch * cp * sb - sh * sp * cb;
	return Quaternion(w, x, y, z);
}

Quaternion EulerAngles::toObjectQuaternion() const {
	double h = _heading * M_PI / 180;
	double p = _pitch * M_PI / 180;
	double b = _bank * M_PI / 180;
	double ch = cos(h / 2);
	double cp = cos(p / 2);
	double cb = cos(b / 2);
	double sh = sin(h / 2);
	double sp = sin(p / 2);
	double sb = sin(b / 2);
	double w = ch * cp * cb + sh * sp * sb;
	double x = -ch * sp * cb - sh * cp * sb;
	double y = ch * sp * sb - sh * cp * cb;
	double z = sh * sp * cb - ch * cp * sb;
	return Quaternion(w, x, y, z);
}
