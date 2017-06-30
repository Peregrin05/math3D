#define _USE_MATH_DEFINES
#include <cmath>
#include <gmock/gmock-matchers.h>
#include "gtest/gtest.h"
#include "Mat4.h"

using namespace testing;
using namespace flash::math;

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

class Vec4Test : public testing::Test {
public:
    Vec4 vector;

    void SetUp() override {
        setDefaultValues();
    }

    void setDefaultValues() {
        vector.x = XV1;
        vector.y = YV1;
        vector.z = ZV1;
    }

    void assertEquals(Vec4 vector, float x, float y, float z) {
        ASSERT_EQ(x, vector.x);
        ASSERT_EQ(y, vector.y);
        ASSERT_EQ(z, vector.z);
    }
};

class TwoVectorsTest : public Vec4Test {
public:
    Vec4 vector2;

    void SetUp() override {
        Vec4Test::SetUp();
        vector2.x = XV2;
        vector2.y = YV2;
        vector2.z = ZV2;
    }
};

class ZeroVectorTest : public testing::Test {
public:
    ZeroVectorTest() : zeroVector(0, 0, 0) {}

    Vec4 zeroVector;
};

class VectorWithMatrixTest : public Vec4Test {
public:
    Mat4 matrix;

    void SetUp() override {
        Vec4Test::SetUp();
        setDefaultMatrixValues();
    }

    void setDefaultMatrixValues() {
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

TEST_F(Vec4Test, ConstructorArgumentsSetXYZW) {
    float x(1);
    float y(2);
    float z(3);
    vector = Vec4(x, y, z);
    ASSERT_EQ(x, vector.x);
    ASSERT_EQ(y, vector.y);
    ASSERT_EQ(z, vector.z);
}

TEST_F(Vec4Test, SettersGettersXYZW) {
    ASSERT_EQ(XV1, vector.x);
    ASSERT_EQ(YV1, vector.y);
    ASSERT_EQ(ZV1, vector.z);
}

TEST_F(Vec4Test, AfterConstructed_lengthIsCalculated) {
    ASSERT_EQ(sqrtf(XV1 * XV1 + YV1 * YV1 + ZV1 * ZV1), vector.length());
}

TEST_F(Vec4Test, SettingLength_changesXYZProperly) {
    float currentLength(vector.length());
    float newLength(currentLength + 2);
    float ratio(currentLength / newLength);
    vector.setLength(newLength);

    ASSERT_EQ(XV1 / ratio, vector.x);
    ASSERT_EQ(YV1 / ratio, vector.y);
    ASSERT_EQ(ZV1 / ratio, vector.z);
}

TEST_F(Vec4Test, Normalize_setsLengthTo1) {
    vector.normalize();

    ASSERT_EQ(1, vector.length());
}

TEST_F(Vec4Test, NormalizeOfXVector_setsXTo1) {
    Vec4 vector(VALUE);
    vector.normalize();

    ASSERT_EQ(1, vector.x);
}

TEST_F(Vec4Test, NormalizeOfYVector_setsYTo1) {
    Vec4 vector(0, VALUE);
    vector.normalize();

    ASSERT_EQ(1, vector.y);
}

TEST_F(Vec4Test, NormalizeOfZVector_setsZTo1) {
    Vec4 vector(0, 0, VALUE);
    vector.normalize();

    ASSERT_EQ(1, vector.z);
}

TEST_F(Vec4Test, SettingX_updatesLength) {
    float oldLength(vector.length());
    vector.x += 1;

    ASSERT_NE(oldLength, vector.length());
}

TEST_F(Vec4Test, SettingY_updatesLength) {
    float oldLength(vector.length());
    vector.y += 1;

    ASSERT_NE(oldLength, vector.length());
}

TEST_F(Vec4Test, SettingZ_updatesLength) {
    float oldLength(vector.length());
    vector.z += 1;

    ASSERT_NE(oldLength, vector.length());
}

TEST_F(Vec4Test, SettingW_doesNotUpdateLength) {
	float oldLength(vector.length());
	vector.w += 1;

	ASSERT_THAT(vector.length(), Eq(oldLength));
}

TEST_F(Vec4Test, MultiplyByScalar) {
    int multiplier(5);

    vector *= multiplier;
    ASSERT_EQ(XV1 * multiplier, vector.x);
    ASSERT_EQ(YV1 * multiplier, vector.y);
    ASSERT_EQ(ZV1 * multiplier, vector.z);
}

TEST_F(Vec4Test, AfterMultiplyByScalar_lengthIsUpdated) {
    float oldLength(vector.length());
    vector *= 5;

    ASSERT_NE(oldLength, vector.length());
}

TEST_F(Vec4Test, CopyAssignment) {
    Vec4 cloneVector = vector;

    ASSERT_EQ(cloneVector.x, vector.x);
    ASSERT_EQ(cloneVector.y, vector.y);
    ASSERT_EQ(cloneVector.z, vector.z);
    ASSERT_EQ(cloneVector.length(), vector.length());
}

TEST_F(ZeroVectorTest, DISABLED_NormalizeThrowsException) {
	ASSERT_ANY_THROW(zeroVector.normalize());
}

TEST_F(ZeroVectorTest, DISABLED_SetLengthThrowsException) {
	ASSERT_ANY_THROW(zeroVector.setLength(2));
}

TEST_F(TwoVectorsTest, Add) {
    Vec4 v2 = vector;
    vector += vector2;
    ASSERT_EQ(XV1 + XV2, vector.x);
    ASSERT_EQ(YV1 + YV2, vector.y);
    ASSERT_EQ(ZV1 + ZV2, vector.z);
    vector = v2 + vector2;
    ASSERT_EQ(XV1 + XV2, vector.x);
    ASSERT_EQ(YV1 + YV2, vector.y);
    ASSERT_EQ(ZV1 + ZV2, vector.z);
}

TEST_F(TwoVectorsTest, AfterAdd_lengthIsUpdated) {
    float oldLength(vector.length());
    vector += vector2;
    ASSERT_NE(oldLength, vector.length());
}

TEST_F(TwoVectorsTest, Subtract) {
    Vec4 v2 = vector;
    vector -= vector2;
    ASSERT_EQ(XV1 - XV2, vector.x);
    ASSERT_EQ(YV1 - YV2, vector.y);
    ASSERT_EQ(ZV1 - ZV2, vector.z);
    vector = v2 - vector2;
    ASSERT_EQ(XV1 - XV2, vector.x);
    ASSERT_EQ(YV1 - YV2, vector.y);
    ASSERT_EQ(ZV1 - ZV2, vector.z);
}

TEST_F(TwoVectorsTest, AfterSubtract_lengthIsUpdated) {
    float oldLength(vector.length());
    vector -= vector2;
    ASSERT_NE(oldLength, vector.length());
}

TEST_F(TwoVectorsTest, DistanceBetween) {
    float distance(Vec4::distanceBetween(vector, vector2));
    vector2 -= vector;
    ASSERT_EQ(vector2.length(), distance);
}

TEST_F(TwoVectorsTest, DotProduct) {
    float expected = vector2.x * vector.x + vector2.y * vector.y + vector2.z * vector.z;
    ASSERT_EQ(expected, Vec4::dotProduct(vector, vector2));
    ASSERT_EQ(expected, vector | vector2);
}

TEST_F(TwoVectorsTest, AngleBetween) {
    float angle(Vec4::angleBetween(vector, vector2));
    vector.normalize();
    vector2.normalize();

    float dotProduct = Vec4::dotProduct(vector, vector2);

    ASSERT_EQ((float) (acosf(dotProduct) * 180 / M_PI), angle);
}

TEST_F(TwoVectorsTest, CrossProduct) {
    float expectedX = vector.y * vector2.z - vector.z * vector2.y;
    float expectedY = vector.z * vector2.x - vector.x * vector2.z;
    float expectedZ = vector.x * vector2.y - vector.y * vector2.x;

    Vec4 crossProduct = Vec4::crossProduct(vector, vector2);
    ASSERT_EQ(expectedX, crossProduct.x);
    ASSERT_EQ(expectedY, crossProduct.y);
    ASSERT_EQ(expectedZ, crossProduct.z);

    crossProduct = vector ^ vector2;
    ASSERT_EQ(expectedX, crossProduct.x);
    ASSERT_EQ(expectedY, crossProduct.y);
    ASSERT_EQ(expectedZ, crossProduct.z);
}

TEST_F(TwoVectorsTest, CcrossProductOfTwoAxisGivesThird) {
    Vec4 xAxis(1);
    Vec4 yAxis(0, 1);
    Vec4 zAxis(0, 0, 1);

    ASSERT_TRUE(Vec4::crossProduct(xAxis, yAxis).equals(zAxis));
    ASSERT_TRUE(Vec4::crossProduct(yAxis, zAxis).equals(xAxis));
    ASSERT_TRUE(Vec4::crossProduct(zAxis, xAxis).equals(yAxis));

    Vec4 xAxisNegative(-1);
    Vec4 yAxisNegative(0, -1);
    Vec4 zAxisNegative(0, 0, -1);

    ASSERT_TRUE(Vec4::crossProduct(yAxis, xAxis).equals(zAxisNegative));
    ASSERT_TRUE(Vec4::crossProduct(zAxis, yAxis).equals(xAxisNegative));
    ASSERT_TRUE(Vec4::crossProduct(xAxis, zAxis).equals(yAxisNegative));
}

TEST_F(TwoVectorsTest, IsEqualToTrue) {
    ASSERT_TRUE(vector.equals(Vec4(XV1, YV1, ZV1)));
}

TEST_F(TwoVectorsTest, IsEqualToFalse) {
    ASSERT_FALSE(vector.equals(vector2));
}

TEST_F(VectorWithMatrixTest, MultiplyByMatrix) {
    vector = vector * matrix;
    assertEquals(vector, XV1 * X1 + YV1 * X2 + ZV1 * X3, XV1 * Y1 + YV1 * Y2 + ZV1 * Y3,
            XV1 * Z1 + YV1 * Z2 + ZV1 * Z3);
    setDefaultValues();
    vector *= matrix;
    assertEquals(vector, XV1 * X1 + YV1 * X2 + ZV1 * X3, XV1 * Y1 + YV1 * Y2 + ZV1 * Y3,
                 XV1 * Z1 + YV1 * Z2 + ZV1 * Z3);
}

TEST_F(VectorWithMatrixTest, AfterMultiplyByMatrix_lengthIsUpdated) {
    float oldLength(vector.length());
    vector *= matrix;
    ASSERT_NE(oldLength, vector.length());
}

TEST_F(VectorWithMatrixTest, bla) {
	int xt = 4;
	int yt = 5;
	int zt = 6;
	matrix.translate(xt, yt, zt);
	vector.w = 1;
	vector *= matrix;

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
	vector.w = 0;
	vector *= matrix;

	float x = XV1 * X1 + YV1 * X2 + ZV1 * X3;
	float y = XV1 * Y1 + YV1 * Y2 + ZV1 * Y3;
	float z = XV1 * Z1 + YV1 * Z2 + ZV1 * Z3;
	assertEquals(vector, x, y, z);
}

