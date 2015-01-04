#include <array>
#include "gmock/gmock.h"
#include "Matrix3D.h"

using namespace std;
using namespace testing;

const double X1 = 3;
const double Y1 = 2;
const double Z1 = 1;
const double X2 = 1;
const double Y2 = 3;
const double Z2 = 2;
const double X3 = 2;
const double Y3 = 1;
const double Z3 = 3;
const double XT = 3;
const double YT = 4;
const double ZT = 5;

double const P1 = 3;
double const Q1 = 4;
double const R1 = 5;
double const P2 = 5;
double const Q2 = 3;
double const R2 = 4;
double const P3 = 4;
double const Q3 = 5;
double const R3 = 3;

const array<double const, 3> V1 = {X1, Y1, Z1};
const array<double const, 3> V2 = {X2, Y2, Z2};
const array<double const, 3> V3 = {X3, Y3, Z3};
const array<double const, 3> PV = {P1, P2, P3};
const array<double const, 3> QV = {Q1, Q2, Q3};
const array<double const, 3> RV = {R1, R2, R3};

int const VALUE = 5;

double const DELTA = 0.002;

double const ORTH_X1 = 0.8931070092097471;
double const ORTH_Y1 = 0.1264769355380969;
double const ORTH_Z1 = -0.4316983378208827;
double const ORTH_X2 = -0.22538366839574475;
double const ORTH_Y2 = 0.9563315511762042;
double const ORTH_Z2 = -0.1860971956945946;
double const ORTH_X3 = 0.38930973802474783;
double const ORTH_Y3 = 0.2635024648875364;
double const ORTH_Z3 = 0.8826122471829262;

class Matrix3DTest : public Test {
public:
    Matrix3D matrix;

    void SetUp() override {
        matrix.x1(X1);
        matrix.y1(Y1);
        matrix.z1(Z1);
        matrix.x2(X2);
        matrix.y2(Y2);
        matrix.z2(Z2);
        matrix.x3(X3);
        matrix.y3(Y3);
        matrix.z3(Z3);
    }
};

Vector3D _createArbitraryVector(double length = 1) {
	Vector3D vector = Vector3D(0.2666, -0.5347, 0.8019);
	vector.length(length);
	return vector;
}

class MatrixDeterminantIsUpdatedTest : public Matrix3DTest {
public:
	void SetUp() override {
		Matrix3DTest::SetUp();
		oldDeterminant = *matrix.determinant();
	}

	void assertUpdated() {
		ASSERT_THAT(*matrix.determinant(), Ne(oldDeterminant));
	}

protected:
	double oldDeterminant;
};

class MatrixDeterminantIsNotChanged : public MatrixDeterminantIsUpdatedTest {
public:
	void assertNotChanged() {
		ASSERT_THAT(*matrix.determinant(), Eq(oldDeterminant));
	}
};

class IdentityMatrixTest : public Test {
public:
    IdentityMatrixTest() : identityMatrix(1, 0, 0, 0, 1, 0, 0, 0, 1) {}

    Matrix3D identityMatrix;

    void scaleIdentityMatrixAlongArbitraryVector(double vectorLength = 1) {
		identityMatrix.scaleAlong(_createArbitraryVector(vectorLength), 5);
    }

    void rotateIdentityMatrixAlongArbitraryVector(double vectorLength = 1) {
		identityMatrix.rotateAbout(_createArbitraryVector(vectorLength), -15);
    }
};

class OrthogonalMatrixTest : public Test {
public:
	OrthogonalMatrixTest() : orthogonalMatrix(ORTH_X1, ORTH_Y1, ORTH_Z1, ORTH_X2, ORTH_Y2, ORTH_Z2, ORTH_X3, ORTH_Y3,
		ORTH_Z3) {}

	Matrix3D orthogonalMatrix;
};

class TwoMatricesTest : public Matrix3DTest {
public:
    Matrix3D matrix2;

    void SetUp() override {
        Matrix3DTest::SetUp();
        matrix2.x1(P1);
        matrix2.y1(Q1);
        matrix2.z1(R1);
        matrix2.x2(P2);
        matrix2.y2(Q2);
        matrix2.z2(R2);
        matrix2.x3(P3);
        matrix2.y3(Q3);
        matrix2.z3(R3);
    }
};

void _assertEquals(Matrix3D matrix, double x1, double y1, double z1, double x2, double y2, double z2, double x3,
    double y3, double z3, double multiplier = 1) {
	ASSERT_THAT(*matrix.x1(), Eq(x1 * multiplier));
    ASSERT_THAT(*matrix.y1(), Eq(y1 * multiplier));
    ASSERT_THAT(*matrix.z1(), Eq(z1 * multiplier));
    ASSERT_THAT(*matrix.x2(), Eq(x2 * multiplier));
    ASSERT_THAT(*matrix.y2(), Eq(y2 * multiplier));
    ASSERT_THAT(*matrix.z2(), Eq(z2 * multiplier));
    ASSERT_THAT(*matrix.x3(), Eq(x3 * multiplier));
    ASSERT_THAT(*matrix.y3(), Eq(y3 * multiplier));
    ASSERT_THAT(*matrix.z3(), Eq(z3 * multiplier));
}

void _assertClose(Matrix3D matrix, double x1, double y1, double z1, double x2, double y2, double z2, double x3,
		double y3, double z3, double multiplier = 1) {
	ASSERT_THAT(*matrix.x1(), DoubleNear(x1 * multiplier, DELTA));
	ASSERT_THAT(*matrix.y1(), DoubleNear(y1 * multiplier, DELTA));
	ASSERT_THAT(*matrix.z1(), DoubleNear(z1 * multiplier, DELTA));
	ASSERT_THAT(*matrix.x2(), DoubleNear(x2 * multiplier, DELTA));
	ASSERT_THAT(*matrix.y2(), DoubleNear(y2 * multiplier, DELTA));
	ASSERT_THAT(*matrix.z2(), DoubleNear(z2 * multiplier, DELTA));
	ASSERT_THAT(*matrix.x3(), DoubleNear(x3 * multiplier, DELTA));
	ASSERT_THAT(*matrix.y3(), DoubleNear(y3 * multiplier, DELTA));
	ASSERT_THAT(*matrix.z3(), DoubleNear(z3 * multiplier, DELTA));
}

Matrix3D _createArbitraryOrthogonalMatrix() {
	return Matrix3D(ORTH_X1, ORTH_Y1, ORTH_Z1, ORTH_X2, ORTH_Y2, ORTH_Z2, ORTH_X3, ORTH_Y3, ORTH_Z3);
}

double _dotProd(const array<double const, 3> v1, array<double const, 3> v2) {
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

TEST_F(Matrix3DTest, ConstructorSavesParams) {
	matrix = Matrix3D(X1, Y1, Z1, X2, Y2, Z2, X3, Y3, Z3, XT, YT, ZT);
    ASSERT_EQ(X1, *matrix.x1());
    ASSERT_EQ(X2, *matrix.x2());
    ASSERT_EQ(X3, *matrix.x3());
    ASSERT_EQ(Y1, *matrix.y1());
    ASSERT_EQ(Y2, *matrix.y2());
    ASSERT_EQ(Y3, *matrix.y3());
    ASSERT_EQ(Z1, *matrix.z1());
    ASSERT_EQ(Z2, *matrix.z2());
    ASSERT_EQ(Z3, *matrix.z3());
    ASSERT_EQ(XT, *matrix.xt());
    ASSERT_EQ(YT, *matrix.yt());
    ASSERT_EQ(ZT, *matrix.zt());
}

TEST_F(Matrix3DTest, GetterSetter) {
    matrix.x1(VALUE);
    matrix.y1(VALUE);
    matrix.z1(VALUE);
    matrix.x2(VALUE);
    matrix.y2(VALUE);
    matrix.z2(VALUE);
    matrix.x3(VALUE);
    matrix.y3(VALUE);
    matrix.z3(VALUE);
    matrix.xt(VALUE);
    matrix.yt(VALUE);
    matrix.zt(VALUE);

    ASSERT_EQ(VALUE, *matrix.x1());
    ASSERT_EQ(VALUE, *matrix.y1());
    ASSERT_EQ(VALUE, *matrix.z1());
    ASSERT_EQ(VALUE, *matrix.x2());
    ASSERT_EQ(VALUE, *matrix.y2());
    ASSERT_EQ(VALUE, *matrix.z2());
    ASSERT_EQ(VALUE, *matrix.x3());
    ASSERT_EQ(VALUE, *matrix.y3());
    ASSERT_EQ(VALUE, *matrix.z3());
    ASSERT_EQ(VALUE, *matrix.xt());
    ASSERT_EQ(VALUE, *matrix.yt());
    ASSERT_EQ(VALUE, *matrix.zt());
}

TEST_F(Matrix3DTest, Transpose) {
    matrix.transpose();
    _assertEquals(matrix, X1, X2, X3, Y1, Y2, Y3, Z1, Z2, Z3);
}

TEST_F(Matrix3DTest, Identity) {
    matrix.identity();
    _assertEquals(matrix, 1, 0, 0, 0, 1, 0, 0, 0, 1);
}

TEST_F(Matrix3DTest, MultiplyByScalar) {
    double multiplier(5);
    matrix.multiplyByScalar(multiplier);
    _assertEquals(matrix, X1, Y1, Z1, X2, Y2, Z2, X3, Y3, Z3, multiplier);
}

TEST_F(Matrix3DTest, Clone) {
    Matrix3D cloneMatrix = matrix.clone();
    _assertEquals(cloneMatrix, X1, Y1, Z1, X2, Y2, Z2, X3, Y3, Z3);
}

TEST_F(TwoMatricesTest, MultiplyByMatrix) {
    matrix.multiplyByMatrix(matrix2);
    _assertEquals(matrix, _dotProd(V1, PV), _dotProd(V1, QV), _dotProd(V1, RV), _dotProd(V2, PV),
        _dotProd(V2, QV), _dotProd(V2, RV), _dotProd(V3, PV), _dotProd(V3, QV), _dotProd(V3, RV));
}

TEST_F(IdentityMatrixTest, RotateAboutX) {
    identityMatrix.rotateAboutX(-22);
    _assertClose(identityMatrix, 1, 0, 0, 0, 0.927, -0.375, 0, 0.375, 0.927);
   }

TEST_F(IdentityMatrixTest, RotateAboutY) {
    identityMatrix.rotateAboutY(30);
    _assertClose(identityMatrix, 0.866, 0, -0.5, 0, 1, 0, 0.5, 0, 0.866);
}

TEST_F(IdentityMatrixTest, RotateAboutZ) {
    identityMatrix.rotateAboutZ(30);
    _assertClose(identityMatrix, 0.866, 0.5, 0, -0.5, 0.866, 0, 0, 0, 1);
}

TEST_F(IdentityMatrixTest, RotateAbout) {
    rotateIdentityMatrixAlongArbitraryVector();
    _assertClose(identityMatrix, 0.968, -0.212, -0.131, 0.203, 0.976, -0.084, 0.146, 0.054, 0.988);
}

//[Test(expects="errors.NotUnitVectorError")]
TEST_F(IdentityMatrixTest, WhenRotatingAlongNotUnitVector_throwException) {
	ASSERT_ANY_THROW(rotateIdentityMatrixAlongArbitraryVector(2));
}

TEST_F(IdentityMatrixTest, ScaleAlong) {
	scaleIdentityMatrixAlongArbitraryVector();
	_assertClose(identityMatrix, 1.285, 0, 0, 0, 2.145, 0, 0, 0, 3.573);
}

//[Test(expects="errors.NotUnitVectorError")]
TEST_F(IdentityMatrixTest, WhenScalingAlongNotUnitVector_throwException) {
	ASSERT_ANY_THROW(scaleIdentityMatrixAlongArbitraryVector(2));
}

TEST_F(Matrix3DTest, Scale) {
	matrix.scale(2, 4, 6);
	_assertEquals(matrix, X1 * 2, Y1 * 2, Z1 * 2, X2 * 4, Y2 * 4, Z2 * 4, X3 * 6, Y3 * 6, Z3 * 6);
}

TEST_F(Matrix3DTest, Determinant) {
	matrix = Matrix3D(3, -2, 0, 1, 4, 0, 0, 0, 2);
	ASSERT_THAT(28, Eq(*matrix.determinant()));
}

TEST_F(MatrixDeterminantIsUpdatedTest, AfterXYZIsChanged) {
	matrix.x1(*matrix.x1() + 1);
	assertUpdated();
	SetUp();
	matrix.y1(*matrix.y1() + 1);
	assertUpdated();
	SetUp();
	matrix.z1(*matrix.z1() + 1);
	assertUpdated();
	SetUp();

	matrix.x2(*matrix.x2() + 1);
	assertUpdated();
	SetUp();
	matrix.y2(*matrix.y2() + 1);
	assertUpdated();
	SetUp();
	matrix.z2(*matrix.z2() + 1);
	assertUpdated();
	SetUp();

	matrix.x3(*matrix.x3() + 1);
	assertUpdated();
	SetUp();
	matrix.y3(*matrix.y3() + 1);
	assertUpdated();
	SetUp();
	matrix.z3(*matrix.z3() + 1);
	assertUpdated();
	SetUp();
}

TEST_F(OrthogonalMatrixTest, DeterminantIsOne) {
	ASSERT_THAT(*orthogonalMatrix.determinant(), Eq(1));
}

TEST_F(OrthogonalMatrixTest, Rotating_doesNotChangeDeterminant) {
	double oldDeterminant = *orthogonalMatrix.determinant();
	orthogonalMatrix.rotateAbout(_createArbitraryVector(), 30);
	ASSERT_THAT(*orthogonalMatrix.determinant(), Eq(oldDeterminant));
}

TEST_F(OrthogonalMatrixTest, RotatingNotOrthogonalMatrix_changesDeterminant) {
	orthogonalMatrix.x1(*orthogonalMatrix.x1() + 1);
	orthogonalMatrix.y3(*orthogonalMatrix.y3() - 1);
	double oldDeterminant = *orthogonalMatrix.determinant();
	orthogonalMatrix.rotateAbout(_createArbitraryVector(), 30);
	ASSERT_THAT(*orthogonalMatrix.determinant(), Ne(oldDeterminant));
}

TEST_F(MatrixDeterminantIsUpdatedTest, RotatingAboutXAxis) {
	matrix.rotateAboutX(30);
	assertUpdated();
}

TEST_F(MatrixDeterminantIsUpdatedTest, RotatingAboutYAxis) {
	matrix.rotateAboutY(30);
	assertUpdated();
}

TEST_F(MatrixDeterminantIsUpdatedTest, RotatingAboutZAxis) {
	matrix.rotateAboutZ(30);
	assertUpdated();
}

TEST_F(Matrix3DTest, AfterIdentifyingMatrix_determinantIsSetTo1) {
	ASSERT_THAT(*matrix.determinant(), Ne(1));
	matrix.identity();
	ASSERT_THAT(*matrix.determinant(), Eq(1));
}

TEST_F(MatrixDeterminantIsNotChanged, Tanspose) {
	matrix.transpose();
	assertNotChanged();
}

TEST_F(MatrixDeterminantIsUpdatedTest, MultiplyByScalar) {
	matrix.multiplyByScalar(2);
	assertUpdated();
}

TEST_F(MatrixDeterminantIsUpdatedTest, MultiplyByMatrix) {
	matrix.multiplyByMatrix(matrix);
	assertUpdated();
}

TEST_F(MatrixDeterminantIsUpdatedTest, ScaleAlong) {
	matrix.scaleAlong(_createArbitraryVector(), 2);
}

TEST_F(Matrix3DTest, SwappingMatrixRows_negatesDeterminant) {
	double oldDeterminant(*matrix.determinant());
	matrix.x1(X2);
	matrix.y1(Y2);
	matrix.z1(Z2);
	matrix.x2(X1);
	matrix.y2(Y1);
	matrix.z2(Z1);
	ASSERT_THAT(-*matrix.determinant(), Eq(oldDeterminant));
}

TEST_F(Matrix3DTest, IsEqual) {
	Matrix3D matrix2 = matrix.clone();
	ASSERT_TRUE(matrix.isEqual(matrix2));
	matrix2.y3(*matrix2.y3() + 1);
	ASSERT_FALSE(matrix.isEqual(matrix2));
}

TEST_F(Matrix3DTest, InverseOrthogonalMatrix_isTranspose) {
	matrix = Matrix3D(-0.1495, -0.1986, -0.9685, -0.8256, 0.5640, 0.0117, -0.5439, -0.8015, 0.2484);
	matrix.inverse();
	_assertClose(matrix, -0.1495, -0.8256, -0.5439, -0.1986, 0.5640, -0.8015, -0.9685, 0.0117, 0.2484);
}

TEST_F(Matrix3DTest, Inverse) {
	matrix = Matrix3D(-4, -3, 3, 0, 2, -2, 1, 4, -1);
	double determinant(*matrix.determinant());
	matrix.inverse();
	_assertClose(matrix, 6, 9, 0, -2, 1, -8, -2, 13, -8, 1 / determinant);
}

TEST_F(Matrix3DTest, IsClose) {
	Matrix3D compareMatrix = matrix.clone();
	matrix.multiplyByScalar(1.000001);
	ASSERT_TRUE(matrix.isClose(compareMatrix, 5));
	ASSERT_FALSE(matrix.isClose(compareMatrix, 7));
}

TEST_F(Matrix3DTest, InverseOfInverse_givesOrigin) {
	Matrix3D origin = matrix.clone();
	matrix.inverse();
	matrix.inverse();
	ASSERT_TRUE(matrix.isClose(origin, 8));
}

TEST_F(Matrix3DTest, InverseMatrixMultipliedByOrigin_givesIdentityMatrix) {
	Matrix3D inverseMatrix = matrix.clone();
	inverseMatrix.inverse();
	matrix.multiplyByMatrix(inverseMatrix);
	const Matrix3D identityMatrix = Matrix3D(1, 0, 0, 0, 1, 0, 0, 0, 1);
	ASSERT_TRUE(matrix.isClose(identityMatrix, 8));
}

//[Test(expects="errors.ZeroDeterminantMatrixError")]
TEST_F(Matrix3DTest, InverseOfZeroDeterminantMatrix_throwsException) {
	matrix.x3(0);
	matrix.y3(0);
	matrix.z3(0);

	ASSERT_THAT(*matrix.determinant(), Eq(0));

	ASSERT_ANY_THROW(matrix.inverse());
}

TEST_F(OrthogonalMatrixTest, IsOrthogonal) {
	ASSERT_TRUE(orthogonalMatrix.isOrthogonal());
	orthogonalMatrix.x1(*orthogonalMatrix.x1() + 0.1);
	ASSERT_FALSE(orthogonalMatrix.isOrthogonal());
}

TEST_F(Matrix3DTest, Orthogonalize) {
	matrix = Matrix3D(1.05, 0, 0, 0, 0.95, 0, 0, 0, 0.8);
	matrix.orthogonalize();
	_assertClose(matrix, 1, 0, 0, 0, 1, 0, 0, 0, 1);
}

TEST_F(OrthogonalMatrixTest, OrthogonalizeUnevenlyScaledMatrix) {
	float scale = 3;
	orthogonalMatrix.x1(*orthogonalMatrix.x1() * scale);
	orthogonalMatrix.y1(*orthogonalMatrix.y1() * scale);
	orthogonalMatrix.z1(*orthogonalMatrix.z1() * scale);
	scale = 40;
	orthogonalMatrix.x2(*orthogonalMatrix.x2() * scale);
	orthogonalMatrix.y2(*orthogonalMatrix.y2() * scale);
	orthogonalMatrix.z2(*orthogonalMatrix.z2() * scale);
	scale = 0.3;
	orthogonalMatrix.x3(*orthogonalMatrix.x3() * scale);
	orthogonalMatrix.y3(*orthogonalMatrix.y3() * scale);
	orthogonalMatrix.z3(*orthogonalMatrix.z3() * scale);

	orthogonalMatrix.orthogonalize();
	_assertClose(orthogonalMatrix, ORTH_X1, ORTH_Y1, ORTH_Z1, ORTH_X2, ORTH_Y2, ORTH_Z2, ORTH_X3, ORTH_Y3, ORTH_Z3);
}

TEST_F(Matrix3DTest, OrthogonalizeArbitraryMatrix) {
	matrix = _createArbitraryOrthogonalMatrix();
	matrix.x1(*matrix.x1() + 1);
	matrix.z1(*matrix.z1() - 1);
	matrix.x3(*matrix.x3() - 1);
	matrix.z3(*matrix.z3() + 1);
	matrix.orthogonalize();
	ASSERT_TRUE(matrix.isOrthogonal());

	matrix.x1(*matrix.x1() + 345.26);
	matrix.y1(*matrix.y1() + -86);
	matrix.z1(*matrix.z1() + 45.456);
	matrix.x2(*matrix.x2() + 7);
	matrix.y2(*matrix.y2() + 94);
	matrix.z2(*matrix.z2() + -8543);
	matrix.x3(*matrix.x3() + 0.4567);
	matrix.y3(*matrix.y3() + -443.96433);
	matrix.z3(*matrix.z3() + -345.34);
	matrix.orthogonalize();
	ASSERT_TRUE(matrix.isOrthogonal());
}

TEST_F(MatrixDeterminantIsUpdatedTest, Orthogonalize) {
	matrix.orthogonalize();
	assertUpdated();
}

// TODO: implement 4x4 matrix transformation on p.182
// TODO: implement perspective projection on p.188
TEST_F(Matrix3DTest, TranslateSavesGivenValues) {
	matrix.translate(XT, YT, ZT);
	ASSERT_THAT(*matrix.xt(), Eq(XT));
	ASSERT_THAT(*matrix.yt(), Eq(YT));
	ASSERT_THAT(*matrix.zt(), Eq(ZT));
}

TEST_F(Matrix3DTest, SimpleRotationTransform) {
	Vector3D vector(1, 0, 0);
	matrix = Matrix3D();
	matrix.rotateAboutZ(30);
	matrix.transform(vector);
	ASSERT_THAT(*vector.y(), Eq(sin(30 * M_PI / 180)));
	ASSERT_THAT(*vector.x(), Eq(cos(30 * M_PI / 180)));
}

TEST_F(Matrix3DTest, SimpleScaleTransform) {
	Vector3D vector(1, 1, 0);
	matrix = Matrix3D();
	matrix.scaleAlong(1, 0, 0, 0);
	matrix.transform(vector);
	ASSERT_THAT(*vector.y(), Eq(1));
	ASSERT_THAT(*vector.x(), Eq(0));
}

TEST_F(Matrix3DTest, SimpleTranslatePointTransform) {
	Vector3D vector(1, 1, 1, 1);
	matrix = Matrix3D();
	matrix.translate(2, 3, 4);
	matrix.transform(vector);
	ASSERT_THAT(*vector.x(), Eq(3));
	ASSERT_THAT(*vector.y(), Eq(4));
	ASSERT_THAT(*vector.z(), Eq(5));
}

TEST_F(Matrix3DTest, SimpleTranslateVectorTransform) {
	Vector3D vector(1, 1, 1, 0);
	matrix = Matrix3D();
	matrix.translate(2, 3, 4);
	matrix.transform(vector);
	ASSERT_THAT(*vector.x(), Eq(1));
	ASSERT_THAT(*vector.y(), Eq(1));
	ASSERT_THAT(*vector.z(), Eq(1));
}