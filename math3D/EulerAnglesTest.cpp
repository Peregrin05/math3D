#include <gmock/gmock-matchers.h>
#include "gtest/gtest.h"
#include "EulerAngles.h"

using namespace testing;

class EulerAnglesTest : public testing::Test {
public:
    EulerAngles eulerAngles;

    void SetUp() override {
        reset();
    }

    void reset() {
        eulerAngles.heading(0);
        eulerAngles.pitch(0);
        eulerAngles.bank(0);
    }

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

TEST_F(EulerAnglesTest, IsCanonicalFalse) {
    eulerAngles.heading(-180);
    ASSERT_FALSE(eulerAngles.isCanonical());

    eulerAngles.heading(180.01);
    ASSERT_FALSE(eulerAngles.isCanonical());

    reset();

    eulerAngles.pitch(-90.01);
    ASSERT_FALSE(eulerAngles.isCanonical());

    eulerAngles.pitch(90.01);
    ASSERT_FALSE(eulerAngles.isCanonical());

    reset();

    eulerAngles.bank(-180);
    ASSERT_FALSE(eulerAngles.isCanonical());

    eulerAngles.bank(180.01);
    ASSERT_FALSE(eulerAngles.isCanonical());
}

TEST_F(EulerAnglesTest, IsCanonicalTrue) {
    eulerAngles.heading(-179.9);
    ASSERT_TRUE(eulerAngles.isCanonical());

    eulerAngles.heading(180);
    ASSERT_TRUE(eulerAngles.isCanonical());

    reset();

    eulerAngles.pitch(-90);
    ASSERT_TRUE(eulerAngles.isCanonical());

    eulerAngles.pitch(90);
    ASSERT_TRUE(eulerAngles.isCanonical());

    reset();

    eulerAngles.bank(-179.9);
    ASSERT_TRUE(eulerAngles.isCanonical());

    eulerAngles.bank(180);
    ASSERT_TRUE(eulerAngles.isCanonical());
}

TEST_F(EulerAnglesTest, IsCanonicalGimbalLock) {
    eulerAngles.pitch(-90);
    eulerAngles.bank(1);
    ASSERT_FALSE(eulerAngles.isCanonical());

    eulerAngles.pitch(90);
    ASSERT_FALSE(eulerAngles.isCanonical());
}

TEST_F(EulerAnglesTest, CanonizeHeading) {
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

TEST_F(EulerAnglesTest, CanonizeBank) {
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

TEST_F(EulerAnglesTest, CanonizeInRangePitch) {
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

TEST_F(EulerAnglesTest, CanonizeOutOfRangePitch) {
    assertCanonizeComplexPitch(135, 45);
    assertCanonizeComplexPitch(-135, -45);
    assertCanonizeComplexPitch(100, 80);
    assertCanonizeComplexPitch(-100, -80);
    assertCanonizeComplexPitch(170, 10);
    assertCanonizeComplexPitch(-170, -10);
    assertCanonizeComplexPitch(180, 0);
    assertCanonizeComplexPitch(-180, 0);
}

TEST_F(EulerAnglesTest, CanonizeOutOfRangePitchWidthHeading) {
    assertCanonizeComplex(90, 135, 0, -90, 45, 180);
    assertCanonizeComplex(-10, 100, 0, 170, 80, 180);
    assertCanonizeComplex(-135, 170, 0, 45, 10, 180);
}

TEST_F(EulerAnglesTest, CanonizeOutOfRangePitchWidthBank) {
    assertCanonizeComplex(0, 135, 90, 180, 45, -90);
    assertCanonizeComplex(0, 100, -10, 180, 80, 170);
    assertCanonizeComplex(0, 170, -135, 180, 10, 45);
}

TEST_F(EulerAnglesTest, CanonizeOutOfRangePitchWidthHeadingAndBank) {
    assertCanonizeComplex(10, 135, 90, -170, 45, -90);
    assertCanonizeComplex(110, 100, -10, -70, 80, 170);
    assertCanonizeComplex(-45, 170, -135, 135, 10, 45);
}

TEST_F(EulerAnglesTest, CanonizeGimbalLock) {
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