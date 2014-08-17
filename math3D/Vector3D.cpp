#import <math.h>
#include "Vector3D.h"

Vector3D::Vector3D(double x, double y, double z, double w) : _x(x), _y(y), _z(z), _w(w) {
}

// TODO use interface
double Vector3D::distanceBetween(Vector3D vector1, Vector3D vector2) {
    const double x(*vector2.x() - *vector1.x());
    const double y(*vector2.y() - *vector1.y());
    const double z(*vector2.z() - *vector1.z());
    return _squareRootOfSquareSums(x, y, z);
}

// TODO use interface
double Vector3D::dotProduct(Vector3D vector1, Vector3D vector2) {
    return *vector2.x() * *vector1.x() + *vector2.y() * *vector1.y() + *vector2.z() * *vector1.z();
}

// TODO use interface
double Vector3D::angleBetween(Vector3D vector1, Vector3D vector2) {
    double dotProd = dotProduct(vector1, vector2);
    double val = dotProd / *vector1.length() / *vector2.length();
    return acos(val) * 180 / M_PI;
}

// TODO pass and return interface
Vector3D Vector3D::crossProduct(Vector3D vector1, Vector3D vector2) {
    Vector3D resultVector;
    resultVector.x(*vector1.y() * *vector2.z() - *vector1.z() * *vector2.y());
    resultVector.y(*vector1.z() * *vector2.x() - *vector1.x() * *vector2.z());
    resultVector.z(*vector1.x() * *vector2.y() - *vector1.y() * *vector2.x());
    return resultVector;
}

double Vector3D::_squareRootOfSquareSums(const double a, const double b, const double c) {
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

void Vector3D::x(const double value) {
    _x = value;
    _lengthNeedsUpdate = true;
}

void Vector3D::y(const double value) {
    _y = value;
    _lengthNeedsUpdate = true;
}

void Vector3D::z(const double value) {
    _z = value;
    _lengthNeedsUpdate = true;
}

void Vector3D::w(const double value) {
    _w = value;
    _lengthNeedsUpdate = true;
}

const double *Vector3D::length() const {
    if (_lengthNeedsUpdate) {
        _updateLength();
    }
    return &_length;
}

void Vector3D::length(double value) {
    normalize();
    multiplyByScalar(value);
    _setLengthValue(value);
}

void Vector3D::negate() {
    multiplyByScalar(-1);
}

// TODO should accept interface
void Vector3D::add(const Vector3D vector) {
    _x += *vector.x();
    _y += *vector.y();
    _z += *vector.z();
    _lengthNeedsUpdate = true;
}

// TODO should accept interface
void Vector3D::subtract(const Vector3D vector) {
    _x -= *vector.x();
    _y -= *vector.y();
    _z -= *vector.z();
    _lengthNeedsUpdate = true;
}

void Vector3D::multiplyByMatrix(Matrix3D matrix) {
    double newX = _x * *matrix.x1() + _y * *matrix.x2() + _z * *matrix.x3();
    double newY = _x * *matrix.y1() + _y * *matrix.y2() + _z * *matrix.y3();
    _z = _x * *matrix.z1() + _y * *matrix.z2() + _z * *matrix.z3();
    _x = newX;
    _y = newY;
    _lengthNeedsUpdate = true;
}

// TODO should return interface
Vector3D Vector3D::clone() {
    Vector3D cloneVector(_x, _y, _z, _w);
    if (!_lengthNeedsUpdate) {
        cloneVector._setLengthValue(_length);
    }
    return cloneVector;
}

bool Vector3D::isEqualTo(const Vector3D vector) {
    return *vector.x() == _x && *vector.y() == _y && *vector.z() == _z && *vector.w() == _w;
}

void Vector3D::_updateLength() const {
    const double value = _squareRootOfSquareSums(_x, _y, _z);
    _setLengthValue(value);
}

void Vector3D::_setLengthValue(const double value) const {
    _length = value;
    _lengthNeedsUpdate = false;
}

void Vector3D::multiplyByScalar(const double scalar) {
    _x *= scalar;
    _y *= scalar;
    _z *= scalar;
    _lengthNeedsUpdate = true;
}

void Vector3D::normalize() {
    if (_isZero()) {
        //throw new ("Forbidden operation: attempt to change the length or normalize a zero vector.")
        return;
    }
    multiplyByScalar(1 / *length());
    _setLengthValue(1);
}

bool Vector3D::_isZero() {
    return _x == 0 && _y == 0 && _z == 0;;
}
