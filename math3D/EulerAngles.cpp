#include <math.h>
#include "EulerAngles.h"

double _wrap180(double theta);

const static double pi = 180;
const static double pi2 = 360;

EulerAngles::EulerAngles(float const &heading, float const &pitch, float const &bank) : _heading(heading), _pitch(pitch), _bank(bank) {};

void EulerAngles::heading(double const &value) {
	_heading = value;
}

void EulerAngles::pitch(double const &value) {
	_pitch = value;
}

void EulerAngles::bank(double const &value) {
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

double _wrap180(double theta) {
	// Check if already in range
	if (theta > pi || theta <= -pi) {
		// out of range. Determine how many "revolutions" we need to add
		double revolutions = floor((theta + pi) / pi2);
		theta -= revolutions * pi2;
	}
	return theta;
}
