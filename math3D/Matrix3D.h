#ifndef __Matrix3D_H_
#define __Matrix3D_H_


#include "Vector3D.h"

class Vector3D;

class Matrix3D {

public:
    Matrix3D(double x1 = 1, double y1 = 0, double z1 = 0, double x2 = 0, double y2 = 1, double z2 = 0,
            double x3 = 0, double y3 = 0, double z3 = 1);

    const double *x1() const;
    void x1(double value);

    const double *x2() const;
    void x2(double value);

    const double *x3() const;
    void x3(double value);

    const double *y1() const;
    void y1(double value);

    const double *y2() const;
    void y2(double value);

    const double *y3() const;
    void y3(double value);

    const double *z1() const;
    void z1(double value);

    const double *z2() const;
    void z2(double value);

    const double *z3() const;
    void z3(double value);

    const double *determinant() const;

    void transpose();

    void identity();

    void multiplyByScalar(double scalar);

    void multiplyByMatrix(Matrix3D matrix);

    void rotateAboutX(float degrees);

    void rotateAboutY(float degrees);

    void rotateAboutZ(float degrees);

	void rotateAbout(Vector3D vector, float degrees);

	void scaleAlong(Vector3D vector, float factor);

    void inverse();

    Matrix3D clone() const;

    bool isClose(Matrix3D matrix, unsigned int precision) const;

    bool isEqual(Matrix3D matrix) const;

	bool isOrthogonal() const;

	void orthogonalize();

private:
    double _x1;
    double _x2;
    double _x3;
    double _y1;
    double _y2;
    double _y3;
    double _z1;
    double _z2;
    double _z3;
    mutable double _determinant;
    mutable bool _detNeedsUpdate = true;

    void _checkIfDeterminantNeedUpdateAfterRotation() const;

	void _checkUnitVector(Vector3D vector) const;

    void _checkNonZeroDeterminant() const;

    bool _areClose(double value1, double value2, int factor) const;

	void _performGrandSchmidtOrthogonalizingAlgorithm();

	void _performOrthogonalizingAlgorithm();
};


#endif //__Matrix3D_H_
