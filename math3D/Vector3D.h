#ifndef __Vector3D_H_
#define __Vector3D_H_


#include "Matrix3D.h"

class Matrix3D;

class Vector3D {
public:
    Vector3D(double x = 0, double y = 0, double z = 0, double w = 0);

    static double distanceBetween(Vector3D vector1, Vector3D vector2);

    static double dotProduct(Vector3D vector1, Vector3D vector2);

    static double angleBetween(Vector3D vector1, Vector3D vector2);

    static Vector3D crossProduct(Vector3D vector1, Vector3D vector2);

    const double *x() const;
    void x(const double value);

    const double *y() const;
    void y(const double value);

    const double *z() const;
    void z(const double value);

    const double *w() const;
    void w(const double value);

    const double *length() const;
    void length(double value);

    void multiplyByScalar(const double scalar);

    void normalize();

    void add(const Vector3D vector);

    void subtract(const Vector3D vector);

    bool isEqualTo(const Vector3D vector);

    void multiplyByMatrix(Matrix3D matrix);

    Vector3D clone();

private:
    double _x;
    double _y;
    double _z;
    double _w;
    mutable double _length;
    mutable bool _lengthNeedsUpdate = true;

    static double _squareRootOfSquareSums(const double a, const double b, const double c);

    void _updateLength() const;

    void _setLengthValue(const double value) const;

    bool _isZero();
};


#endif //__Vector3D_H_
