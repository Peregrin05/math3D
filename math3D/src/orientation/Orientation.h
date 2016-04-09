//
// Created by Islam Aliev on 28/12/14.
// Copyright (c) 2014 me. All rights reserved.
//


#ifndef __Orientation_H_
#define __Orientation_H_


class Orientation {
public:
	float static getShortestDifference(float angle1, float angle2);
private:
    float static _wrapPi(float theta);
};


#endif //__Orientation_H_
