#ifndef __Matrix3D_H_
#define __Matrix3D_H_


#include "Vector3D.h"

class Vector3D;

class Matrix3D {

public:
    explicit Matrix3D(float x1, float y1 = 0, float z1 = 0, float x2 = 0,
			float y2 = 1, float z2 = 0, float x3 = 0, float y3 = 0,
			float z3 = 1, float xt = 0, float yt = 0, float zt = 0);

	Matrix3D();

	static void multiplyVectorByMatrix(Vector3D &vector, const Matrix3D &matrix);

	static Matrix3D perspectiveProjection(float fovy, float aspectRatio, float near, float far);

	static Matrix3D orthographicProjection(float fovy, float aspectRatio, float near, float far);

    float x1() const;
    void x1(float value);

    float x2() const;
    void x2(float value);

    float x3() const;
    void x3(float value);

    float y1() const;
    void y1(float value);

    float y2() const;
    void y2(float value);

    float y3() const;
    void y3(float value);

    float z1() const;
    void z1(float value);

    float z2() const;
    void z2(float value);

    float z3() const;
    void z3(float value);

	float xt() const;
	void xt(float value);

	float yt() const;
	void yt(float value);

	float zt() const;
	void zt(float value);

	float w1() const;
	void w1(float value);

	float w2() const;
	void w2(float value);

	float w3() const;
	void w3(float value);

	float wt() const;
	void wt(float value);

    float determinant() const;

    void transpose();

    void identity();

    void multiplyByScalar(float scalar);

    void multiplyByMatrix(Matrix3D const &matrix);

    void rotateAboutX(float degrees);

    void rotateAboutY(float degrees);

    void rotateAboutZ(float degrees);

	void rotateAbout(Vector3D const &vector, float degrees);

	void scaleAlong(Vector3D const &vector, float factor);
	void scaleAlong(float x, float y, float z, float factor);

	void scale(float scaleX, float scaleY, float scaleZ);

    void inverse();

    Matrix3D clone() const;

    bool isClose(Matrix3D const &matrix, unsigned int precision) const;

    bool isEqual(Matrix3D const &matrix) const;

	bool isOrthogonal() const;

	void orthogonalize();

	void translate(float xt, float yt, float zt);

	void transform(Vector3D &vector) const;

private:
    float _x1;
    float _x2;
    float _x3;
    float _y1;
    float _y2;
    float _y3;
    float _z1;
    float _z2;
    float _z3;
	float _xt;
	float _yt;
	float _zt;
	float _w1;
	float _w2;
	float _w3;
	float _wt = 1;
    mutable float _determinant;
    mutable bool _detNeedsUpdate = true;

    void _checkIfDeterminantNeedUpdateAfterRotation() const;

	void _checkUnitVector(Vector3D const &vector) const;
	void _checkUnitVector(float x, float y, float z) const;

    void _checkNonZeroDeterminant() const;

    bool _areClose(float value1, float value2, int factor) const;

	void _performGrandSchmidtOrthogonalizingAlgorithm();

	void _performOrthogonalizingAlgorithm();
};


#endif //__Matrix3D_H_
