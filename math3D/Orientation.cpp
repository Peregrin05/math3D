//
// Created by Islam Aliev on 28/12/14.
// Copyright (c) 2014 me. All rights reserved.
//

#include <math.h>
#include "Orientation.h"

double _wrapPi(double theta);

const static double pi = M_PI;
const static double pi2 = 2 * M_PI;

double Orientation::getShortestDifference(double const &angle1, double const &angle2) {
	return _wrapPi(angle2 - angle1);
}

double _wrapPi(double theta) {
	// Check if already in range
	if (fabs(theta) > pi) {
		// out of range. Determine how many "revolutions" we need to add
		double revolutions = floor((theta + pi) / pi2);
		theta -= revolutions * pi2;
	}
	return theta;
}
