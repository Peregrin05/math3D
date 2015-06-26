#include <math.h>
#include <gmock/gmock-matchers.h>
#include "gtest/gtest.h"
#include "Matrix3D.h"

using namespace testing;

const float VALUE = 5;
const float XV1 = 2;
const float YV1 = 3;
const float ZV1 = 4;
const float XV2 = 10;
const float YV2 = -20;
const float ZV2 = 6.5;

const float X1 = 3;
const float Y1 = 2;
const float Z1 = 1;
const float X2 = 1;
const float Y2 = 3;
const float Z2 = 2;
const float X3 = 2;
const float Y3 = 1;
const float Z3 = 3;

class Vector3DTest : public testing::Test {
public:
    Vector3D vector;

    void SetUp() override {
        vector.x(XV1);
        vector.y(YV1);
        vector.z(ZV1);
    }

    void assertEquals(Vector3D vector, float x, float y, float z) {
        ASSERT_EQ(x, vector.x());
        ASSERT_EQ(y, vector.y());
        ASSERT_EQ(z, vector.z());
    }
};

class TwoVectorsTest : public Vector3DTest {
public:
    Vector3D vector2;

    void SetUp() override {
        Vector3DTest::SetUp();
        vector2.x(XV2);
        vector2.y(YV2);
        vector2.z(ZV2);
    }
};

class ZeroVectorTest : public testing::Test {
public:
    ZeroVectorTest() : zeroVector(0, 0, 0) {}

    Vector3D zeroVector;
};

class VectorWithMatrixTest : public Vector3DTest {
public:
    Matrix3D matrix;

    void SetUp() override {
        Vector3DTest::SetUp();
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

TEST_F(Vector3DTest, ConstructorArgumentsSetXYZW) {
    float x(1);
    float y(2);
    float z(3);
    vector = Vector3D(x, y, z);
    ASSERT_EQ(x, vector.x());
    ASSERT_EQ(y, vector.y());
    ASSERT_EQ(z, vector.z());
}

TEST_F(Vector3DTest, SettersGettersXYZW) {
    ASSERT_EQ(XV1, vector.x());
    ASSERT_EQ(YV1, vector.y());
    ASSERT_EQ(ZV1, vector.z());
}

TEST_F(Vector3DTest, AfterConstructed_lengthIsCalculated) {
    ASSERT_EQ(sqrtf(XV1 * XV1 + YV1 * YV1 + ZV1 * ZV1), vector.length());
}

TEST_F(Vector3DTest, SettingLength_changesXYZProperly) {
    float currentLength(vector.length());
    float newLength(currentLength + 2);
    float ratio(currentLength / newLength);
    vector.length(newLength);

    ASSERT_EQ(XV1 / ratio, vector.x());
    ASSERT_EQ(YV1 / ratio, vector.y());
    ASSERT_EQ(ZV1 / ratio, vector.z());
}

TEST_F(Vector3DTest, Normalize_setsLengthTo1) {
    vector.normalize();

    ASSERT_EQ(1, vector.length());
}

TEST_F(Vector3DTest, NormalizeOfXVector_setsXTo1) {
    Vector3D vector(VALUE);
    vector.normalize();

    ASSERT_EQ(1, vector.x());
}

TEST_F(Vector3DTest, NormalizeOfYVector_setsYTo1) {
    Vector3D vector(0, VALUE);
    vector.normalize();

    ASSERT_EQ(1, vector.y());
}

TEST_F(Vector3DTest, NormalizeOfZVector_setsZTo1) {
    Vector3D vector(0, 0, VALUE);
    vector.normalize();

    ASSERT_EQ(1, vector.z());
}

TEST_F(Vector3DTest, SettingX_updatesLength) {
    float oldLength(vector.length());
    vector.x(vector.x() + 1);

    ASSERT_NE(oldLength, vector.length());
}

TEST_F(Vector3DTest, SettingY_updatesLength) {
    float oldLength(vector.length());
    vector.y(vector.y() + 1);

    ASSERT_NE(oldLength, vector.length());
}

TEST_F(Vector3DTest, SettingZ_updatesLength) {
    float oldLength(vector.length());
    vector.z(vector.z() + 1);

    ASSERT_NE(oldLength, vector.length());
}

TEST_F(Vector3DTest, SettingW_doesNotUpdateLength) {
	float oldLength(vector.length());
	vector.w(vector.w() + 1);

	ASSERT_THAT(vector.length(), Eq(oldLength));
}

TEST_F(Vector3DTest, MultiplyByScalar) {
    int multiplier(5);

    vector.multiplyByScalar(multiplier);
    ASSERT_EQ(XV1 * multiplier, vector.x());
    ASSERT_EQ(YV1 * multiplier, vector.y());
    ASSERT_EQ(ZV1 * multiplier, vector.z());
}

TEST_F(Vector3DTest, AfterMultiplyByScalar_lengthIsUpdated) {
    float oldLength(vector.length());
    vector.multiplyByScalar(5);

    ASSERT_NE(oldLength, vector.length());
}

TEST_F(Vector3DTest, Clone) {
    Vector3D cloneVector = vector.clone();

    ASSERT_EQ(cloneVector.x(), vector.x());
    ASSERT_EQ(cloneVector.y(), vector.y());
    ASSERT_EQ(cloneVector.z(), vector.z());
    ASSERT_EQ(cloneVector.length(), vector.length());
}

TEST_F(ZeroVectorTest, NormalizeThrowsException) {
	ASSERT_ANY_THROW(zeroVector.normalize());
}

TEST_F(ZeroVectorTest, SetLengthThrowsException) {
	ASSERT_ANY_THROW(zeroVector.length(2));
}

TEST_F(TwoVectorsTest, Add) {
    vector.add(vector2);
    ASSERT_EQ(XV1 + XV2, vector.x());
    ASSERT_EQ(YV1 + YV2, vector.y());
    ASSERT_EQ(ZV1 + ZV2, vector.z());
}

TEST_F(TwoVectorsTest, AfterAdd_lengthIsUpdated) {
    float oldLength(vector.length());
    vector.add(vector2);
    ASSERT_NE(oldLength, vector.length());
}

TEST_F(TwoVectorsTest, Subtract) {
    vector.subtract(vector2);
    ASSERT_EQ(XV1 - XV2, vector.x());
    ASSERT_EQ(YV1 - YV2, vector.y());
    ASSERT_EQ(ZV1 - ZV2, vector.z());
}

TEST_F(TwoVectorsTest, AfterSubtract_lengthIsUpdated) {
    float oldLength(vector.length());
    vector.subtract(vector2);
    ASSERT_NE(oldLength, vector.length());
}

TEST_F(TwoVectorsTest, DistanceBetween) {
    float distance(Vector3D::distanceBetween(vector, vector2));
    vector2.subtract(vector);
    ASSERT_EQ(vector2.length(), distance);
}

TEST_F(TwoVectorsTest, DotProduct) {
    float dotProduct(Vector3D::dotProduct(vector, vector2));

    ASSERT_EQ(vector2.x() * vector.x() + vector2.y() * vector.y() + vector2.z() * vector.z(), dotProduct);
}

TEST_F(TwoVectorsTest, AngleBetween) {
    float angle(Vector3D::angleBetween(vector, vector2));
    vector.normalize();
    vector2.normalize();

    float dotProduct = Vector3D::dotProduct(vector, vector2);

    ASSERT_EQ((float) (acosf(dotProduct) * 180 / M_PI), angle);
}

TEST_F(TwoVectorsTest, CrossProduct) {
    Vector3D crossProduct = Vector3D::crossProduct(vector, vector2);

    ASSERT_EQ(vector.y() * vector2.z() - vector.z() * vector2.y(), crossProduct.x());
    ASSERT_EQ(vector.z() * vector2.x() - vector.x() * vector2.z(), crossProduct.y());
    ASSERT_EQ(vector.x() * vector2.y() - vector.y() * vector2.x(), crossProduct.z());
}

TEST_F(TwoVectorsTest, CcrossProductOfTwoAxisGivesThird) {
    Vector3D xAxis(1);
    Vector3D yAxis(0, 1);
    Vector3D zAxis(0, 0, 1);

    ASSERT_TRUE(Vector3D::crossProduct(xAxis, yAxis).isEqualTo(zAxis));
    ASSERT_TRUE(Vector3D::crossProduct(yAxis, zAxis).isEqualTo(xAxis));
    ASSERT_TRUE(Vector3D::crossProduct(zAxis, xAxis).isEqualTo(yAxis));

    Vector3D xAxisNegative(-1);
    Vector3D yAxisNegative(0, -1);
    Vector3D zAxisNegative(0, 0, -1);

    ASSERT_TRUE(Vector3D::crossProduct(yAxis, xAxis).isEqualTo(zAxisNegative));
    ASSERT_TRUE(Vector3D::crossProduct(zAxis, yAxis).isEqualTo(xAxisNegative));
    ASSERT_TRUE(Vector3D::crossProduct(xAxis, zAxis).isEqualTo(yAxisNegative));
}

TEST_F(TwoVectorsTest, IsEqualToTrue) {
    ASSERT_TRUE(vector.isEqualTo(Vector3D(XV1, YV1, ZV1)));
}

TEST_F(TwoVectorsTest, IsEqualToFalse) {
    ASSERT_FALSE(vector.isEqualTo(vector2));
}

TEST_F(VectorWithMatrixTest, MultiplyByMatrix) {
    vector.multiplyByMatrix(matrix);
    assertEquals(vector, XV1 * X1 + YV1 * X2 + ZV1 * X3, XV1 * Y1 + YV1 * Y2 + ZV1 * Y3,
            XV1 * Z1 + YV1 * Z2 + ZV1 * Z3);
}

TEST_F(VectorWithMatrixTest, AfterMultiplyByMatrix_lengthIsUpdated) {
    float oldLength(vector.length());
    vector.multiplyByMatrix(matrix);
    ASSERT_NE(oldLength, vector.length());
}

TEST_F(VectorWithMatrixTest, bla) {
	int xt = 4;
	int yt = 5;
	int zt = 6;
	matrix.translate(xt, yt, zt);
	vector.multiplyByMatrix(matrix);

	float x = XV1 * X1 + YV1 * X2 + ZV1 * X3;
	float y = XV1 * Y1 + YV1 * Y2 + ZV1 * Y3;
	float z = XV1 * Z1 + YV1 * Z2 + ZV1 * Z3;
	assertEquals(vector, x + xt, y + yt, z + zt);
}

TEST_F(VectorWithMatrixTest, bla2) {
	int xt = 4;
	int yt = 5;
	int zt = 6;
	matrix.translate(xt, yt, zt);
	vector.w(0);
	vector.multiplyByMatrix(matrix);

	float x = XV1 * X1 + YV1 * X2 + ZV1 * X3;
	float y = XV1 * Y1 + YV1 * Y2 + ZV1 * Y3;
	float z = XV1 * Z1 + YV1 * Z2 + ZV1 * Z3;
	assertEquals(vector, x, y, z);
}

