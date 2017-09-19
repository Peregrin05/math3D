#define _USE_MATH_DEFINES
#include <cmath>
#include <gmock/gmock.h>
#include "Orientation.h"

using namespace flash::math;

const static float radialMult = (float const) (M_PI / 180);

class OrientationTest : public testing::Test {
public:
	void SetUp() override {
	}

	void assertShortestDifference(float angle1, float angle2, float difference) {
        const float radian1 = angle1 * radialMult;
		const float radian2 = angle2 * radialMult;
		const float radianDifference = difference * radialMult;
        const float result = Orientation::getShortestDifference(radian1, radian2);
        ASSERT_THAT(radianDifference, testing::FloatNear(result, 0.0001f));
	}
};

TEST_F(OrientationTest, GetShortestDifference) {
	assertShortestDifference(-170, 170, -20);
	assertShortestDifference(-90, 45, 135);
	assertShortestDifference(0, 90, 90);
	assertShortestDifference(-90, -150, -60);
}