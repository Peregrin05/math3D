#ifndef __Vector3D_H_
#define __Vector3D_H_


#include "Matrix3D.h"

class Matrix3D;

class Vector3D {
public:
    Vector3D(double const &x = 0, double const &y = 0, double const &z = 0, double const &w = 1);

    static double distanceBetween(Vector3D const &vector1, Vector3D const &vector2);

    static double dotProduct(Vector3D const &vector1, Vector3D const &vector2);

    static double angleBetween(Vector3D const &vector1, Vector3D const &vector2);

    static Vector3D crossProduct(Vector3D const &vector1, Vector3D const &vector2);

    const double *x() const;
    void x(double const &value);

    const double *y() const;
    void y(double const &value);

    const double *z() const;
    void z(double const &value);

    const double *w() const;
    void w(double const &value);

    const double *length() const;
    void length(double const &value);

    void multiplyByScalar(double const &scalar);

    void normalize();

    void add(Vector3D const &vector);

    void subtract(Vector3D const &vector);

    bool isEqualTo(Vector3D const &vector);

    void multiplyByMatrix(Matrix3D const &matrix);

    Vector3D clone() const;

private:
    double _x;
    double _y;
    double _z;
    double _w;
    mutable double _length;
    mutable bool _lengthNeedsUpdate = true;

    static double _squareRootOfSquareSums(double const &a, double const &b, double const &c);

    void _updateLength() const;

    void _setLengthValue(double const &value) const;

    bool _isZero();
};


#endif //__Vector3D_H_
