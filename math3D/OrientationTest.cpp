#include <gtest/gtest.h>
#include <math.h>
#include "Orientation.h"

const static double radialMult = M_PI / 180;

class OrientationTest : public testing::Test {
public:
	void SetUp() override {
	}

	void assertShortestDifference(double const angle1, double const angle2, double const difference) {
		const double radian1 = -170 * radialMult;
		const double radian2 = 170 * radialMult;
		const double radianDifference = -20 * radialMult;
		ASSERT_FLOAT_EQ(radianDifference, Orientation::getShortestDifference(radian1, radian2));
	}
};

TEST_F(OrientationTest, GetShortestDifference) {
	assertShortestDifference(-170, 170, -20);
	assertShortestDifference(-90, 45, 135);
	assertShortestDifference(0, 90, 90);
	assertShortestDifference(-90, -150, -60);
}