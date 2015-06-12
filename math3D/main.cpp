#include <iostream>
#include <math.h>
#include "gtest/gtest.h"
#include "Vector3D.h"
//#include "Matrix3D.h"


void _vector() ;
void _matrix() ;

int main(int argc, char** argv) {
    /*_vector();
    _matrix();

	float time = 0.5;
	float f = time * (float) M_PI * 0.1f;
	Matrix3D trans1;
	trans1.translate(0.0f, 0.0f, -4.0f);

	Matrix3D trans2;
	trans2.translate(sinf(2.1f * f) * 0.5f, cosf(1.7f * f) * 0.5f, sinf(1.3f * f) * cosf(1.5f * f) * 2.0f);

	Matrix3D rot1;
	rot1.rotateAbout(Vector3D(0.0f, 1.0f, 0.0f), (float) time * 45.0f);

	Matrix3D rot2;
	rot2.rotateAbout(Vector3D(1.0f, 0.0f, 0.0f), (float) time * 81.0f);

	Matrix3D res;
	res.multiplyByMatrix(rot1);
	res.multiplyByMatrix(rot2);
	res.multiplyByMatrix(trans1);
	res.multiplyByMatrix(trans2);*/

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
	return 0;
}

void printMatrix(const Matrix3D matrix) {
    std::cout << printf("\nvector %f, %f, %f, %f, %f, %f, %f, %f, %f - %f           ", matrix.x1(), matrix.y1(),
            matrix.z1(), matrix.x2(), matrix.y2(), matrix.z2(), matrix.x3(), matrix.y3(), matrix.z3(),
            matrix.determinant());
}

void _matrix() {
    Matrix3D matrix(2, 0, 0, 0, 2, 0, 0, 0, 2);
    printMatrix(matrix);
}

void printVector(const Vector3D &vector) {
    std::cout << printf("\nvector %f, %f, %f - %f            ", vector.x(), vector.y(), vector.z(), vector.length());
}

void _vector() {
    Vector3D vector(1, 2, 3, 4);
    printVector(vector);

    vector.x(5);
    printVector(vector);

    vector.normalize();
    printVector(vector);
}
