#include <gmock/gmock-matchers.h>
#include "EulerAngles.h"

using namespace testing;
using namespace flash::math;

float const DELTA = 0.01f;

class EulerAnglesTest : public testing::Test {
public:
	EulerAngles eulerAngles;

	void SetUp() override {
		reset();
	}

	void set(float h, float p, float b) {
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
    void assertCanonizeHeading(float initHeading, float expHeading) {
        eulerAngles.heading(initHeading);
        eulerAngles.canonize();

        ASSERT_EQ(expHeading, eulerAngles.heading());
    }

    void assertCanonizeBank(float initBank, float expBank) {
        eulerAngles.bank(initBank);
        eulerAngles.canonize();

        ASSERT_EQ(expBank, eulerAngles.bank());
    }

    void assertCanonizePitch(float initPitch, float expPitch) {
        eulerAngles.pitch(initPitch);
        eulerAngles.canonize();

        ASSERT_EQ(expPitch, eulerAngles.pitch());
    }

    void assertCanonizeComplexPitch(float initPitch, float expPitch) {
        reset();

        eulerAngles.pitch(initPitch);
        eulerAngles.canonize();

        ASSERT_EQ(expPitch, eulerAngles.pitch());
        ASSERT_EQ(180, eulerAngles.heading());
        ASSERT_EQ(180, eulerAngles.bank());
    }

    void assertCanonizeComplex(float iH, float iP, float iB, float eH, float eP, float eB) {
        reset();

        eulerAngles.heading(iH);
        eulerAngles.pitch(iP);
        eulerAngles.bank(iB);
        eulerAngles.canonize();

        ASSERT_EQ(eH, eulerAngles.heading());
        ASSERT_EQ(eP, eulerAngles.pitch());
        ASSERT_EQ(eB, eulerAngles.bank());
    }
};

class EulerAnglesConvertToMatrixTest : public EulerAnglesTest {
public:
	void assertMatrix(float x1, float y1, float z1, float x2, float y2, float z2, float x3,
			float y3, float z3) {
		assertClose(eulerAngles.toUprightMatrix(), x1, y1, z1, x2, y2, z2, x3, y3, z3);
		assertClose(eulerAngles.toObjectMatrix(), x1, x2, x3, y1, y2, y3, z1, z2, z3);
        Mat4 um(x1, y1, z1, x2, y2, z2, x3, y3, z3);
        Mat4 om(x1, x2, x3, y1, y2, y3, z1, z2, z3);
        /*EulerAngles ue = EulerAngles::fromUprightMatrix(um);
        EulerAngles oe = EulerAngles::fromObjectMatrix(om);
        ASSERT_THAT(eulerAngles.heading(), FloatNear(ue.heading(), DELTA));
        ASSERT_THAT(eulerAngles.pitch(), FloatNear(ue.pitch(), DELTA));
        ASSERT_THAT(eulerAngles.bank(), FloatNear(ue.bank(), DELTA));

        ASSERT_THAT(eulerAngles.heading(), FloatNear(oe.heading(), DELTA));
        ASSERT_THAT(eulerAngles.pitch(), FloatNear(oe.pitch(), DELTA));
        ASSERT_THAT(eulerAngles.bank(), FloatNear(oe.bank(), DELTA));*/
	}

	void assertClose(Mat4 matrix, float x1, float y1, float z1, float x2, float y2, float z2, float x3,
			float y3, float z3) {
		ASSERT_THAT(matrix.x1(), FloatNear(x1, DELTA));
		ASSERT_THAT(matrix.y1(), FloatNear(y1, DELTA));
		ASSERT_THAT(matrix.z1(), FloatNear(z1, DELTA));
		ASSERT_THAT(matrix.x2(), FloatNear(x2, DELTA));
		ASSERT_THAT(matrix.y2(), FloatNear(y2, DELTA));
		ASSERT_THAT(matrix.z2(), FloatNear(z2, DELTA));
		ASSERT_THAT(matrix.x3(), FloatNear(x3, DELTA));
		ASSERT_THAT(matrix.y3(), FloatNear(y3, DELTA));
		ASSERT_THAT(matrix.z3(), FloatNear(z3, DELTA));
	}
};

TEST_F(EulerAnglesCanonizeTest, IsCanonicalFalse) {
    eulerAngles.heading(-180);
    ASSERT_FALSE(eulerAngles.isCanonical());

    eulerAngles.heading(180.01f);
    ASSERT_FALSE(eulerAngles.isCanonical());

    reset();

    eulerAngles.pitch(-90.01f);
    ASSERT_FALSE(eulerAngles.isCanonical());

    eulerAngles.pitch(90.01f);
    ASSERT_FALSE(eulerAngles.isCanonical());

    reset();

    eulerAngles.bank(-180);
    ASSERT_FALSE(eulerAngles.isCanonical());

    eulerAngles.bank(180.01f);
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
	assertMatrix(1, 0, 0, 0, -0.707f, 0.707f, 0, -0.707f, -0.707f);

	set(-135, -45, 0);
	assertMatrix(-0.707f, 0, 0.707f, 0.5f, 0.707f, 0.5f, -0.5f, 0.707f, -0.5f);

	set(-45, -90, 0);
	assertMatrix(0.707f, 0, 0.707f, 0.707f, 0, -0.707f, 0, 1, 0);

	set(123, 33.5f, -32.7f);
	assertMatrix(-0.713f, -0.45f, -0.538f, 0.091f, 0.702f, -0.706f, 0.696f, -0.552f, -0.46f);

	set(-30, 30, 70);
	assertMatrix(0.061f, 0.814f, 0.578f, -0.9f, 0.296f, -0.322f, -0.433f, -0.5f, 0.75f);
}

TEST_F(EulerAnglesConvertToMatrixTest, ConvertToMatrixBlaBla) {
    set(-135, -45, 0);
    Mat4 m(-0.707f, 0, 0.707f, 0.5f, 0.707f, 0.5f, -0.5f, 0.707f, -0.5f);
    eulerAngles = EulerAngles::fromUprightMatrix(m);
    ASSERT_THAT(eulerAngles.heading(), FloatNear(-135, DELTA));
    ASSERT_THAT(eulerAngles.pitch(), FloatNear(-45, DELTA));
    ASSERT_THAT(eulerAngles.bank(), FloatNear(0, DELTA));
}

TEST_F(EulerAnglesConvertToMatrixTest, ConvertToMatrixBlaBlaBla) {
    set(-135, -45, 0);
    Mat4 m(-0.707f, 0, 0.707f, 0.5f, 0.707f, 0.5f, -0.5f, 0.707f, -0.5f);
    m.transpose();
    eulerAngles = EulerAngles::fromObjectMatrix(m);
    ASSERT_THAT(eulerAngles.heading(), FloatNear(-135, DELTA));
    ASSERT_THAT(eulerAngles.pitch(), FloatNear(-45, DELTA));
    ASSERT_THAT(eulerAngles.bank(), FloatNear(0, DELTA));

    set(123, 33.5f, -32.7f);
    m = Mat4(-0.713f, -0.45f, -0.538f, 0.091f, 0.702f, -0.706f, 0.696f, -0.552f, -0.46f);
    m.transpose();
    eulerAngles = EulerAngles::fromObjectMatrix(m);
    ASSERT_THAT(eulerAngles.heading(), FloatNear(123, 0.5));
    ASSERT_THAT(eulerAngles.pitch(), FloatNear(33.5f, DELTA));
    ASSERT_THAT(eulerAngles.bank(), FloatNear(-32.7f, 0.3f));
}

// TODO: figure out why fromObjectMatrix() and fromUprightMatrix() are flipping sign
/*
TEST_F(EulerAnglesConvertToMatrixTest, FromUprightMatrix) {
    set(180, 45, 180);
    Mat4 matrix = eulerAngles.toUprightMatrix();
    eulerAngles = EulerAngles::fromUprightMatrix(matrix);
    ASSERT_THAT(eulerAngles.heading(), FloatNear(180, DELTA));
    ASSERT_THAT(eulerAngles.pitch(), FloatNear(45, DELTA));
    ASSERT_THAT(eulerAngles.bank(), FloatNear(180, DELTA));
}

TEST_F(EulerAnglesConvertToMatrixTest, FromObjectMatrix) {
	set(180, 45, 180);
	Mat4 oMatrix = eulerAngles.toObjectMatrix();
	eulerAngles = EulerAngles::fromObjectMatrix(oMatrix);
	ASSERT_THAT(eulerAngles.heading(), FloatNear(180, DELTA));
	ASSERT_THAT(eulerAngles.pitch(), FloatNear(45, DELTA));
	ASSERT_THAT(eulerAngles.bank(), FloatNear(180, DELTA));
}*/
