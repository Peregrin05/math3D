#include <math.h>
#include <stdexcept>
#include "Matrix3D.h"

static float ORTHOGONALIZE_FRACTION = 0.25;

Vector3D _deriveBasisVector(Vector3D const &v1, Vector3D const &v2, Vector3D const &v3) ;

Matrix3D::Matrix3D(float x1, float y1, float z1, float x2, float y2,
		float z2, float x3, float y3, float z3, float xt, float yt,
		float zt) :
        _x1(x1), _y1(y1), _z1(z1), _x2(x2), _y2(y2), _z2(z2), _x3(x3), _y3(y3), _z3(z3), _xt(xt), _yt(yt), _zt(zt),
		_w1(0), _w2(0), _w3(0), _wt(1) {};

Matrix3D::Matrix3D() :
		_x1(1), _y1(0), _z1(0), _x2(0), _y2(1), _z2(0), _x3(0), _y3(0), _z3(1), _xt(0), _yt(0), _zt(0), _w1(0),
		_w2(0), _w3(0), _wt(1) {};

Matrix3D Matrix3D::perspectiveProjection(float fovy, float aspectRatio, float near, float far) {
	Matrix3D matrix;
	float zoomY = 1 / tanf(fovy * (float) M_PI / 360);
	float zoomX = zoomY / aspectRatio;
	float z = (near + far) / (far - near);
	float zt = (-2 * near * far) / (far - near);
	matrix.x1(zoomX);
	matrix.y2(zoomY);
	matrix.z3(z);
	matrix.zt(zt);
	matrix.w3(1);
	matrix.wt(0);
	return matrix;
}

Matrix3D Matrix3D::orthographicProjection(float fovy, float aspectRatio, float near, float far) {
	Matrix3D matrix;
	float zoomY = 1 / tanf(fovy * (float) M_PI / 360);
	float zoomX = zoomY / aspectRatio;
	float z = 2 / (far - near);
	float zt = -(near + far) / (far - near);
	matrix.x1(zoomX);
	matrix.y2(zoomY);
	matrix.z3(z);
	matrix.zt(zt);
	return matrix;
}

float Matrix3D::x1() const {
    return _x1;
}

float Matrix3D::x2() const {
    return _x2;
}

float Matrix3D::x3() const {
    return _x3;
}

float Matrix3D::y1() const {
    return _y1;
}

float Matrix3D::y2() const {
    return _y2;
}

float Matrix3D::y3() const {
    return _y3;
}

float Matrix3D::z1() const {
    return _z1;
}

float Matrix3D::z2() const {
    return _z2;
}

float Matrix3D::z3() const {
    return _z3;
}

float Matrix3D::xt() const {
	return _xt;
}

float Matrix3D::yt() const {
	return _yt;
}

float Matrix3D::zt() const {
	return _zt;
}

float Matrix3D::w1() const {
	return _w1;
}

float Matrix3D::w2() const {
	return _w2;
}

float Matrix3D::w3() const {
	return _w3;
}

float  Matrix3D::wt() const {
	return _wt;
}

void Matrix3D::x1(float value) {
    _x1 = value;
    _detNeedsUpdate = true;
}

void Matrix3D::x2(float value) {
    _x2 = value;
    _detNeedsUpdate = true;
}

void Matrix3D::x3(float value) {
    _x3 = value;
    _detNeedsUpdate = true;
}

void Matrix3D::y1(float value) {
    _y1 = value;
    _detNeedsUpdate = true;
}

void Matrix3D::y2(float value) {
    _y2 = value;
    _detNeedsUpdate = true;
}

void Matrix3D::y3(float value) {
    _y3 = value;
    _detNeedsUpdate = true;
}

void Matrix3D::z1(float value) {
    _z1 = value;
    _detNeedsUpdate = true;
}

void Matrix3D::z2(float value) {
    _z2 = value;
    _detNeedsUpdate = true;
}

void Matrix3D::z3(float value) {
    _z3 = value;
    _detNeedsUpdate = true;
}

void Matrix3D::xt(float value) {
	_xt = value;
}

void Matrix3D::yt(float value) {
	_yt = value;
}

void Matrix3D::zt(float value) {
	_zt = value;
}

void Matrix3D::w1(float value) {
	_w1 = value;
}

void Matrix3D::w2(float value) {
	_w2 = value;
}

void Matrix3D::w3(float value) {
	_w3 = value;
}

void Matrix3D::wt(float value) {
	_wt = value;
}

float  Matrix3D::determinant() const {
    if (_detNeedsUpdate) {
        _determinant =
        _x1 * _y2 * _z3 + _y1 * _z2 * _x3 + _z1 * _x2 * _y3 - _x1 * _z2 * _y3 - _y1 * _x2 * _z3 - _z1 *
                _y2 * _x3;
        _detNeedsUpdate = false;
    }
    return _determinant;
}

void Matrix3D::transpose() {
    float temp = _x2;
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

void Matrix3D::multiplyByScalar(float scalar) {
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

void Matrix3D::multiplyByMatrix(Matrix3D const &matrix) {
	float  mx1 = matrix.x1();
	float  mx2 = matrix.x2();
	float  mx3 = matrix.x3();
	float  mxt = matrix.xt();
	float  newX1 = _x1 * mx1 + _y1 * mx2 + _z1 * mx3 + _w1 * mxt;
    float  newX2 = _x2 * mx1 + _y2 * mx2 + _z2 * mx3 + _w2 * mxt;
    float  newX3 = _x3 * mx1 + _y3 * mx2 + _z3 * mx3 + _w3 * mxt;
    float  newXT = _xt * mx1 + _yt * mx2 + _zt * mx3 + _wt * mxt;
	float  my1 = matrix.y1();
	float  my2 = matrix.y2();
	float  my3 = matrix.y3();
	float  myt = matrix.yt();
	float  newY1 = _x1 * my1 + _y1 * my2 + _z1 * my3 + _w1 * myt;
    float  newY2 = _x2 * my1 + _y2 * my2 + _z2 * my3 + _w2 * myt;
    float  newY3 = _x3 * my1 + _y3 * my2 + _z3 * my3 + _w3 * myt;
    float  newYT = _xt * my1 + _yt * my2 + _zt * my3 + _wt * myt;
	float  mz1 = matrix.z1();
	float  mz2 = matrix.z2();
	float  mz3 = matrix.z3();
	float  mzt = matrix.zt();
	float  newZ1 = _x1 * mz1 + _y1 * mz2 + _z1 * mz3 + _w1 * mzt;
    float  newZ2 = _x2 * mz1 + _y2 * mz2 + _z2 * mz3 + _w2 * mzt;
    float  newZ3 = _x3 * mz1 + _y3 * mz2 + _z3 * mz3 + _w3 * mzt;
    float  newZT = _xt * mz1 + _yt * mz2 + _zt * mz3 + _wt * mzt;
	float  mw1 = matrix.w1();
	float  mw2 = matrix.w2();
	float  mw3 = matrix.w3();
	float  mwt = matrix.wt();
	float  newW1 = _w1 = _x1 * mw1 + _y1 * mw2 + _z1 * mw3 + _w1 * mwt;
	float  newW2 = _w2 = _x2 * mw1 + _y2 * mw2 + _z2 * mw3 + _w2 * mwt;
	float  newW3 = _w3 = _x3 * mw1 + _y3 * mw2 + _z3 * mw3 + _w3 * mwt;
	float  newWT = _wt = _xt * mw1 + _yt * mw2 + _zt * mw3 + _wt * mwt;
	_x1 = newX1;
    _x2 = newX2;
    _x3 = newX3;
    _xt = newXT;
    _y1 = newY1;
    _y2 = newY2;
    _y3 = newY3;
    _yt = newYT;
	_z1 = newZ1;
	_z2 = newZ2;
	_z3 = newZ3;
	_zt = newZT;
	_w1 = newW1;
	_w2 = newW2;
	_w3 = newW3;
	_wt = newWT;
    _detNeedsUpdate = true;
}

void Matrix3D::rotateAboutX(float degrees) {
    float radians = (float) (degrees * M_PI / 180);
    float cosVal = cosf(radians);
    float sinVal = sinf(radians);
    _y2 = cosVal;
    _z2 = sinVal;
    _y3 = -sinVal;
    _z3 = cosVal;
    _checkIfDeterminantNeedUpdateAfterRotation();
}

void Matrix3D::rotateAboutY(float degrees) {
    float radians = (float) (degrees * M_PI / 180);
    float cosVal = cosf(radians);
    float sinVal = sinf(radians);
    _x1 = cosVal;
    _z1 = -sinVal;
    _x3 = sinVal;
    _z3 = cosVal;
    _checkIfDeterminantNeedUpdateAfterRotation();
}

void Matrix3D::rotateAboutZ(float degrees) {
    float radians = (float) (degrees * M_PI / 180);
    float cosVal = cosf(radians);
    float sinVal = sinf(radians);
    _x1 = cosVal;
    _y1 = sinVal;
    _x2 = -sinVal;
    _y2 = cosVal;
    _checkIfDeterminantNeedUpdateAfterRotation();
}

void Matrix3D::rotateAbout(Vector3D const &vector, float degrees) {
    _checkUnitVector(vector);
    float radians = (float) (degrees * M_PI / 180);
    float  vx = vector.x();
    float  vy = vector.y();
    float  vz = vector.z();
    float cosVal = cosf(radians);
    float sinVal = sinf(radians);
    float cosOp = 1 - cosVal;
    float vzSin = vz * sinVal;
    float vySin = vy * sinVal;
    float vxSin = vx * sinVal;
    _x1 = vx * vx * cosOp + cosVal;
    _y1 = vx * vy * cosOp + vzSin;
    _z1 = vx * vz * cosOp - vySin;
    _x2 = vx * vy * cosOp - vzSin;
    _y2 = vy * vy * cosOp + cosVal;
    _z2 = vy * vz * cosOp + vxSin;
    _x3 = vx * vz * cosOp + vySin;
    _y3 = vy * vz * cosOp - vxSin;
    _z3 = vz * vz * cosOp + cosVal;
    _checkIfDeterminantNeedUpdateAfterRotation();
}

void Matrix3D::scaleAlong(Vector3D const &vector, float factor) {
	scaleAlong(vector.x(), vector.y(), vector.z(), factor);
}

void Matrix3D::scaleAlong(float x, float y, float z, float factor) {
	_checkUnitVector(x, y, z);
	float facOp = factor - 1;
	float y1x2 = facOp * x * y;
	float z1x3 = facOp * x * z;
	float z2y3 = facOp * y * z;
	_x1 *= 1 + facOp * x * x;
	_y1 *= y1x2;
	_z1 *= z1x3;
	_x2 *= y1x2;
	_y2 *= 1 + facOp * y * y;
	_z2 *= z2y3;
	_x3 *= z1x3;
	_y3 *= z2y3;
	_z3 *= 1 + facOp * z * z;
	_detNeedsUpdate = true;
}

void Matrix3D::scale(float  scaleX, float  scaleY, float  scaleZ) {
	_x1 *= scaleX;
	_y1 *= scaleX;
	_z1 *= scaleX;
	_x2 *= scaleY;
	_y2 *= scaleY;
	_z2 *= scaleY;
	_x3 *= scaleZ;
	_y3 *= scaleZ;
	_z3 *= scaleZ;
	_detNeedsUpdate = true;
}

void Matrix3D::inverse() {
    _checkNonZeroDeterminant();
    float newX1 = _y2 * _z3 - _z2 * _y3; // cofactor 0, 0 +
    float newY1 = _z2 * _x3 - _x2 * _z3; // cofactor 0, 1 -
    float newZ1 = _x2 * _y3 - _y2 * _x3; // cofactor 0, 2 +
    float newX2 = _z1 * _y3 - _y1 * _z3; // cofactor 1, 0 -
    float newY2 = _x1 * _z3 - _z1 * _x3; // cofactor 1, 1 +
    float newZ2 = _y1 * _x3 - _x1 * _y3; // cofactor 1, 2 -
    float newX3 = _y1 * _z2 - _z1 * _y2; // cofactor 2, 0 +
    float newY3 = _z1 * _x2 - _x1 * _z2; // cofactor 2, 1 -
    float newZ3 = _x1 * _y2 - _y1 * _x2; // cofactor 2, 2 +
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

bool Matrix3D::isEqual(Matrix3D const &matrix) const {
    return matrix.x1() == _x1 && matrix.x2() == _x2 && matrix.x3() == _x3 && matrix.y1() == _y1 &&
            matrix.y2() == _y2 && matrix.y3() == _y3 && matrix.z1() == _z1 && matrix.z2() == _z2 &&
            matrix.z3() == _z3;
}

bool Matrix3D::isClose(Matrix3D const &matrix, unsigned int precision) const {
    int factor = (int) powf(10, (float) precision);
    return _areClose(matrix.x1(), _x1, factor) && _areClose(matrix.y1(), _y1, factor) && _areClose(matrix.z1(), _z1,
    factor) && _areClose(matrix.x2(), _x2, factor) && _areClose(matrix.y2(), _y2,
    factor) && _areClose(matrix.z2(), _z2, factor) && _areClose(matrix.x3(), _x3,
    factor) && _areClose(matrix.y3(), _y3, factor) && _areClose(matrix.z3(), _z3, factor);
}

void Matrix3D::translate(float xt, float yt, float zt) {
	_xt = xt;
	_yt = yt;
	_zt = zt;
}

void Matrix3D::transform(Vector3D &vector) const {
	multiplyVectorByMatrix(vector, *this);
}

Matrix3D Matrix3D::clone() const {
    Matrix3D matrix = Matrix3D(_x1, _y1, _z1, _x2, _y2, _z2, _x3, _y3, _z3, _xt, _yt, _zt);
    matrix.w1(_w1);
    matrix.w2(_w2);
    matrix.w3(_w3);
    matrix.wt(_wt);
    return matrix;
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
	_x1 = basis.x();
	_y1 = basis.y();
	_z1 = basis.z();
	basis = Vector3D(_x2, _y2, _z2);
	basis.normalize();
	_x2 = basis.x();
	_y2 = basis.y();
	_z2 = basis.z();
	basis = Vector3D(_x3, _y3, _z3);
	basis.normalize();
	_x3 = basis.x();
	_y3 = basis.y();
	_z3 = basis.z();
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
	_x1 = v1.x();
	_y1 = v1.y();
	_z1 = v1.z();

	float dp = Vector3D::dotProduct(v2, v1);
	Vector3D tempV2 = v2.clone();
	tempV2.multiplyByScalar(dp);
	v2.subtract(tempV2);
	_x2 = v2.x();
	_y2 = v2.y();
	_z2 = v2.z();

	Vector3D v3 = Vector3D::crossProduct(v1, v2);
	_x3 = v3.x();
	_y3 = v3.y();
	_z3 = v3.z();
}

void Matrix3D::_performOrthogonalizingAlgorithm() {
	Vector3D v1 = Vector3D(_x1, _y1, _z1);
	Vector3D v2 = Vector3D(_x2, _y2, _z2);
	Vector3D v3 = Vector3D(_x3, _y3, _z3);
	Vector3D basis1 = _deriveBasisVector(v1, v2, v3);
	Vector3D basis2 = _deriveBasisVector(v2, v1, v3);
	Vector3D basis3 = _deriveBasisVector(v3, v1, v2);
	_x1 = basis1.x();
	_y1 = basis1.y();
	_z1 = basis1.z();
	_x2 = basis2.x();
	_y2 = basis2.y();
	_z2 = basis2.z();
	_x3 = basis3.x();
	_y3 = basis3.y();
	_z3 = basis3.z();
}

Vector3D _deriveBasisVector(Vector3D const &v1, Vector3D const &v2, Vector3D const &v3) {
	float dp12 = Vector3D::dotProduct(v1, v2);
	float dp22 = Vector3D::dotProduct(v2, v2);
	float dp13 = Vector3D::dotProduct(v1, v3);
	float dp33 = Vector3D::dotProduct(v3, v3);
	Vector3D basis = v1.clone();
	Vector3D v2Clone = v2.clone();
	Vector3D v3Clone = v3.clone();
	v2Clone.multiplyByScalar(ORTHOGONALIZE_FRACTION * dp12 / dp22);
	v3Clone.multiplyByScalar(ORTHOGONALIZE_FRACTION * dp13 / dp33);
	basis.subtract(v2Clone);
	basis.subtract(v2Clone);
	return basis;
}

bool Matrix3D::_areClose(float value1, float value2, int factor) const {
    const float d1 = roundf(value1 * factor);
    const float d2 = roundf(value2 * factor);
    return d1 == d2;
}


void Matrix3D::_checkIfDeterminantNeedUpdateAfterRotation() const {
	if (!_detNeedsUpdate && _determinant != 1) {
		_detNeedsUpdate = true;
	}
}

void Matrix3D::_checkUnitVector(Vector3D const &vector) const {
	if (vector.length() != 1) {
		throw std::runtime_error("Given vector is not a unit vector.");
		// throw NotUnitVectorError();
	}
}

void Matrix3D::_checkUnitVector(float  x, float  y, float  z) const {
    if (sqrtf(x * x + y * y + z * z) != 1) {
		throw std::runtime_error("Given vector is no a unit vector.");
	}
}

void Matrix3D::_checkNonZeroDeterminant() const {
	if (determinant() == 0) {
		throw std::runtime_error("Matrix's determinant must not be 0.");
		// throw ZeroDeterminantMatrixError();
	}
}

void Matrix3D::multiplyVectorByMatrix(Vector3D &vector, const Matrix3D &matrix) {
	float x = vector.x();
	float y = vector.y();
	float z = vector.z();
	float newX = x * matrix.x1() + y * matrix.x2() + z * matrix.x3() + vector.w() * matrix.xt();
	float newY = x * matrix.y1() + y * matrix.y2() + z * matrix.y3() + vector.w() * matrix.yt();
	vector.z(x * matrix.z1() + y * matrix.z2() + z * matrix.z3() + vector.w() * matrix.zt());
	vector.x(newX);
	vector.y(newY);
}