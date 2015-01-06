#import <math.h>
#include <stdexcept>
#include "Vector3D.h"

Vector3D::Vector3D(double const &x, double const &y, double const &z, double const &w) : _x(x), _y(y), _z(z), _w(w) {
}

// TODO use interface
double Vector3D::distanceBetween(Vector3D const &vector1, Vector3D const &vector2) {
    const double x(*vector2.x() - *vector1.x());
    const double y(*vector2.y() - *vector1.y());
    const double z(*vector2.z() - *vector1.z());
    return _squareRootOfSquareSums(x, y, z);
}

// TODO use interface
double Vector3D::dotProduct(Vector3D const &vector1, Vector3D const &vector2) {
    return *vector2.x() * *vector1.x() + *vector2.y() * *vector1.y() + *vector2.z() * *vector1.z();
}

// TODO use interface
double Vector3D::angleBetween(Vector3D const &vector1, Vector3D const &vector2) {
    double dotProd = dotProduct(vector1, vector2);
    double val = dotProd / *vector1.length() / *vector2.length();
    return acos(val) * 180 / M_PI;
}

// TODO pass and return interface
Vector3D Vector3D::crossProduct(Vector3D const &vector1, Vector3D const &vector2) {
    Vector3D resultVector;
    resultVector.x(*vector1.y() * *vector2.z() - *vector1.z() * *vector2.y());
    resultVector.y(*vector1.z() * *vector2.x() - *vector1.x() * *vector2.z());
    resultVector.z(*vector1.x() * *vector2.y() - *vector1.y() * *vector2.x());
    return resultVector;
}

double Vector3D::_squareRootOfSquareSums(double const &a, double const &b, double const &c) {
    return sqrt(a * a + b * b + c * c);
}

const double *Vector3D::x() const {
    return &_x;
}

const double *Vector3D::y() const {
    return &_y;
}

const double *Vector3D::z() const {
    return &_z;
}

const double *Vector3D::w() const {
    return &_w;
}

void Vector3D::x(double const &value) {
    _x = value;
    _lengthNeedsUpdate = true;
}

void Vector3D::y(double const &value) {
    _y = value;
    _lengthNeedsUpdate = true;
}

void Vector3D::z(double const &value) {
    _z = value;
    _lengthNeedsUpdate = true;
}

void Vector3D::w(double const &value) {
    _w = value;
}

const double *Vector3D::length() const {
    if (_lengthNeedsUpdate) {
        _updateLength();
    }
    return &_length;
}

void Vector3D::length(double const &value) {
    normalize();
    multiplyByScalar(value);
    _setLengthValue(value);
}

// TODO should accept interface
void Vector3D::add(Vector3D const &vector) {
    _x += *vector.x();
    _y += *vector.y();
    _z += *vector.z();
    _lengthNeedsUpdate = true;
}

// TODO should accept interface
void Vector3D::subtract(Vector3D const &vector) {
    _x -= *vector.x();
    _y -= *vector.y();
    _z -= *vector.z();
    _lengthNeedsUpdate = true;
}

void Vector3D::multiplyByMatrix(Matrix3D const &matrix) {
	Matrix3D::multiplyVectorByMatrix(*this, matrix);
}

// TODO should return interface
Vector3D Vector3D::clone() const {
    Vector3D cloneVector(_x, _y, _z, _w);
    if (!_lengthNeedsUpdate) {
        cloneVector._setLengthValue(_length);
    }
    return cloneVector;
}

bool Vector3D::isEqualTo(Vector3D const &vector) const {
    return *vector.x() == _x && *vector.y() == _y && *vector.z() == _z && *vector.w() == _w;
}

void Vector3D::_updateLength() const {
    const double value = _squareRootOfSquareSums(_x, _y, _z);
    _setLengthValue(value);
}

void Vector3D::_setLengthValue(double const &value) const {
    _length = value;
    _lengthNeedsUpdate = false;
}

void Vector3D::multiplyByScalar(double const &scalar) {
    _x *= scalar;
    _y *= scalar;
    _z *= scalar;
    _lengthNeedsUpdate = true;
}

void Vector3D::normalize() {
    if (_isZero()) {
		throw std::runtime_error("Forbidden operation: attempt to change the length or normalize a zero vector.");
    }
    multiplyByScalar(1 / *length());
    _setLengthValue(1);
}

bool Vector3D::_isZero() {
    return _x == 0 && _y == 0 && _z == 0;;
}

double Vector3D::operator*(Vector3D &v) const {
    return dotProduct(*this, v);
}

Vector3D Vector3D::operator+(Vector3D &v) const {
    Vector3D resultVector = *this;
    resultVector.add(v);
    return resultVector;
}

Vector3D Vector3D::operator/(Vector3D &v) const {
    return Vector3D::crossProduct(*this, v);
}

Vector3D Vector3D::operator*(double &scalar) const {
    Vector3D resultVector = *this;
    resultVector.multiplyByScalar(scalar);
    return resultVector;
}

Vector3D Vector3D::operator-(Vector3D &v) const {
    Vector3D resultVector = *this;
    resultVector.subtract(v);
    return resultVector;
}

bool Vector3D::operator==(Vector3D &v) const {
    return isEqualTo(v);
}

Vector3D Vector3D::operator*(Matrix3D &m) const {
    Vector3D resultVector = *this;
    resultVector.multiplyByMatrix(m);
    return resultVector;
}
