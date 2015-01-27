#include <gmock/gmock-matchers.h>
#include "gtest/gtest.h"
#include "EulerAngles.h"

using namespace testing;

double const DELTA = 0.006;

class EulerAnglesTest : public testing::Test {
public:
	EulerAngles eulerAngles;

	void SetUp() override {
		reset();
	}

	void set(float const h, float const p, float const b) {
		eulerAngles.heading(h);
		eulerAngles.pitch(p);
		eulerAngles.bank(b);
	}

	void reset() {
		eulerAngles.heading(0);
		eulerAngles.pitch(0);
		eulerAngles.bank(0);
	}
};

class EulerAnglesCanonizeTest : public EulerAnglesTest {
public :
    void assertCanonizeHeading(double initHeading, double expHeading) {
        eulerAngles.heading(initHeading);
        eulerAngles.canonize();

        ASSERT_EQ(expHeading, *eulerAngles.heading());
    }

    void assertCanonizeBank(double initBank, double expBank) {
        eulerAngles.bank(initBank);
        eulerAngles.canonize();

        ASSERT_EQ(expBank, *eulerAngles.bank());
    }

    void assertCanonizePitch(double initPitch, double expPitch) {
        eulerAngles.pitch(initPitch);
        eulerAngles.canonize();

        ASSERT_EQ(expPitch, *eulerAngles.pitch());
    }

    void assertCanonizeComplexPitch(double initPitch, double expPitch) {
        reset();

        eulerAngles.pitch(initPitch);
        eulerAngles.canonize();

        ASSERT_EQ(expPitch, *eulerAngles.pitch());
        ASSERT_EQ(180, *eulerAngles.heading());
        ASSERT_EQ(180, *eulerAngles.bank());
    }

    void assertCanonizeComplex(double iH, double iP, double iB, double eH, double eP, double eB) {
        reset();

        eulerAngles.heading(iH);
        eulerAngles.pitch(iP);
        eulerAngles.bank(iB);
        eulerAngles.canonize();

        ASSERT_EQ(eH, *eulerAngles.heading());
        ASSERT_EQ(eP, *eulerAngles.pitch());
        ASSERT_EQ(eB, *eulerAngles.bank());
    }
};

class EulerAnglesConvertToMatrixTest : public EulerAnglesTest {
public:
	void assertMatrix(double x1, double y1, double z1, double x2, double y2, double z2, double x3,
			double y3, double z3, double multiplier = 1) {
		assertClose(eulerAngles.toUprightMatrix(), x1, y1, z1, x2, y2, z2, x3, y3, z3);
		assertClose(eulerAngles.toObjectMatrix(), x1, x2, x3, y1, y2, y3, z1, z2, z3);
	}

	void assertClose(Matrix3D matrix, double x1, double y1, double z1, double x2, double y2, double z2, double x3,
			double y3, double z3) {
		ASSERT_THAT(*matrix.x1(), DoubleNear(x1, DELTA));
		ASSERT_THAT(*matrix.y1(), DoubleNear(y1, DELTA));
		ASSERT_THAT(*matrix.z1(), DoubleNear(z1, DELTA));
		ASSERT_THAT(*matrix.x2(), DoubleNear(x2, DELTA));
		ASSERT_THAT(*matrix.y2(), DoubleNear(y2, DELTA));
		ASSERT_THAT(*matrix.z2(), DoubleNear(z2, DELTA));
		ASSERT_THAT(*matrix.x3(), DoubleNear(x3, DELTA));
		ASSERT_THAT(*matrix.y3(), DoubleNear(y3, DELTA));
		ASSERT_THAT(*matrix.z3(), DoubleNear(z3, DELTA));
	}
};

TEST_F(EulerAnglesCanonizeTest, IsCanonicalFalse) {
    eulerAngles.heading(-180);
    ASSERT_FALSE(eulerAngles.isCanonical());

    eulerAngles.heading(180.01);
    ASSERT_FALSE(eulerAngles.isCanonical());

    reset();

    eulerAngles.pitch(-90.01f);
    ASSERT_FALSE(eulerAngles.isCanonical());

    eulerAngles.pitch(90.01);
    ASSERT_FALSE(eulerAngles.isCanonical());

    reset();

    eulerAngles.bank(-180);
    ASSERT_FALSE(eulerAngles.isCanonical());

    eulerAngles.bank(180.01);
    ASSERT_FALSE(eulerAngles.isCanonical());
}

TEST_F(EulerAnglesCanonizeTest, IsCanonicalTrue) {
    eulerAngles.heading(-179.9f);
    ASSERT_TRUE(eulerAngles.isCanonical());

    eulerAngles.heading(180);
    ASSERT_TRUE(eulerAngles.isCanonical());

    reset();

    eulerAngles.pitch(-90);
    ASSERT_TRUE(eulerAngles.isCanonical());

    eulerAngles.pitch(90);
    ASSERT_TRUE(eulerAngles.isCanonical());

    reset();

    eulerAngles.bank(-179.9f);
    ASSERT_TRUE(eulerAngles.isCanonical());

    eulerAngles.bank(180);
    ASSERT_TRUE(eulerAngles.isCanonical());
}

TEST_F(EulerAnglesCanonizeTest, IsCanonicalGimbalLock) {
    eulerAngles.pitch(-90);
    eulerAngles.bank(1);
    ASSERT_FALSE(eulerAngles.isCanonical());

    eulerAngles.pitch(90);
    ASSERT_FALSE(eulerAngles.isCanonical());
}

TEST_F(EulerAnglesCanonizeTest, CanonizeHeading) {
    assertCanonizeHeading(10, 10);
    assertCanonizeHeading(380, 20);
    assertCanonizeHeading(-10, -10);
    assertCanonizeHeading(-200, 160);
    assertCanonizeHeading(200, -160);
    assertCanonizeHeading(-170, -170);
    assertCanonizeHeading(170, 170);
    assertCanonizeHeading(-380, -20);
    assertCanonizeHeading(750, 30);
    assertCanonizeHeading(-750, -30);
    assertCanonizeHeading(180, 180);
    assertCanonizeHeading(-180, 180);
    assertCanonizeHeading(-540, 180);
}

TEST_F(EulerAnglesCanonizeTest, CanonizeBank) {
    assertCanonizeBank(10, 10);
    assertCanonizeBank(380, 20);
    assertCanonizeBank(-10, -10);
    assertCanonizeBank(-200, 160);
    assertCanonizeBank(200, -160);
    assertCanonizeBank(-170, -170);
    assertCanonizeBank(170, 170);
    assertCanonizeBank(-380, -20);
    assertCanonizeBank(750, 30);
    assertCanonizeBank(-750, -30);
    assertCanonizeBank(180, 180);
    assertCanonizeBank(-180, 180);
    assertCanonizeBank(-540, 180);
}

TEST_F(EulerAnglesCanonizeTest, CanonizeInRangePitch) {
    assertCanonizePitch(0, 0);
    assertCanonizePitch(90, 90);
    assertCanonizePitch(80, 80);
    assertCanonizePitch(-80, -80);
    assertCanonizePitch(-90, -90);
    assertCanonizePitch(450, 90); // 360
    assertCanonizePitch(440, 80); // 360
    assertCanonizePitch(-440, -80); // -360
    assertCanonizePitch(-450, -90); // -360
    assertCanonizePitch(810, 90); // 360 * 2
    assertCanonizePitch(800, 80); // 360 * 2
    assertCanonizePitch(-800, -80); // -360 * 2
    assertCanonizePitch(-810, -90); // -360 * 2
}

TEST_F(EulerAnglesCanonizeTest, CanonizeOutOfRangePitch) {
    assertCanonizeComplexPitch(135, 45);
    assertCanonizeComplexPitch(-135, -45);
    assertCanonizeComplexPitch(100, 80);
    assertCanonizeComplexPitch(-100, -80);
    assertCanonizeComplexPitch(170, 10);
    assertCanonizeComplexPitch(-170, -10);
    assertCanonizeComplexPitch(180, 0);
    assertCanonizeComplexPitch(-180, 0);
}

TEST_F(EulerAnglesCanonizeTest, CanonizeOutOfRangePitchWidthHeading) {
    assertCanonizeComplex(90, 135, 0, -90, 45, 180);
    assertCanonizeComplex(-10, 100, 0, 170, 80, 180);
    assertCanonizeComplex(-135, 170, 0, 45, 10, 180);
}

TEST_F(EulerAnglesCanonizeTest, CanonizeOutOfRangePitchWidthBank) {
    assertCanonizeComplex(0, 135, 90, 180, 45, -90);
    assertCanonizeComplex(0, 100, -10, 180, 80, 170);
    assertCanonizeComplex(0, 170, -135, 180, 10, 45);
}

TEST_F(EulerAnglesCanonizeTest, CanonizeOutOfRangePitchWidthHeadingAndBank) {
    assertCanonizeComplex(10, 135, 90, -170, 45, -90);
    assertCanonizeComplex(110, 100, -10, -70, 80, 170);
    assertCanonizeComplex(-45, 170, -135, 135, 10, 45);
}

TEST_F(EulerAnglesCanonizeTest, CanonizeGimbalLock) {
    assertCanonizeComplex(90, 90, 90, 180, 90, 0);
    assertCanonizeComplex(90, 90, -90, 0, 90, 0);
    assertCanonizeComplex(30, 90, 30, 60, 90, 0);
    assertCanonizeComplex(45, 90, 45, 90, 90, 0);
    assertCanonizeComplex(-90, 90, -135, 135, 90, 0);

    assertCanonizeComplex(90, -90, 90, 0, -90, 0);
    assertCanonizeComplex(-90, -90, -90, 0, -90, 0);
    assertCanonizeComplex(90, -90, -90, 180, -90, 0);
    assertCanonizeComplex(-45, -90, 180, 135, -90, 0);
    assertCanonizeComplex(-30, -90, 10, -40, -90, 0);
}

TEST_F(EulerAnglesConvertToMatrixTest, ConvertToMatrix) {
	set(0, 0, 0);
	assertMatrix(1, 0, 0, 0, 1, 0, 0, 0, 1);

	set(180, 45, 180);
	assertMatrix(1, 0, 0, 0, -0.707, 0.707, 0, -0.707, -0.707);

	set(-135, -45, 0);
	assertMatrix(-0.707, 0, 0.707, 0.5, 0.707, 0.5, -0.5, 0.707, -0.5);

	set(-45, -90, 0);
	assertMatrix(0.707, 0, 0.707, 0.707, 0, -0.707, 0, 1, 0);

	set(123, 33.5f, -32.7f);
	assertMatrix(-0.713, -0.45, -0.538, 0.091, 0.702, -0.706, 0.696, -0.552, -0.46);

	set(-30, 30, 70);
	assertMatrix(0.061, 0.814, 0.578, -0.9, 0.296, -0.322, -0.433, -0.5, 0.75);
}

TEST_F(EulerAnglesConvertToMatrixTest, FromUprightMatrix) {
	set(180, 45, 180);
	Matrix3D matrix = eulerAngles.toUprightMatrix();
	eulerAngles = EulerAngles::fromUprightMatrix(matrix);
	ASSERT_THAT(*eulerAngles.heading(), FloatNear(180, DELTA));
	ASSERT_THAT(*eulerAngles.pitch(), FloatNear(45, DELTA));
	ASSERT_THAT(*eulerAngles.bank(), FloatNear(180, DELTA));
}

TEST_F(EulerAnglesConvertToMatrixTest, FromObjectMatrix) {
	set(180, 45, 180);
	Matrix3D oMatrix = eulerAngles.toObjectMatrix();
	eulerAngles = EulerAngles::fromObjectMatrix(oMatrix);
	ASSERT_THAT(*eulerAngles.heading(), FloatNear(180, DELTA));
	ASSERT_THAT(*eulerAngles.pitch(), FloatNear(45, DELTA));
	ASSERT_THAT(*eulerAngles.bank(), FloatNear(180, DELTA));
}