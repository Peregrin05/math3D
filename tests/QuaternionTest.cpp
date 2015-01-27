#include <gmock/gmock-matchers.h>
#include "gtest/gtest.h"
#include "EulerAngles.h"

using namespace testing;

double const DELTA = 0.006;
double const EA_DELTA = 0.03;

class QuaternionTest : public testing::Test {
public:
	Quaternion quaternion = Quaternion();

	void SetUp() override {
		reset();
	}

	void set(double const w, double const x, double const y, double const z) {
		quaternion.w(w);
		quaternion.x(x);
		quaternion.y(y);
		quaternion.z(z);
	}

	void setAxisAngle(float const angle, double const vx, double const vy, double const vz) {
		double toRadians = M_PI / 180;
		quaternion = Quaternion(angle * toRadians, Vector3D(vx, vy, vz));
	}

	void reset() {
		quaternion.w(1);
		quaternion.x(0);
		quaternion.y(0);
		quaternion.z(0);
	}

	void assertClose(Quaternion q, double w, double x, double y, double z) {
		ASSERT_THAT(*q.w(), DoubleNear(w, DELTA));
		ASSERT_THAT(*q.x(), DoubleNear(x, DELTA));
		ASSERT_THAT(*q.y(), DoubleNear(y, DELTA));
		ASSERT_THAT(*q.z(), DoubleNear(z, DELTA));
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

	void assertMatrix(double x1, double y1, double z1, double x2, double y2, double z2, double x3,
			double y3, double z3) {
		assertClose(quaternion.toMatrix(), x1, y1, z1, x2, y2, z2, x3, y3, z3);
	}
};

TEST_F(QuaternionTest, VectorConstructor) {
	setAxisAngle(30, 1, 0, 0);
	assertClose(quaternion, 0.966, 0.259, 0, 0);
}

TEST_F(QuaternionTest, ToEulerAngles) {
	set(0.966, 0.259, 0, 0);
	EulerAngles ea = quaternion.uprightToEulerAngles();
	ASSERT_THAT(*ea.heading(), FloatNear(0, EA_DELTA));
	ASSERT_THAT(*ea.pitch(), FloatNear(30, EA_DELTA));
	ASSERT_THAT(*ea.bank(), FloatNear(0, EA_DELTA));
}

TEST_F(QuaternionTest, UprightQuaternionFromEulerAngles) {
	set(0.966, 0.259, 0, 0);
	EulerAngles ea = quaternion.uprightToEulerAngles();
	Quaternion q = ea.toUprightQuaternion();
	assertClose(q, 0.966, 0.259, 0, 0);
}

TEST_F(QuaternionTest, ObjectQuaternionFromEulerAngles) {
	set(0.966, 0.259, 0, 0);
	EulerAngles ea = quaternion.objectToEulerAngles();
	Quaternion q = ea.toObjectQuaternion();
	assertClose(q, 0.966, 0.259, 0, 0);
}

TEST_F(QuaternionTest, ToMatrix) {
	setAxisAngle(98.4, -0.863, -0.357, -0.357);
	assertMatrix(0.707, 0, 0.707, 0.707, 0, -0.707, 0, 1, 0);

	setAxisAngle(0, 0.707, -0.707, 0);
	assertMatrix(1, 0, 0, 0, 1, 0, 0, 0, 1);

	setAxisAngle(87, 0.089, -0.506, 0.857);
	assertMatrix(0.061, 0.814, 0.578, -0.9, 0.296, -0.322, -0.433, -0.5, 0.75);

	setAxisAngle(135, 1, 0, 0);
	assertMatrix(1, 0, 0, 0, -0.707, 0.707, 0, -0.707, -0.707);

	setAxisAngle(261.6, 0.863, 0.357, 0.357);
	assertMatrix(0.707, 0, 0.707, 0.707, 0, -0.707, 0, 1, 0);

	setAxisAngle(139, -0.156, -0.912, -0.378);
	assertMatrix(-0.707, 0, 0.707, 0.5, 0.707, 0.5, -0.5, 0.707, -0.5);

	setAxisAngle(7200, 0, -1, 0);
	assertMatrix(1, 0, 0, 0, 1, 0, 0, 0, 1);

	setAxisAngle(-135, -1, 0, 0);
	assertMatrix(1, 0, 0, 0, -0.707, 0.707, 0, -0.707, -0.707);
}

TEST_F(QuaternionTest, FromMatrix) {
	setAxisAngle(98.4, -0.863, -0.357, -0.357);
	const Matrix3D matrix = quaternion.toMatrix();
	const Quaternion q = Quaternion::fromMatrix(matrix);
	assertClose(q, *q.w(), *q.x(), *q.y(), *q.z());
}

TEST_F(QuaternionTest, Multiplication) {
	quaternion = Quaternion(0.965, 0.149, -0.149, 0.149);
	quaternion = quaternion * quaternion;
	assertClose(quaternion, 0.867, 0.288, -0.288, 0.288);

	quaternion = Quaternion(0.233, 0.06, -0.257, -0.935);
	Quaternion quaternion2 = Quaternion(-0.752, 0.286, 0.374, 0.459);
	Quaternion resultQuaternion = quaternion * quaternion2;
	assertClose(resultQuaternion, 0.333, 0.253, -0.015, 0.906);
}

TEST_F(QuaternionTest, DotProduct) {
	quaternion = Quaternion(0.233, 0.06, -0.257, -0.935);
	Quaternion quaternion2 = Quaternion(-0.752, 0.286, 0.374, 0.459);

	double dotProduct = Quaternion::dotProduct(quaternion, quaternion2);
	ASSERT_THAT(dotProduct, DoubleNear(-0.683, DELTA));
}

TEST_F(QuaternionTest, Difference) {
	quaternion = Quaternion(0.233, 0.06, -0.257, -0.935);
	Quaternion quaternion2 = Quaternion(-0.752, 0.286, 0.374, 0.459);

	Quaternion resultQuaternion = Quaternion::getDifference(quaternion, quaternion2);
	assertClose(resultQuaternion, -0.683, 0.343, -0.401, -0.5);
}

TEST_F(QuaternionTest, Exponentiation) {
	setAxisAngle(90, 1, 0, 0);

	double exponent = 0.33333333;
	quaternion = quaternion.exp(exponent);
	
	assertClose(quaternion, 0.9659, 0.2588, 0, 0);
}

TEST_F(QuaternionTest, Slerp) {
	setAxisAngle(20, 1, 0, 0);
	Quaternion start = quaternion;
	setAxisAngle(40, 1, 0, 0);
	double fraction = 0.5;
	quaternion = start.slerp(quaternion, fraction);

	assertClose(quaternion, 0.9659, 0.2588, 0, 0);
}