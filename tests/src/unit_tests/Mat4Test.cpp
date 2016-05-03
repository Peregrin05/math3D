#include <array>
#include "gmock/gmock.h"
#include "Mat4.h"

using namespace testing;
using namespace flash::math;

using std::array;

const float X1 = 3;
const float Y1 = 2;
const float Z1 = 1;
const float X2 = 1;
const float Y2 = 3;
const float Z2 = 2;
const float X3 = 2;
const float Y3 = 1;
const float Z3 = 3;
const float XT = 3;
const float YT = 4;
const float ZT = 5;

const float P1 = 3;
const float Q1 = 4;
const float R1 = 5;
const float P2 = 5;
const float Q2 = 3;
const float R2 = 4;
const float P3 = 4;
const float Q3 = 5;
const float R3 = 3;

const array<const float, 3> V1 = {X1, Y1, Z1};
const array<const float, 3> V2 = {X2, Y2, Z2};
const array<const float, 3> V3 = {X3, Y3, Z3};
const array<const float, 3> PV = {P1, P2, P3};
const array<const float, 3> QV = {Q1, Q2, Q3};
const array<const float, 3> RV = {R1, R2, R3};

const int VALUE = 5;

const float DELTA = 0.002;

const float ORTH_X1 = 0.8931070092097471f;
const float ORTH_Y1 = 0.1264769355380969f;
const float ORTH_Z1 = -0.4316983378208827f;
const float ORTH_X2 = -0.22538366839574475f;
const float ORTH_Y2 = 0.9563315511762042f;
const float ORTH_Z2 = -0.1860971956945946f;
const float ORTH_X3 = 0.38930973802474783f;
const float ORTH_Y3 = 0.2635024648875364f;
const float ORTH_Z3 = 0.8826122471829262f;

class Mat4Test : public Test {
public:
    Mat4 matrix;

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

Vec4 _createArbitraryVector(float length = 1) {
	Vec4 vector = Vec4(0.2666, -0.5347f, 0.8019);
	vector.setLength(length);
	return vector;
}

class MatrixDeterminantIsUpdatedTest : public Mat4Test {
public:
	void SetUp() override {
		Mat4Test::SetUp();
		oldDeterminant = matrix.determinant();
	}

	void assertUpdated() {
		ASSERT_THAT(matrix.determinant(), Ne(oldDeterminant));
	}

protected:
	float oldDeterminant;
};

class MatrixDeterminantIsNotChanged : public MatrixDeterminantIsUpdatedTest {
public:
	void assertNotChanged() {
		ASSERT_THAT(matrix.determinant(), Eq(oldDeterminant));
	}
};

class IdentityMatrixTest : public Test {
public:
    IdentityMatrixTest() : identityMatrix(1, 0, 0, 0, 1, 0, 0, 0, 1) {}

    Mat4 identityMatrix;

    void scaleIdentityMatrixAlongArbitraryVector(float vectorLength = 1) {
		identityMatrix.scaleAlong(_createArbitraryVector(vectorLength), 5);
    }

    void rotateIdentityMatrixAlongArbitraryVector(float vectorLength = 1) {
		identityMatrix.rotateAbout(_createArbitraryVector(vectorLength), -15);
    }
};

class OrthogonalMatrixTest : public Test {
public:
	OrthogonalMatrixTest() : orthogonalMatrix(ORTH_X1, ORTH_Y1, ORTH_Z1, ORTH_X2, ORTH_Y2, ORTH_Z2, ORTH_X3, ORTH_Y3,
		ORTH_Z3) {}

	Mat4 orthogonalMatrix;
};

class TwoMatricesTest : public Mat4Test {
public:
    Mat4 matrix2;

    void SetUp() override {
        Mat4Test::SetUp();
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

void _assertEquals(Mat4 matrix, float x1, float y1, float z1, float x2, float y2, float z2, float x3,
    float y3, float z3, float multiplier = 1) {
	ASSERT_THAT(matrix.x1(), Eq(x1 * multiplier));
    ASSERT_THAT(matrix.y1(), Eq(y1 * multiplier));
    ASSERT_THAT(matrix.z1(), Eq(z1 * multiplier));
    ASSERT_THAT(matrix.x2(), Eq(x2 * multiplier));
    ASSERT_THAT(matrix.y2(), Eq(y2 * multiplier));
    ASSERT_THAT(matrix.z2(), Eq(z2 * multiplier));
    ASSERT_THAT(matrix.x3(), Eq(x3 * multiplier));
    ASSERT_THAT(matrix.y3(), Eq(y3 * multiplier));
    ASSERT_THAT(matrix.z3(), Eq(z3 * multiplier));
}

void _assertClose(Mat4 matrix, float x1, float y1, float z1, float x2, float y2, float z2, float x3,
		float y3, float z3, float multiplier = 1) {
	ASSERT_THAT(matrix.x1(), FloatNear(x1 * multiplier, DELTA));
	ASSERT_THAT(matrix.y1(), FloatNear(y1 * multiplier, DELTA));
	ASSERT_THAT(matrix.z1(), FloatNear(z1 * multiplier, DELTA));
	ASSERT_THAT(matrix.x2(), FloatNear(x2 * multiplier, DELTA));
	ASSERT_THAT(matrix.y2(), FloatNear(y2 * multiplier, DELTA));
	ASSERT_THAT(matrix.z2(), FloatNear(z2 * multiplier, DELTA));
	ASSERT_THAT(matrix.x3(), FloatNear(x3 * multiplier, DELTA));
	ASSERT_THAT(matrix.y3(), FloatNear(y3 * multiplier, DELTA));
	ASSERT_THAT(matrix.z3(), FloatNear(z3 * multiplier, DELTA));
}

Mat4 _createArbitraryOrthogonalMatrix() {
	return Mat4(ORTH_X1, ORTH_Y1, ORTH_Z1, ORTH_X2, ORTH_Y2, ORTH_Z2, ORTH_X3, ORTH_Y3, ORTH_Z3);
}

float _dotProd(const array<float const, 3> v1, array<float const, 3> v2) {
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

TEST_F(Mat4Test, MatrixMultiplication) {
    matrix = Mat4();
    Mat4 m;
    m.multiplyByScalar(2);
    matrix.multiplyByMatrix(m);
    ASSERT_EQ(2, matrix.x1());
    ASSERT_EQ(0, matrix.x2());
    ASSERT_EQ(0, matrix.x3());
    ASSERT_EQ(0, matrix.y1());
    ASSERT_EQ(2, matrix.y2());
    ASSERT_EQ(0, matrix.y3());
    ASSERT_EQ(0, matrix.z1());
    ASSERT_EQ(0, matrix.z2());
    ASSERT_EQ(2, matrix.z3());
    ASSERT_EQ(0, matrix.xt());
    ASSERT_EQ(0, matrix.yt());
    ASSERT_EQ(0, matrix.zt());
}

TEST_F(Mat4Test, IdentityMatrix) {
    matrix = Mat4();
    ASSERT_EQ(1, matrix.x1());
    ASSERT_EQ(0, matrix.y1());
    ASSERT_EQ(0, matrix.z1());
    ASSERT_EQ(0, matrix.w1());
    ASSERT_EQ(0, matrix.x2());
    ASSERT_EQ(1, matrix.y2());
    ASSERT_EQ(0, matrix.z2());
    ASSERT_EQ(0, matrix.w2());
    ASSERT_EQ(0, matrix.x3());
    ASSERT_EQ(0, matrix.y3());
    ASSERT_EQ(1, matrix.z3());
    ASSERT_EQ(0, matrix.w3());
    ASSERT_EQ(0, matrix.xt());
    ASSERT_EQ(0, matrix.yt());
    ASSERT_EQ(0, matrix.zt());
    ASSERT_EQ(1, matrix.wt());
}

TEST_F(Mat4Test, StaticIdentityMatrix) {
	ASSERT_TRUE(Mat4::IDENTITY.isEqual(Mat4()));
}

TEST_F(Mat4Test, ConstructorSavesParams) {
	matrix = Mat4(X1, Y1, Z1, X2, Y2, Z2, X3, Y3, Z3, XT, YT, ZT);
    ASSERT_EQ(X1, matrix.x1());
    ASSERT_EQ(X2, matrix.x2());
    ASSERT_EQ(X3, matrix.x3());
    ASSERT_EQ(Y1, matrix.y1());
    ASSERT_EQ(Y2, matrix.y2());
    ASSERT_EQ(Y3, matrix.y3());
    ASSERT_EQ(Z1, matrix.z1());
    ASSERT_EQ(Z2, matrix.z2());
    ASSERT_EQ(Z3, matrix.z3());
    ASSERT_EQ(XT, matrix.xt());
    ASSERT_EQ(YT, matrix.yt());
    ASSERT_EQ(ZT, matrix.zt());
}

TEST_F(Mat4Test, GetterSetter) {
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

    ASSERT_EQ(VALUE, matrix.x1());
    ASSERT_EQ(VALUE, matrix.y1());
    ASSERT_EQ(VALUE, matrix.z1());
    ASSERT_EQ(VALUE, matrix.x2());
    ASSERT_EQ(VALUE, matrix.y2());
    ASSERT_EQ(VALUE, matrix.z2());
    ASSERT_EQ(VALUE, matrix.x3());
    ASSERT_EQ(VALUE, matrix.y3());
    ASSERT_EQ(VALUE, matrix.z3());
    ASSERT_EQ(VALUE, matrix.xt());
    ASSERT_EQ(VALUE, matrix.yt());
    ASSERT_EQ(VALUE, matrix.zt());
}

TEST_F(Mat4Test, Transpose) {
    matrix.transpose();
    _assertEquals(matrix, X1, X2, X3, Y1, Y2, Y3, Z1, Z2, Z3);
}

TEST_F(Mat4Test, Identity) {
    matrix.identity();
    _assertEquals(matrix, 1, 0, 0, 0, 1, 0, 0, 0, 1);
}

TEST_F(Mat4Test, MultiplyByScalar) {
    float multiplier(5);
    matrix.multiplyByScalar(multiplier);
    _assertEquals(matrix, X1, Y1, Z1, X2, Y2, Z2, X3, Y3, Z3, multiplier);
}

TEST_F(Mat4Test, Clone) {
    Mat4 cloneMatrix = matrix.clone();
    _assertEquals(cloneMatrix, X1, Y1, Z1, X2, Y2, Z2, X3, Y3, Z3);
}

TEST_F(TwoMatricesTest, MultiplyByMatrix) {
    matrix.multiplyByMatrix(matrix2);
    _assertEquals(matrix, _dotProd(V1, PV), _dotProd(V1, QV), _dotProd(V1, RV), _dotProd(V2, PV),
        _dotProd(V2, QV), _dotProd(V2, RV), _dotProd(V3, PV), _dotProd(V3, QV), _dotProd(V3, RV));
}

TEST_F(IdentityMatrixTest, RotateAboutX) {
    identityMatrix.rotateAboutX(-22);
    _assertClose(identityMatrix, 1, 0, 0, 0, 0.927, -0.375f, 0, 0.375, 0.927);
   }

TEST_F(IdentityMatrixTest, RotateAboutY) {
    identityMatrix.rotateAboutY(30);
    _assertClose(identityMatrix, 0.866, 0, -0.5f, 0, 1, 0, 0.5, 0, 0.866);
}

TEST_F(IdentityMatrixTest, RotateAboutZ) {
    identityMatrix.rotateAboutZ(30);
    _assertClose(identityMatrix, 0.866, 0.5, 0, -0.5f, 0.866, 0, 0, 0, 1);
}

TEST_F(IdentityMatrixTest, RotateAbout) {
    rotateIdentityMatrixAlongArbitraryVector();
    _assertClose(identityMatrix, 0.968, -0.212f, -0.131f, 0.203, 0.976, -0.084f, 0.146, 0.054, 0.988);
}

//[Test(expects="errors.NotUnitVectorError")]
TEST_F(IdentityMatrixTest, DISABLED_WhenRotatingAlongNotUnitVector_throwException) {
	ASSERT_ANY_THROW(rotateIdentityMatrixAlongArbitraryVector(2));
}

TEST_F(IdentityMatrixTest, ScaleAlong) {
	scaleIdentityMatrixAlongArbitraryVector();
	_assertClose(identityMatrix, 1.285, 0, 0, 0, 2.145, 0, 0, 0, 3.573);
}

//[Test(expects="errors.NotUnitVectorError")]
TEST_F(IdentityMatrixTest, DISABLED_WhenScalingAlongNotUnitVector_throwException) {
	ASSERT_ANY_THROW(scaleIdentityMatrixAlongArbitraryVector(2));
}

TEST_F(Mat4Test, Scale) {
	matrix.scale(2, 4, 6);
	_assertEquals(matrix, X1 * 2, Y1 * 2, Z1 * 2, X2 * 4, Y2 * 4, Z2 * 4, X3 * 6, Y3 * 6, Z3 * 6);
}

TEST_F(Mat4Test, Determinant) {
	matrix = Mat4(3, -2, 0, 1, 4, 0, 0, 0, 2, 0, 0, 0);
	ASSERT_THAT(28, Eq(matrix.determinant()));
}

TEST_F(MatrixDeterminantIsUpdatedTest, AfterXYZIsChanged) {
	matrix.x1(matrix.x1() + 1);
	assertUpdated();
	SetUp();
	matrix.y1(matrix.y1() + 1);
	assertUpdated();
	SetUp();
	matrix.z1(matrix.z1() + 1);
	assertUpdated();
	SetUp();

	matrix.x2(matrix.x2() + 1);
	assertUpdated();
	SetUp();
	matrix.y2(matrix.y2() + 1);
	assertUpdated();
	SetUp();
	matrix.z2(matrix.z2() + 1);
	assertUpdated();
	SetUp();

	matrix.x3(matrix.x3() + 1);
	assertUpdated();
	SetUp();
	matrix.y3(matrix.y3() + 1);
	assertUpdated();
	SetUp();
	matrix.z3(matrix.z3() + 1);
	assertUpdated();
	SetUp();
}

TEST_F(OrthogonalMatrixTest, DeterminantIsOne) {
	ASSERT_THAT(orthogonalMatrix.determinant(), Eq(1));
}

TEST_F(OrthogonalMatrixTest, Rotating_doesNotChangeDeterminant) {
	float oldDeterminant = orthogonalMatrix.determinant();
	orthogonalMatrix.rotateAbout(_createArbitraryVector(), 30);
	ASSERT_THAT(orthogonalMatrix.determinant(), FloatEq(oldDeterminant));
}

TEST_F(OrthogonalMatrixTest, RotatingNotOrthogonalMatrix_changesDeterminant) {
	orthogonalMatrix.x1(orthogonalMatrix.x1() + 1);
	orthogonalMatrix.y3(orthogonalMatrix.y3() - 1);
	float oldDeterminant = orthogonalMatrix.determinant();
	orthogonalMatrix.rotateAbout(_createArbitraryVector(), 30);
	ASSERT_THAT(orthogonalMatrix.determinant(), Ne(oldDeterminant));
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

TEST_F(Mat4Test, AfterIdentifyingMatrix_determinantIsSetTo1) {
	ASSERT_THAT(matrix.determinant(), Ne(1));
	matrix.identity();
	ASSERT_THAT(matrix.determinant(), Eq(1));
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

TEST_F(Mat4Test, SwappingMatrixRows_negatesDeterminant) {
	float oldDeterminant(matrix.determinant());
	matrix.x1(X2);
	matrix.y1(Y2);
	matrix.z1(Z2);
	matrix.x2(X1);
	matrix.y2(Y1);
	matrix.z2(Z1);
	ASSERT_THAT(-matrix.determinant(), Eq(oldDeterminant));
}

TEST_F(Mat4Test, IsEqual) {
	Mat4 matrix2 = matrix.clone();
	ASSERT_TRUE(matrix.isEqual(matrix2));
	matrix2.y3(matrix2.y3() + 1);
	ASSERT_FALSE(matrix.isEqual(matrix2));
	matrix2 = matrix.clone();
	matrix2.translate(1, 0, 0);
	ASSERT_FALSE(matrix.isEqual(matrix2));
	matrix2 = matrix.clone();
	matrix2.translate(0, 1, 0);
	ASSERT_FALSE(matrix.isEqual(matrix2));
	matrix2 = matrix.clone();
	matrix2.translate(0, 0, 1);
	ASSERT_FALSE(matrix.isEqual(matrix2));
	matrix2 = matrix.clone();
	matrix2.v1.w++;
	ASSERT_FALSE(matrix.isEqual(matrix2));
	matrix2 = matrix.clone();
	matrix2.vt.w++;
	ASSERT_FALSE(matrix.isEqual(matrix2));
}

TEST_F(Mat4Test, InverseOrthogonalMatrix_isTranspose) {
	matrix = Mat4(-0.1495f, -0.1986f, -0.9685f, -0.8256f, 0.5640, 0.0117, -0.5439f, -0.8015f, 0.2484);
	matrix.inverse();
	_assertClose(matrix, -0.1495f, -0.8256f, -0.5439f, -0.1986f, 0.5640, -0.8015f, -0.9685f, 0.0117, 0.2484);
}

TEST_F(Mat4Test, Inverse) {
	matrix = Mat4(-4, -3, 3, 0, 2, -2, 1, 4, -1);
	float determinant(matrix.determinant());
	matrix.inverse();
	_assertClose(matrix, 6, 9, 0, -2, 1, -8, -2, 13, -8, 1 / determinant);
}

TEST_F(Mat4Test, IsClose) {
	Mat4 compareMatrix = matrix.clone();
	matrix.multiplyByScalar(1.000001);
	ASSERT_TRUE(matrix.isClose(compareMatrix, 5));
	ASSERT_FALSE(matrix.isClose(compareMatrix, 7));
}

TEST_F(Mat4Test, InverseOfInverse_givesOrigin) {
	Mat4 origin = matrix.clone();
	matrix.inverse();
	matrix.inverse();
	ASSERT_TRUE(matrix.isClose(origin, 6));
}

TEST_F(Mat4Test, InverseMatrixMultipliedByOrigin_givesIdentityMatrix) {
	Mat4 inverseMatrix = matrix.clone();
	inverseMatrix.inverse();
	matrix.multiplyByMatrix(inverseMatrix);
	Mat4 identityMatrix = Mat4(1, 0, 0, 0, 1, 0, 0, 0, 1);
	ASSERT_TRUE(matrix.isClose(identityMatrix, 6));
}

//[Test(expects="errors.ZeroDeterminantMatrixError")]
TEST_F(Mat4Test, DISABLED_InverseOfZeroDeterminantMatrix_throwsException) {
	matrix.x3(0);
	matrix.y3(0);
	matrix.z3(0);

	ASSERT_THAT(matrix.determinant(), Eq(0));

	ASSERT_ANY_THROW(matrix.inverse());
}

TEST_F(OrthogonalMatrixTest, IsOrthogonal) {
	ASSERT_TRUE(orthogonalMatrix.isOrthogonal());
	orthogonalMatrix.x1(orthogonalMatrix.x1() + 0.1f);
	ASSERT_FALSE(orthogonalMatrix.isOrthogonal());
}

TEST_F(Mat4Test, Orthogonalize) {
	matrix = Mat4(1.05, 0, 0, 0, 0.95, 0, 0, 0, 0.8);
	matrix.orthogonalize();
	_assertClose(matrix, 1, 0, 0, 0, 1, 0, 0, 0, 1);
}

TEST_F(OrthogonalMatrixTest, OrthogonalizeUnevenlyScaledMatrix) {
	float scale = 3;
	orthogonalMatrix.x1(orthogonalMatrix.x1() * scale);
	orthogonalMatrix.y1(orthogonalMatrix.y1() * scale);
	orthogonalMatrix.z1(orthogonalMatrix.z1() * scale);
	scale = 40;
	orthogonalMatrix.x2(orthogonalMatrix.x2() * scale);
	orthogonalMatrix.y2(orthogonalMatrix.y2() * scale);
	orthogonalMatrix.z2(orthogonalMatrix.z2() * scale);
	scale = 0.3;
	orthogonalMatrix.x3(orthogonalMatrix.x3() * scale);
	orthogonalMatrix.y3(orthogonalMatrix.y3() * scale);
	orthogonalMatrix.z3(orthogonalMatrix.z3() * scale);

	orthogonalMatrix.orthogonalize();
	_assertClose(orthogonalMatrix, ORTH_X1, ORTH_Y1, ORTH_Z1, ORTH_X2, ORTH_Y2, ORTH_Z2, ORTH_X3, ORTH_Y3, ORTH_Z3);
}

TEST_F(Mat4Test, OrthogonalizeArbitraryMatrix) {
	matrix = _createArbitraryOrthogonalMatrix();
	matrix.x1(matrix.x1() + 1);
	matrix.z1(matrix.z1() - 1);
	matrix.x3(matrix.x3() - 1);
	matrix.z3(matrix.z3() + 1);
	matrix.orthogonalize();
	ASSERT_TRUE(matrix.isOrthogonal());

	matrix.x1(matrix.x1() + 345.26f);
	matrix.y1(matrix.y1() + -86);
	matrix.z1(matrix.z1() + 45.456f);
	matrix.x2(matrix.x2() + 7);
	matrix.y2(matrix.y2() + 94);
	matrix.z2(matrix.z2() + -8543);
	matrix.x3(matrix.x3() + 0.4567f);
	matrix.y3(matrix.y3() + -443.96433f);
	matrix.z3(matrix.z3() + -345.34f);
	matrix.orthogonalize();
	ASSERT_TRUE(matrix.isOrthogonal());
}

TEST_F(MatrixDeterminantIsUpdatedTest, Orthogonalize) {
	matrix.orthogonalize();
	assertUpdated();
}

// TODO: implement perspective projection on p.188
TEST_F(Mat4Test, TranslateSavesGivenValues) {
	matrix.translate(XT, YT, ZT);
	ASSERT_THAT(matrix.xt(), Eq(XT));
	ASSERT_THAT(matrix.yt(), Eq(YT));
	ASSERT_THAT(matrix.zt(), Eq(ZT));
}

TEST_F(Mat4Test, SimpleRotationTransform) {
	Vec4 vector(1, 0, 0);
	matrix = Mat4();
	matrix.rotateAboutZ(30);
	matrix.transform(vector);
	ASSERT_THAT(vector.y, Eq(sinf(30 * M_PI / 180)));
	ASSERT_THAT(vector.x, Eq(cosf(30 * M_PI / 180)));
}

TEST_F(Mat4Test, SimpleScaleTransform) {
	Vec4 vector(1, 1, 0);
	matrix = Mat4();
	matrix.scaleAlong(1, 0, 0, 0);
	matrix.transform(vector);
	ASSERT_THAT(vector.y, Eq(1));
	ASSERT_THAT(vector.x, Eq(0));
}

TEST_F(Mat4Test, SimpleTranslatePointTransform) {
	Vec4 vector(1, 1, 1, 1);
	matrix = Mat4();
	matrix.translate(2, 3, 4);
	matrix.transform(vector);
	ASSERT_THAT(vector.x, Eq(3));
	ASSERT_THAT(vector.y, Eq(4));
	ASSERT_THAT(vector.z, Eq(5));
}

TEST_F(Mat4Test, SimpleTranslateVectorTransform) {
	Vec4 vector(1, 1, 1, 0);
	matrix = Mat4();
	matrix.translate(2, 3, 4);
	matrix.transform(vector);
	ASSERT_THAT(vector.x, Eq(1));
	ASSERT_THAT(vector.y, Eq(1));
	ASSERT_THAT(vector.z, Eq(1));
}
