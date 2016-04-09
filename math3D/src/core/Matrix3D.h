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

	static void multiplyVectorByMatrix(Vector3D& vector, const Matrix3D& matrix);

	static Matrix3D perspectiveProjection(float fovy, float aspectRatio, float near, float far);

	static Matrix3D orthographicProjection(float left, float right, float bottom, float top, float near, float far);

    float x1() const { return _rows[0][0]; };
    void x1(float value);

    float x2() const { return _rows[1][0]; }
    void x2(float value);

    float x3() const { return _rows[2][0]; }
    void x3(float value);

    float y1() const { return _rows[0][1]; }
    void y1(float value);

    float y2() const { return _rows[1][1]; }
    void y2(float value);

    float y3() const { return _rows[2][1]; }
    void y3(float value);

    float z1() const { return _rows[0][2]; }
    void z1(float value);

    float z2() const { return _rows[1][2]; }
    void z2(float value);

    float z3() const { return _rows[2][2]; }
    void z3(float value);

	float xt() const { return _rows[3][0]; }
	void xt(float value);

	float yt() const { return _rows[3][1]; }
	void yt(float value);

	float zt() const { return _rows[3][2]; }
	void zt(float value);

	float w1() const { return _rows[0][3]; }
	void w1(float value);

	float w2() const { return _rows[1][3]; }
	void w2(float value);

	float w3() const { return _rows[2][3]; }
	void w3(float value);

	float wt() const { return _rows[3][3]; }
	void wt(float value);

    float determinant() const;

    void transpose();

    void identity();

    void multiplyByScalar(float scalar);

    void multiplyByMatrix(const Matrix3D& m);

    void rotateAboutX(float degrees);

    void rotateAboutY(float degrees);

    void rotateAboutZ(float degrees);

	void rotateAbout(const Vector3D& vector, float degrees);

	void scaleAlong(const Vector3D& vector, float factor);
	void scaleAlong(float x, float y, float z, float factor);

	void scale(float scaleX, float scaleY, float scaleZ);

    void inverse();

    Matrix3D clone() const;

    bool isClose(const Matrix3D& matrix, unsigned precision) const;

    bool isEqual(const Matrix3D& matrix) const;

	bool isOrthogonal() const;

	void orthogonalize();

	void translate(float xt, float yt, float zt);

	void transform(Vector3D& vector) const;

    Vector3D& operator[](int index);
    const Vector3D& operator[](int index) const;

    inline operator float*() { return &_rows[0][0]; }
    inline operator const float*() const { return &_rows[0][0]; }

private:
    bool _areClose(float value1, float value2, int factor) const;

	void _performGrandSchmidtOrthogonalizingAlgorithm();

	void _performOrthogonalizingAlgorithm();

    Vector3D _rows[4] = {};
};


#endif //__Matrix3D_H_
