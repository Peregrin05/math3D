//
// Created by Islam Aliev on 20/07/14.
// Copyright (c) 2014 me. All rights reserved.
//

#include <math.h>
#include "Matrix3D.h"
#include "Vector3D.h"

static float const ORTHOGONALIZE_FRACTION = 0.25;

Vector3D _deriveBasisVector(Vector3D v1, Vector3D v2, Vector3D v3) ;

Matrix3D::Matrix3D(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3) :
        _x1(x1), _y1(y1), _z1(z1), _x2(x2), _y2(y2), _z2(z2), _x3(x3), _y3(y3), _z3(z3) {};

const double *Matrix3D::x1() const {
    return &_x1;
}

const double *Matrix3D::x2() const {
    return &_x2;
}

const double *Matrix3D::x3() const {
    return &_x3;
}

const double *Matrix3D::y1() const {
    return &_y1;
}

const double *Matrix3D::y2() const {
    return &_y2;
}

const double *Matrix3D::y3() const {
    return &_y3;
}

const double *Matrix3D::z1() const {
    return &_z1;
}

const double *Matrix3D::z2() const {
    return &_z2;
}

const double *Matrix3D::z3() const {
    return &_z3;
}

void Matrix3D::x1(double value) {
    _x1 = value;
    _detNeedsUpdate = true;
}

void Matrix3D::x2(double value) {
    _x2 = value;
    _detNeedsUpdate = true;
}

void Matrix3D::x3(double value) {
    _x3 = value;
    _detNeedsUpdate = true;
}

void Matrix3D::y1(double value) {
    _y1 = value;
    _detNeedsUpdate = true;
}

void Matrix3D::y2(double value) {
    _y2 = value;
    _detNeedsUpdate = true;
}

void Matrix3D::y3(double value) {
    _y3 = value;
    _detNeedsUpdate = true;
}

void Matrix3D::z1(double value) {
    _z1 = value;
    _detNeedsUpdate = true;
}

void Matrix3D::z2(double value) {
    _z2 = value;
    _detNeedsUpdate = true;
}

void Matrix3D::z3(double value) {
    _z3 = value;
    _detNeedsUpdate = true;
}

const double *Matrix3D::determinant() const {
    if (_detNeedsUpdate) {
        _determinant =
        _x1 * _y2 * _z3 + _y1 * _z2 * _x3 + _z1 * _x2 * _y3 - _x1 * _z2 * _y3 - _y1 * _x2 * _z3 - _z1 *
                _y2 * _x3;
        _detNeedsUpdate = false;
    }
    return &_determinant;
}

void Matrix3D::transpose() {
    double temp = _x2;
    _x2 = _y1;
    _y1 = temp;
    temp = _x3;
    _x3 = _z1;
    _z1 = temp;
    temp = _z2;
    _z2 = _y3;
    _y3 = temp;
}

void Matrix3D::identity() {
    _x1 = 1;
    _y1 = 0;
    _z1 = 0;
    _x2 = 0;
    _y2 = 1;
    _z2 = 0;
    _x3 = 0;
    _y3 = 0;
    _z3 = 1;
    _determinant = 1;
    _detNeedsUpdate = false;
}

void Matrix3D::multiplyByScalar(double scalar) {
    _x1 *= scalar;
    _y1 *= scalar;
    _z1 *= scalar;
    _x2 *= scalar;
    _y2 *= scalar;
    _z2 *= scalar;
    _x3 *= scalar;
    _y3 *= scalar;
    _z3 *= scalar;
    _detNeedsUpdate = true;
}

// TODO interface should be used instead
void Matrix3D::multiplyByMatrix(Matrix3D matrix) {
    double newX1 = _x1 * *matrix.x1() + _y1 * *matrix.x2() + _z1 * *matrix.x3();
    double newX2 = _x2 * *matrix.x1() + _y2 * *matrix.x2() + _z2 * *matrix.x3();
    double newX3 = _x3 * *matrix.x1() + _y3 * *matrix.x2() + _z3 * *matrix.x3();
    double newY1 = _x1 * *matrix.y1() + _y1 * *matrix.y2() + _z1 * *matrix.y3();
    double newY2 = _x2 * *matrix.y1() + _y2 * *matrix.y2() + _z2 * *matrix.y3();
    double newY3 = _x3 * *matrix.y1() + _y3 * *matrix.y2() + _z3 * *matrix.y3();
    _z1 = _x1 * *matrix.z1() + _y1 * *matrix.z2() + _z1 * *matrix.z3();
    _z2 = _x2 * *matrix.z1() + _y2 * *matrix.z2() + _z2 * *matrix.z3();
    _z3 = _x3 * *matrix.z1() + _y3 * *matrix.z2() + _z3 * *matrix.z3();
    _x1 = newX1;
    _x2 = newX2;
    _x3 = newX3;
    _y1 = newY1;
    _y2 = newY2;
    _y3 = newY3;
    _detNeedsUpdate = true;
}


void Matrix3D::rotateAboutX(float degrees) {
    double radians = degrees * M_PI / 180;
    double cosVal = cos(radians);
    double sinVal = sin(radians);
    _y2 = cosVal;
    _z2 = sinVal;
    _y3 = -sinVal;
    _z3 = cosVal;
    _checkIfDeterminantNeedUpdateAfterRotation();
}

void Matrix3D::rotateAboutY(float degrees) {
    double radians = degrees * M_PI / 180;
    double cosVal = cos(radians);
    double sinVal = sin(radians);
    _x1 = cosVal;
    _z1 = -sinVal;
    _x3 = sinVal;
    _z3 = cosVal;
    _checkIfDeterminantNeedUpdateAfterRotation();
}

void Matrix3D::rotateAboutZ(float degrees) {
    double radians = degrees * M_PI / 180;
    double cosVal = cos(radians);
    double sinVal = sin(radians);
    _x1 = cosVal;
    _y1 = sinVal;
    _x2 = -sinVal;
    _y2 = cosVal;
    _checkIfDeterminantNeedUpdateAfterRotation();
}

// TODO use interface
/*void Matrix3D::rotateAbout(Vector3D vector, float degrees) {
    _checkUnitVector(vector);
    double radians = degrees * M_PI / 180;
    const double *vx = vector.x();
    const double *vy = vector.y();
    const double *vz = vector.z();
    double cos = cos(radians);
    double sin = sin(radians);
    double cosOp = 1 - cos;
    double vzSin = *vz * sin;
    double vySin = *vy * sin;
    double vxSin = *vx * sin;
    _x1 = *vx * *vx * cosOp + cos;
    _y1 = *vx * *vy * cosOp + vzSin;
    _z1 = *vx * *vz * cosOp - vySin;
    _x2 = *vx * *vy * cosOp - vzSin;
    _y2 = *vy * *vy * cosOp + cos;
    _z2 = *vy * *vz * cosOp + vxSin;
    _x3 = *vx * *vz * cosOp + vySin;
    _y3 = *vy * *vz * cosOp - vxSin;
    _z3 = *vz * *vz * cosOp + cos;
    _checkIfDeterminantNeedUpdateAfterRotation();
}

void Matrix3D::scaleAlong(Vector3D vector, float factor) {
    _checkUnitVector(vector);
    const double *vx = vector.x();
    const double *vy = vector.y();
    const double *vz = vector.z();
    float facOp = factor - 1;
    double y1x2 = facOp * *vx * *vy;
    double z1x3 = facOp * *vx * *vz;
    double z2y3 = facOp * *vy * *vz;
    _x1 = 1 + facOp * *vx * *vx;
    _y1 = y1x2;
    _z1 = z1x3;
    _x2 = y1x2;
    _y2 = 1 + facOp * *vy * *vy;
    _z2 = z2y3;
    _x3 = z1x3;
    _y3 = z2y3;
    _z3 = 1 + facOp * *vz * *vz;
    _detNeedsUpdate = true;
}*/

void Matrix3D::inverse() {
    _checkNonZeroDeterminant();
    double newX1 = _y2 * _z3 - _z2 * _y3; // cofactor 0, 0 +
    double newY1 = _z2 * _x3 - _x2 * _z3; // cofactor 0, 1 -
    double newZ1 = _x2 * _y3 - _y2 * _x3; // cofactor 0, 2 +
    double newX2 = _z1 * _y3 - _y1 * _z3; // cofactor 1, 0 -
    double newY2 = _x1 * _z3 - _z1 * _x3; // cofactor 1, 1 +
    double newZ2 = _y1 * _x3 - _x1 * _y3; // cofactor 1, 2 -
    double newX3 = _y1 * _z2 - _z1 * _y2; // cofactor 2, 0 +
    double newY3 = _z1 * _x2 - _x1 * _z2; // cofactor 2, 1 -
    double newZ3 = _x1 * _y2 - _y1 * _x2; // cofactor 2, 2 +
    _x1 = newX1;
    _y1 = newY1;
    _z1 = newZ1;
    _x2 = newX2;
    _y2 = newY2;
    _z2 = newZ2;
    _x3 = newX3;
    _y3 = newY3;
    _z3 = newZ3;
    transpose();
    multiplyByScalar(1 / _determinant);
}

// TODO use interface
bool Matrix3D::isEqual(Matrix3D matrix) const {
    return *matrix.x1() == _x1 && *matrix.x2() == _x2 && *matrix.x3() == _x3 && *matrix.y1() == _y1 &&
            *matrix.y2() == _y2 && *matrix.y3() == _y3 && *matrix.z1() == _z1 && *matrix.z2() == _z2 &&
            *matrix.z3() == _z3;
}

// TODO why unsigned precision doesn't work?
bool Matrix3D::isClose(Matrix3D matrix, unsigned int precision) const {
    int factor = (int) pow(10, (double) precision);
    return _areClose(*matrix.x1(), _x1, factor) && _areClose(*matrix.y1(), _y1, factor) && _areClose(*matrix.z1(), _z1,
    factor) && _areClose(*matrix.x2(), _x2, factor) && _areClose(*matrix.y2(), _y2,
    factor) && _areClose(*matrix.z2(), _z2, factor) && _areClose(*matrix.x3(), _x3,
    factor) && _areClose(*matrix.y3(), _y3, factor) && _areClose(*matrix.z3(), _z3, factor);
}

Matrix3D Matrix3D::clone() const {
    return Matrix3D(_x1, _y1, _z1, _x2, _y2, _z2, _x3, _y3, _z3);
}

bool Matrix3D::_areClose(double value1, double value2, int factor) const {
    return round(value1 * factor) == round(value2 * factor);
}


void Matrix3D::_checkIfDeterminantNeedUpdateAfterRotation() const {
    if (!_detNeedsUpdate && _determinant != 1) {
        _detNeedsUpdate = true;
    }
}

/*void Matrix3D::_checkUnitVector(Vector3D vector) const {
    if (*vector.length() != 1) {
        // TODO throw exception
        // throw new NotUnitVectorError();
    }
}*/

void Matrix3D::_checkNonZeroDeterminant() const {
    if (*determinant() == 0) {
        // TODO throw exception
        // throw new ZeroDeterminantMatrixError();
    }
}

bool Matrix3D::isOrthogonal() const {
	Matrix3D transposedMatrix = clone();
	transposedMatrix.transpose();
	transposedMatrix.multiplyByMatrix(*this);
	return transposedMatrix.isClose(Matrix3D(), 5);
}

void Matrix3D::orthogonalize() {
	Vector3D basis = Vector3D(_x1, _y1, _z1);
	basis.normalize();
	_x1 = *basis.x();
	_y1 = *basis.y();
	_z1 = *basis.z();
	basis = Vector3D(_x2, _y2, _z2);
	basis.normalize();
	_x2 = *basis.x();
	_y2 = *basis.y();
	_z2 = *basis.z();
	basis = Vector3D(_x3, _y3, _z3);
	basis.normalize();
	_x3 = *basis.x();
	_y3 = *basis.y();
	_z3 = *basis.z();
	for (int i = 0; i < 5; i++) {
		_performOrthogonalizingAlgorithm();
	}
	_performGrandSchmidtOrthogonalizingAlgorithm();
	_detNeedsUpdate = true;
}

void Matrix3D::_performGrandSchmidtOrthogonalizingAlgorithm() {
	Vector3D v1 = Vector3D(_x1, _y1, _z1);
	Vector3D v2 = Vector3D(_x2, _y2, _z2);
	v1.normalize();
	v2.normalize();
	_x1 = *v1.x();
	_y1 = *v1.y();
	_z1 = *v1.z();

	double dp = Vector3D::dotProduct(v2, v1);
	Vector3D tempV2 = v2.clone();
	tempV2.multiplyByScalar(dp);
	v2.subtract(tempV2);
	_x2 = *v2.x();
	_y2 = *v2.y();
	_z2 = *v2.z();

	Vector3D v3 = Vector3D::crossProduct(v1, v2);
	_x3 = *v3.x();
	_y3 = *v3.y();
	_z3 = *v3.z();
}

void Matrix3D::_performOrthogonalizingAlgorithm() {
	Vector3D v1 = Vector3D(_x1, _y1, _z1);
	Vector3D v2 = Vector3D(_x2, _y2, _z2);
	Vector3D v3 = Vector3D(_x3, _y3, _z3);
	Vector3D basis1 = _deriveBasisVector(v1, v2, v3);
	Vector3D basis2 = _deriveBasisVector(v2, v1, v3);
	Vector3D basis3 = _deriveBasisVector(v3, v1, v2);
	_x1 = *basis1.x();
	_y1 = *basis1.y();
	_z1 = *basis1.z();
	_x2 = *basis2.x();
	_y2 = *basis2.y();
	_z2 = *basis2.z();
	_x3 = *basis3.x();
	_y3 = *basis3.y();
	_z3 = *basis3.z();
}

Vector3D _deriveBasisVector(Vector3D v1, Vector3D v2, Vector3D v3) {
	double dp12 = Vector3D::dotProduct(v1, v2);
	double dp22 = Vector3D::dotProduct(v2, v2);
	double dp13 = Vector3D::dotProduct(v1, v3);
	double dp33 = Vector3D::dotProduct(v3, v3);
	Vector3D basis = v1.clone();
	Vector3D v2Clone = v2.clone();
	Vector3D v3Clone = v3.clone();
	v2Clone.multiplyByScalar(ORTHOGONALIZE_FRACTION * dp12 / dp22);
	v3Clone.multiplyByScalar(ORTHOGONALIZE_FRACTION * dp13 / dp33);
	basis.subtract(v2Clone);
	basis.subtract(v2Clone);
	return basis;
}