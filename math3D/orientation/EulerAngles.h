#ifndef __EulerAngles_H_
#define __EulerAngles_H_


#include "../core/Matrix3D.h"
#include "Quaternion.h"

class Quaternion;

class EulerAngles {
public:
	static EulerAngles fromUprightMatrix(const Matrix3D &matrix);

	static EulerAngles fromObjectMatrix(const Matrix3D &matrix);

	EulerAngles(float heading = 0, float pitch = 0, float bank = 0);

	float heading() const {
		return _heading;
	}
	void heading(float value);

	float pitch() const {
		return _pitch;
	}
	void pitch(float value);

	float bank() const {
		return _bank;
	}
	void bank(float value);

	bool isCanonical() const;

	void canonize();

	Matrix3D toUprightMatrix() const;

	Matrix3D toObjectMatrix() const;

	Quaternion toUprightQuaternion() const;

	Quaternion toObjectQuaternion() const;

private:
    const static int HALF_CIRCLE = 180;
    const static int FULL_CIRCLE = 360;

    float _heading;
	float _pitch;
	float _bank;

    float _wrap180(float theta);
};


#endif //__EulerAngles_H_
