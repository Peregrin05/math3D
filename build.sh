#!/usr/bin/env bash
g++ -Wall -std=c++11 math3D/core/Matrix3D.cpp math3D/core/Vector3D.cpp math3D/orientation/EulerAngles.cpp math3D/orientation/Orientation.cpp math3D/orientation/Quaternion.cpp -c
if [[ -d "build" && ! -L "build" ]] ; then
    rm -r build
fi
mkdir build
mkdir build/include
mkdir build/include/math3D
mkdir build/include/math3D/core
mkdir build/include/math3D/orientation
cp -r math3D/core/*.h build/include/math3D/core
cp -r math3D/orientation/*.h build/include/math3D/orientation
ar rcs build/libmath3D.a EulerAngles.o Matrix3D.o Orientation.o Quaternion.o Vector3D.o
rm *.o
echo "build is done!"
