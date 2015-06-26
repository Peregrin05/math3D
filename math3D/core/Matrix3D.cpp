#include <math.h>
#include <stdexcept>
#include "Matrix3D.h"

static float ORTHOGONALIZE_FRACTION = 0.25;

Vector3D _deriveBasisVector(Vector3D const &v1, Vector3D const &v2, Vector3D const &v3) ;

Matrix3D::Matrix3D(float x1, float y1, float z1, float x2, float y2,
		float z2, float x3, float y3, float z3, float xt, float yt,
		float zt)
{
    _rows[0] = Vector3D(x1, y1, z1);
    _rows[1] = Vector3D(x2, y2, z2);
    _rows[2] = Vector3D(x3, y3, z3);
    _rows[3] = Vector3D(xt, yt, zt);
}

Matrix3D::Matrix3D()
{
    _rows[0] = Vector3D(1, 0, 0);
    _rows[1] = Vector3D(0, 1, 0);
    _rows[2] = Vector3D(0, 0, 1);
}

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

void Matrix3D::x1(float value) {
    _rows[0][0] = value;
    _detNeedsUpdate = true;
}

void Matrix3D::x2(float value) {
    _rows[1][0] = value;
    _detNeedsUpdate = true;
}

void Matrix3D::x3(float value) {
    _rows[2][0] = value;
    _detNeedsUpdate = true;
}

void Matrix3D::y1(float value) {
    _rows[0][1] = value;
    _detNeedsUpdate = true;
}

void Matrix3D::y2(float value) {
    _rows[1][1] = value;
    _detNeedsUpdate = true;
}

void Matrix3D::y3(float value) {
    _rows[2][1] = value;
    _detNeedsUpdate = true;
}

void Matrix3D::z1(float value) {
    _rows[0][2] = value;
    _detNeedsUpdate = true;
}

void Matrix3D::z2(float value) {
    _rows[1][2] = value;
    _detNeedsUpdate = true;
}

void Matrix3D::z3(float value) {
    _rows[2][2] = value;
    _detNeedsUpdate = true;
}

void Matrix3D::xt(float value) {
    _rows[3][0] = value;
}

void Matrix3D::yt(float value) {
    _rows[3][1] = value;
}

void Matrix3D::zt(float value) {
    _rows[3][2] = value;
}

void Matrix3D::w1(float value) {
    _rows[0][3] = value;
}

void Matrix3D::w2(float value) {
    _rows[1][3] = value;
}

void Matrix3D::w3(float value) {
    _rows[2][3] = value;
}

void Matrix3D::wt(float value) {
    _rows[3][3] = value;
}

float  Matrix3D::determinant() const {
    if (_detNeedsUpdate) {
        _determinant =
        _rows[0][0] * _rows[1][1] * _rows[2][2] + _rows[0][1] * _rows[1][2] * _rows[2][0] + _rows[0][2] * _rows[1][0] *
                _rows[2][1] - _rows[0][0] * _rows[1][2] * _rows[2][1] - _rows[0][1] * _rows[1][0] *
                _rows[2][2] - _rows[0][2] * _rows[1][1] * _rows[2][0];
        _detNeedsUpdate = false;
    }
    return _determinant;
}

void Matrix3D::transpose() {
    float temp = _rows[1][0];
    _rows[1][0] = _rows[0][1];
    _rows[0][1] = temp;
    temp = _rows[2][0];
    _rows[2][0] = _rows[0][2];
    _rows[0][2] = temp;
    temp = _rows[1][2];
    _rows[1][2] = _rows[2][1];
    _rows[2][1] = temp;
}

void Matrix3D::identity() {
    _rows[0][0] = 1;
    _rows[0][1] = 0;
    _rows[0][2] = 0;
    _rows[1][0] = 0;
    _rows[1][1] = 1;
    _rows[1][2] = 0;
    _rows[2][0] = 0;
    _rows[2][1] = 0;
    _rows[2][2] = 1;
    _determinant = 1;
    _detNeedsUpdate = false;
}

void Matrix3D::multiplyByScalar(float scalar) {
    _rows[0][0] *= scalar;
    _rows[0][1] *= scalar;
    _rows[0][2] *= scalar;
    _rows[1][0] *= scalar;
    _rows[1][1] *= scalar;
    _rows[1][2] *= scalar;
    _rows[2][0] *= scalar;
    _rows[2][1] *= scalar;
    _rows[2][2] *= scalar;
    _detNeedsUpdate = true;
}

void Matrix3D::multiplyByMatrix(Matrix3D const & m) {
	float  newX1 = _rows[0][0] * m[0][0] + _rows[0][1] * m[1][0] + _rows[0][2] * m[2][0] + _rows[0][3] * m[3][0];
    float  newX2 = _rows[1][0] * m[0][0] + _rows[1][1] * m[1][0] + _rows[1][2] * m[2][0] + _rows[1][3] * m[3][0];
    float  newX3 = _rows[2][0] * m[0][0] + _rows[2][1] * m[1][0] + _rows[2][2] * m[2][0] + _rows[2][3] * m[3][0];
    float  newXT = _rows[3][0] * m[0][0] + _rows[3][1] * m[1][0] + _rows[3][2] * m[2][0] + _rows[3][3] * m[3][0];
	float  newY1 = _rows[0][0] * m[0][1] + _rows[0][1] * m[1][1] + _rows[0][2] * m[2][1] + _rows[0][3] * m[3][1];
    float  newY2 = _rows[1][0] * m[0][1] + _rows[1][1] * m[1][1] + _rows[1][2] * m[2][1] + _rows[1][3] * m[3][1];
    float  newY3 = _rows[2][0] * m[0][1] + _rows[2][1] * m[1][1] + _rows[2][2] * m[2][1] + _rows[2][3] * m[3][1];
    float  newYT = _rows[3][0] * m[0][1] + _rows[3][1] * m[1][1] + _rows[3][2] * m[2][1] + _rows[3][3] * m[3][1];
	float  newZ1 = _rows[0][0] * m[0][2] + _rows[0][1] * m[1][2] + _rows[0][2] * m[2][2] + _rows[0][3] * m[3][2];
    float  newZ2 = _rows[1][0] * m[0][2] + _rows[1][1] * m[1][2] + _rows[1][2] * m[2][2] + _rows[1][3] * m[3][2];
    float  newZ3 = _rows[2][0] * m[0][2] + _rows[2][1] * m[1][2] + _rows[2][2] * m[2][2] + _rows[2][3] * m[3][2];
    float  newZT = _rows[3][0] * m[0][2] + _rows[3][1] * m[1][2] + _rows[3][2] * m[2][2] + _rows[3][3] * m[3][2];
	float  newW1 = _rows[0][3] = _rows[0][0] * m[0][3] + _rows[0][1] * m[1][3] + _rows[0][2] * m[2][3] + _rows[0][3] * m[3][3];
	float  newW2 = _rows[1][3] = _rows[1][0] * m[0][3] + _rows[1][1] * m[1][3] + _rows[1][2] * m[2][3] + _rows[1][3] * m[3][3];
	float  newW3 = _rows[2][3] = _rows[2][0] * m[0][3] + _rows[2][1] * m[1][3] + _rows[2][2] * m[2][3] + _rows[2][3] * m[3][3];
	float  newWT = _rows[3][3] = _rows[3][0] * m[0][3] + _rows[3][1] * m[1][3] + _rows[3][2] * m[2][3] + _rows[3][3] * m[3][3];
	_rows[0][0] = newX1;
    _rows[1][0] = newX2;
    _rows[2][0] = newX3;
    _rows[3][0] = newXT;
    _rows[0][1] = newY1;
    _rows[1][1] = newY2;
    _rows[2][1] = newY3;
    _rows[3][1] = newYT;
	_rows[0][2] = newZ1;
	_rows[1][2] = newZ2;
	_rows[2][2] = newZ3;
	_rows[3][2] = newZT;
	_rows[0][3] = newW1;
	_rows[1][3] = newW2;
	_rows[2][3] = newW3;
	_rows[3][3] = newWT;
    _detNeedsUpdate = true;
}

void Matrix3D::rotateAboutX(float degrees) {
    float radians = (float) (degrees * M_PI / 180);
    float cosVal = cosf(radians);
    float sinVal = sinf(radians);
    _rows[1][1] = cosVal;
    _rows[1][2] = sinVal;
    _rows[2][1] = -sinVal;
    _rows[2][2] = cosVal;
    _checkIfDeterminantNeedUpdateAfterRotation();
}

void Matrix3D::rotateAboutY(float degrees) {
    float radians = (float) (degrees * M_PI / 180);
    float cosVal = cosf(radians);
    float sinVal = sinf(radians);
    _rows[0][0] = cosVal;
    _rows[0][2] = -sinVal;
    _rows[2][0] = sinVal;
    _rows[2][2] = cosVal;
    _checkIfDeterminantNeedUpdateAfterRotation();
}

void Matrix3D::rotateAboutZ(float degrees) {
    float radians = (float) (degrees * M_PI / 180);
    float cosVal = cosf(radians);
    float sinVal = sinf(radians);
    _rows[0][0] = cosVal;
    _rows[0][1] = sinVal;
    _rows[1][0] = -sinVal;
    _rows[1][1] = cosVal;
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
    _rows[0][0] = vx * vx * cosOp + cosVal;
    _rows[0][1] = vx * vy * cosOp + vzSin;
    _rows[0][2] = vx * vz * cosOp - vySin;
    _rows[1][0] = vx * vy * cosOp - vzSin;
    _rows[1][1] = vy * vy * cosOp + cosVal;
    _rows[1][2] = vy * vz * cosOp + vxSin;
    _rows[2][0] = vx * vz * cosOp + vySin;
    _rows[2][1] = vy * vz * cosOp - vxSin;
    _rows[2][2] = vz * vz * cosOp + cosVal;
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
	_rows[0][0] *= 1 + facOp * x * x;
	_rows[0][1] *= y1x2;
	_rows[0][2] *= z1x3;
	_rows[1][0] *= y1x2;
	_rows[1][1] *= 1 + facOp * y * y;
	_rows[1][2] *= z2y3;
	_rows[2][0] *= z1x3;
	_rows[2][1] *= z2y3;
	_rows[2][2] *= 1 + facOp * z * z;
	_detNeedsUpdate = true;
}

void Matrix3D::scale(float  scaleX, float  scaleY, float  scaleZ) {
	_rows[0][0] *= scaleX;
	_rows[0][1] *= scaleX;
	_rows[0][2] *= scaleX;
	_rows[1][0] *= scaleY;
	_rows[1][1] *= scaleY;
	_rows[1][2] *= scaleY;
	_rows[2][0] *= scaleZ;
	_rows[2][1] *= scaleZ;
	_rows[2][2] *= scaleZ;
	_detNeedsUpdate = true;
}

void Matrix3D::inverse() {
    _checkNonZeroDeterminant();
    float newX1 = _rows[1][1] * _rows[2][2] - _rows[1][2] * _rows[2][1]; // cofactor 0, 0 +
    float newY1 = _rows[1][2] * _rows[2][0] - _rows[1][0] * _rows[2][2]; // cofactor 0, 1 -
    float newZ1 = _rows[1][0] * _rows[2][1] - _rows[1][1] * _rows[2][0]; // cofactor 0, 2 +
    float newX2 = _rows[0][2] * _rows[2][1] - _rows[0][1] * _rows[2][2]; // cofactor 1, 0 -
    float newY2 = _rows[0][0] * _rows[2][2] - _rows[0][2] * _rows[2][0]; // cofactor 1, 1 +
    float newZ2 = _rows[0][1] * _rows[2][0] - _rows[0][0] * _rows[2][1]; // cofactor 1, 2 -
    float newX3 = _rows[0][1] * _rows[1][2] - _rows[0][2] * _rows[1][1]; // cofactor 2, 0 +
    float newY3 = _rows[0][2] * _rows[1][0] - _rows[0][0] * _rows[1][2]; // cofactor 2, 1 -
    float newZ3 = _rows[0][0] * _rows[1][1] - _rows[0][1] * _rows[1][0]; // cofactor 2, 2 +
    _rows[0][0] = newX1;
    _rows[0][1] = newY1;
    _rows[0][2] = newZ1;
    _rows[1][0] = newX2;
    _rows[1][1] = newY2;
    _rows[1][2] = newZ2;
    _rows[2][0] = newX3;
    _rows[2][1] = newY3;
    _rows[2][2] = newZ3;
    transpose();
    multiplyByScalar(1 / _determinant);
}

bool Matrix3D::isEqual(Matrix3D const &matrix) const {
    return matrix.x1() == _rows[0][0] && matrix.x2() == _rows[1][0] && matrix.x3() == _rows[2][0] && matrix.y1() == _rows[0][1] &&
            matrix.y2() == _rows[1][1] && matrix.y3() == _rows[2][1] && matrix.z1() == _rows[0][2] && matrix.z2() == _rows[1][2] &&
            matrix.z3() == _rows[2][2];
}

bool Matrix3D::isClose(Matrix3D const &matrix, unsigned int precision) const {
    int factor = (int) powf(10, (float) precision);
    return _areClose(matrix.x1(), _rows[0][0], factor) && _areClose(matrix.y1(), _rows[0][1], factor) && _areClose(matrix.z1(), _rows[0][2],
    factor) && _areClose(matrix.x2(), _rows[1][0], factor) && _areClose(matrix.y2(), _rows[1][1],
    factor) && _areClose(matrix.z2(), _rows[1][2], factor) && _areClose(matrix.x3(), _rows[2][0],
    factor) && _areClose(matrix.y3(), _rows[2][1], factor) && _areClose(matrix.z3(), _rows[2][2], factor);
}

void Matrix3D::translate(float xt, float yt, float zt) {
	_rows[3][0] = xt;
	_rows[3][1] = yt;
	_rows[3][2] = zt;
}

void Matrix3D::transform(Vector3D &vector) const {
	multiplyVectorByMatrix(vector, *this);
}

Matrix3D Matrix3D::clone() const {
    Matrix3D matrix = Matrix3D(_rows[0][0], _rows[0][1], _rows[0][2], _rows[1][0], _rows[1][1], _rows[1][2],
            _rows[2][0], _rows[2][1], _rows[2][2], _rows[3][0], _rows[3][1], _rows[3][2]);
    matrix.w1(_rows[0][3]);
    matrix.w2(_rows[1][3]);
    matrix.w3(_rows[2][3]);
    matrix.wt(_rows[3][3]);
    return matrix;
}

bool Matrix3D::isOrthogonal() const {
	Matrix3D transposedMatrix = clone();
	transposedMatrix.transpose();
	transposedMatrix.multiplyByMatrix(*this);
	return transposedMatrix.isClose(Matrix3D(), 5);
}

void Matrix3D::orthogonalize() {
	Vector3D basis = Vector3D(_rows[0][0], _rows[0][1], _rows[0][2]);
	basis.normalize();
	_rows[0][0] = basis.x();
	_rows[0][1] = basis.y();
	_rows[0][2] = basis.z();
	basis = Vector3D(_rows[1][0], _rows[1][1], _rows[1][2]);
	basis.normalize();
	_rows[1][0] = basis.x();
	_rows[1][1] = basis.y();
	_rows[1][2] = basis.z();
	basis = Vector3D(_rows[2][0], _rows[2][1], _rows[2][2]);
	basis.normalize();
	_rows[2][0] = basis.x();
	_rows[2][1] = basis.y();
	_rows[2][2] = basis.z();
	for (int i = 0; i < 5; i++) {
		_performOrthogonalizingAlgorithm();
	}
	_performGrandSchmidtOrthogonalizingAlgorithm();
	_detNeedsUpdate = true;
}

void Matrix3D::_performGrandSchmidtOrthogonalizingAlgorithm() {
	Vector3D v1 = Vector3D(_rows[0][0], _rows[0][1], _rows[0][2]);
	Vector3D v2 = Vector3D(_rows[1][0], _rows[1][1], _rows[1][2]);
	v1.normalize();
	v2.normalize();
	_rows[0][0] = v1.x();
	_rows[0][1] = v1.y();
	_rows[0][2] = v1.z();

	float dp = Vector3D::dotProduct(v2, v1);
	Vector3D tempV2 = v2.clone();
	tempV2.multiplyByScalar(dp);
	v2.subtract(tempV2);
	_rows[1][0] = v2.x();
	_rows[1][1] = v2.y();
	_rows[1][2] = v2.z();

	Vector3D v3 = Vector3D::crossProduct(v1, v2);
	_rows[2][0] = v3.x();
	_rows[2][1] = v3.y();
	_rows[2][2] = v3.z();
}

void Matrix3D::_performOrthogonalizingAlgorithm() {
	Vector3D v1 = Vector3D(_rows[0][0], _rows[0][1], _rows[0][2]);
	Vector3D v2 = Vector3D(_rows[1][0], _rows[1][1], _rows[1][2]);
	Vector3D v3 = Vector3D(_rows[2][0], _rows[2][1], _rows[2][2]);
	Vector3D basis1 = _deriveBasisVector(v1, v2, v3);
	Vector3D basis2 = _deriveBasisVector(v2, v1, v3);
	Vector3D basis3 = _deriveBasisVector(v3, v1, v2);
	_rows[0][0] = basis1.x();
	_rows[0][1] = basis1.y();
	_rows[0][2] = basis1.z();
	_rows[1][0] = basis2.x();
	_rows[1][1] = basis2.y();
	_rows[1][2] = basis2.z();
	_rows[2][0] = basis3.x();
	_rows[2][1] = basis3.y();
	_rows[2][2] = basis3.z();
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
    float zt = matrix.zt();
    vector.z(x * matrix.z1() + y * matrix.z2() + z * matrix.z3() + vector.w() * zt);
	vector.x(newX);
	vector.y(newY);
}

Vector3D& Matrix3D::operator[](int index)
{
    return _rows[index];
}

const Vector3D& Matrix3D::operator[](int index) const
{
    return _rows[index];
}