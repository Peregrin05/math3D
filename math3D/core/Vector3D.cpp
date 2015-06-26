#import <math.h>
#include <stdexcept>
#include "Matrix3D.h"

Vector3D::Vector3D(float x, float y, float z, float w) {
    _row[0] = x;
    _row[1] = y;
    _row[2] = z;
    _row[3] = w;
};

float Vector3D::distanceBetween(Vector3D const &vector1, Vector3D const &vector2) {
    float x(vector2.x() - vector1.x());
    float y(vector2.y() - vector1.y());
    float z(vector2.z() - vector1.z());
    return _squareRootOfSquareSums(x, y, z);
}

float Vector3D::dotProduct(Vector3D const &vector1, Vector3D const &vector2) {
    return vector2.x() * vector1.x() + vector2.y() * vector1.y() + vector2.z() * vector1.z();
}

float Vector3D::angleBetween(Vector3D const &vector1, Vector3D const &vector2) {
    float dotProd = dotProduct(vector1, vector2);
    float val = dotProd / vector1.length() / vector2.length();
    return (float) (acosf(val) * 180 / M_PI);
}

Vector3D Vector3D::crossProduct(Vector3D const &vector1, Vector3D const &vector2) {
    Vector3D resultVector;
    resultVector.x(vector1.y() * vector2.z() - vector1.z() * vector2.y());
    resultVector.y(vector1.z() * vector2.x() - vector1.x() * vector2.z());
    resultVector.z(vector1.x() * vector2.y() - vector1.y() * vector2.x());
    return resultVector;
}

float Vector3D::_squareRootOfSquareSums(float a, float b, float c) {
    return sqrtf(a * a + b * b + c * c);
}

void Vector3D::x(float value) {
    _row[0] = value;
    _lengthNeedsUpdate = true;
}

void Vector3D::y(float value) {
    _row[1] = value;
    _lengthNeedsUpdate = true;
}

void Vector3D::z(float value) {
    _row[2] = value;
    _lengthNeedsUpdate = true;
}

void Vector3D::w(float value) {
    _row[3] = value;
}

float Vector3D::length() const {
//    if (_lengthNeedsUpdate) {
        _updateLength();
//    }
    return _length;
}

void Vector3D::length(float value) {
    normalize();
    multiplyByScalar(value);
    _setLengthValue(value);
}

void Vector3D::add(Vector3D const &vector) {
    _row[0] += vector[0];
    _row[1] += vector[1];
    _row[2] += vector[2];
    _lengthNeedsUpdate = true;
}

void Vector3D::subtract(Vector3D const &vector) {
    _row[0] -= vector[0];
    _row[1] -= vector[1];
    _row[2] -= vector[2];
    _lengthNeedsUpdate = true;
}

void Vector3D::multiplyByMatrix(Matrix3D const &matrix) {
	Matrix3D::multiplyVectorByMatrix(*this, matrix);
}

Vector3D Vector3D::clone() const {
    Vector3D cloneVector(_row[0], _row[1], _row[2], _row[3]);
    if (!_lengthNeedsUpdate) {
        cloneVector._setLengthValue(_length);
    }
    return cloneVector;
}

bool Vector3D::isEqualTo(Vector3D const &vector) const {
    return vector.x() == _row[0] && vector.y() == _row[1] && vector.z() == _row[2] && vector.w() == _row[3];
}

void Vector3D::_updateLength() const {
    float value = _squareRootOfSquareSums(_row[0], _row[1], _row[2]);
    _setLengthValue(value);
}

void Vector3D::_setLengthValue(float value) const {
    _length = value;
    _lengthNeedsUpdate = false;
}

void Vector3D::multiplyByScalar(float scalar) {
    _row[0] *= scalar;
    _row[1] *= scalar;
    _row[2] *= scalar;
    _lengthNeedsUpdate = true;
}

void Vector3D::normalize() {
    if (_isZero()) {
		throw std::runtime_error("Forbidden operation: attempt to change the length or normalize a zero vector.");
    }
    multiplyByScalar(1 / length());
    _setLengthValue(1);
}

bool Vector3D::_isZero() {
    return _row[0] == 0 && _row[1] == 0 && _row[2] == 0;;
}

float Vector3D::operator*(Vector3D &v) const {
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

Vector3D Vector3D::operator*(float scalar) const {
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

const float& Vector3D::operator[](int index) const
{
    return _row[index];
}

float& Vector3D::operator[](int index)
{
    return _row[index];
}
