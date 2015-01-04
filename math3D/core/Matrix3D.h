#ifndef __Matrix3D_H_
#define __Matrix3D_H_


#include "Vector3D.h"

class Vector3D;

class Matrix3D {

public:
    explicit Matrix3D(double const &x1 = 1, double const &y1 = 0, double const &z1 = 0, double const &x2 = 0,
			double const &y2 = 1, double const &z2 = 0, double const &x3 = 0, double const &y3 = 0,
			double const &z3 = 1, double const &xt = 0, double const &yt = 0, double const &zt = 0);

	static void multiplyVectorByMatrix(Vector3D &vector, const Matrix3D &matrix);

    const double *x1() const;
    void x1(double const &value);

    const double *x2() const;
    void x2(double const &value);

    const double *x3() const;
    void x3(double const &value);

    const double *y1() const;
    void y1(double const &value);

    const double *y2() const;
    void y2(double const &value);

    const double *y3() const;
    void y3(double const &value);

    const double *z1() const;
    void z1(double const &value);

    const double *z2() const;
    void z2(double const &value);

    const double *z3() const;
    void z3(double const &value);

	const double *xt() const;
	void xt(double const &value);

	const double *yt() const;
	void yt(double const &value);

	const double *zt() const;
	void zt(double const &value);

    const double *determinant() const;

    void transpose();

    void identity();

    void multiplyByScalar(double const &scalar);

    void multiplyByMatrix(Matrix3D const &matrix);

    void rotateAboutX(float const &degrees);

    void rotateAboutY(float const &degrees);

    void rotateAboutZ(float const &degrees);

	void rotateAbout(Vector3D const &vector, float const &degrees);

	void scaleAlong(Vector3D const &vector, float const &factor);
	void scaleAlong(const double &x, const double &y, const double &z, float const &factor);

	void scale(const double &scaleX, const double &scaleY, const double &scaleZ);

    void inverse();

    Matrix3D clone() const;

    bool isClose(Matrix3D const &matrix, unsigned int const &precision) const;

    bool isEqual(Matrix3D const &matrix) const;

	bool isOrthogonal() const;

	void orthogonalize();

	void translate(double const &xt, double const &yt, double const &zt);

	void transform(Vector3D &vector) const;

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
	double _xt;
	double _yt;
	double _zt;
    mutable double _determinant;
    mutable bool _detNeedsUpdate = true;

    void _checkIfDeterminantNeedUpdateAfterRotation() const;

	void _checkUnitVector(Vector3D const &vector) const;
	void _checkUnitVector(const double &x, const double &y, const double &z) const;

    void _checkNonZeroDeterminant() const;

    bool _areClose(double const &value1, double const &value2, int const &factor) const;

	void _performGrandSchmidtOrthogonalizingAlgorithm();

	void _performOrthogonalizingAlgorithm();
};


#endif //__Matrix3D_H_
