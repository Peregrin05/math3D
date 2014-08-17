#include <iostream>
#include "gtest/gtest.h"
#include "Vector3D.h"
//#include "Matrix3D.h"


void _vector() ;
void _matrix() ;

int main(int argc, char** argv) {
//    _vector();
//    _matrix();

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

void printMatrix(const Matrix3D matrix) {
    std::cout << printf("\nvector %f, %f, %f, %f, %f, %f, %f, %f, %f - %f           ", *matrix.x1(), *matrix.y1(),
            *matrix.z1(), *matrix.x2(), *matrix.y2(), *matrix.z2(), *matrix.x3(), *matrix.y3(), *matrix.z3(),
            *matrix.determinant());
}

void _matrix() {
    Matrix3D matrix(2, 0, 0, 0, 2, 0, 0, 0, 2);
    printMatrix(matrix);
}

void printVector(const Vector3D &vector) {
    std::cout << printf("\nvector %f, %f, %f - %f            ", *vector.x(), *vector.y(), *vector.z(), *vector.length());
}

void _vector() {
    Vector3D vector(1, 2, 3, 4);
    printVector(vector);

    vector.x(5);
    printVector(vector);

    vector.normalize();
    printVector(vector);
}
