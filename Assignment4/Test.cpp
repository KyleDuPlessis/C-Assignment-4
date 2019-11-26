//=====================================================================================
// Name        : Test.cpp
// Author      : Kyle du Plessis [DPLKYL002]
// Date:       : 16/04/2019
// Description : An image processing tool to manipulate 2D arrays of numbers (images)
// 				 using various operations - written in C++, Ansi-style
//=====================================================================================

#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "Image.h"

using namespace std;

//-a I1 I2 (add I1 and I2)
TEST_CASE("TESTING ADDITION:") {

	// generate random colour image
	unsigned char* tempArr1 = new unsigned char[16];

	for (int k = 0; k < 8; k++) {

		tempArr1[k] = (rand() % 95) + 160;

	}

	for (int k = 8; k < 16; k++) {

		tempArr1[k] = rand() % 160;

	}

	DPLKYL002::Image t(4, 4, tempArr1);

	// THRESHOLD
	DPLKYL002::Image a = t * 160;

	// INVERT
	DPLKYL002::Image b = !a;

	// generate plain white image
	unsigned char* tempArr2 = new unsigned char[16];

	for (int k = 0; k < 16; k++) {

		tempArr2[k] = 255;

	}

	DPLKYL002::Image x(4, 4, tempArr2);

	DPLKYL002::Image y(t + x); // add random colour image and plain white image

	REQUIRE(y == x); // verify wraps to 255

	DPLKYL002::Image z(b + a); // add image and its inverse

	REQUIRE(z == x); // verify addition produces plain white image

}

//-s I1 I2 (subtract I2 from I1)
TEST_CASE("TESTING SUBTRACTION:") {

	// generate plain black image
	unsigned char* tempArr1 = new unsigned char[16];

	for (int k = 0; k < 16; k++) {

		tempArr1[k] = 0;

	}

	DPLKYL002::Image x(4, 4, tempArr1);

	// generate random colour image
	unsigned char* tempArr2 = new unsigned char[16];

	for (int k = 0; k < 16; k++) {

		tempArr2[k] = rand() % 255;

	}

	DPLKYL002::Image y(4, 4, tempArr2);

	// generate plain white image
	unsigned char* tempArr3 = new unsigned char[16];

	for (int k = 0; k < 16; k++) {

		tempArr3[k] = 255;

	}

	DPLKYL002::Image z(4, 4, tempArr3);

	DPLKYL002::Image d = y - z;

	REQUIRE(d == x); // verify subtraction wraps to 0

}

//-i I1 (invert I1)
TEST_CASE("TESTING INVERSION:") {

	// generate random colour image
	unsigned char* tempArr1 = new unsigned char[16];

	for (int k = 0; k < 8; k++) {

		tempArr1[k] = (rand() % 95) + 160;

	}

	for (int k = 8; k < 16; k++) {

		tempArr1[k] = rand() % 160;

	}

	DPLKYL002::Image a(4, 4, tempArr1);

	// THRESHOLD
	DPLKYL002::Image t = a * 160;

	// INVERT
	DPLKYL002::Image i1 = !t;

	// INVERT
	DPLKYL002::Image i2 = !i1;

	REQUIRE(i2 == t); // verify result of two inversions equal to original image

}

//-l I1 I2 (mask I1 with I2)
TEST_CASE("TESTING MASK:") {

	// generate random colour image
	unsigned char* tempArr1 = new unsigned char[16];

	for (int k = 0; k < 8; k++) {

		tempArr1[k] = 161;

	}

	for (int k = 8; k < 16; k++) {
		tempArr1[k] = 0;
	}

	DPLKYL002::Image t(4, 4, tempArr1);

	// THRESHOLD
	DPLKYL002::Image m1 = t * 160;

	// INVERT
	DPLKYL002::Image m2 = !m1;

	unsigned char* tempArr2 = new unsigned char[16];

	for (int k = 0; k < 16; k++) {

		tempArr2[k] = rand() % 255;

	}

	DPLKYL002::Image t1(4, 4, tempArr2);

	// MASK
	DPLKYL002::Image i1 = t1 / m1;

	// MASK
	DPLKYL002::Image i2 = t1 / m2;

	// ADD
	DPLKYL002::Image p = i1 + i2;

	REQUIRE(p == t1); // verify addition of result of two inverse maskings equal to original image
}

//-t I1 f (threshold I1 with integer value f)
TEST_CASE("TESTING THRESHOLD:") {

	// generate random colour image
	unsigned char* tempArr1 = new unsigned char[16];

	for (int k = 0; k < 8; k++) {

		tempArr1[k] = (rand() % 95) + 160;

	}

	for (int k = 8; k < 16; k++) {

		tempArr1[k] = rand() % 160;

	}

	// generate upper half white and lower half black image
	unsigned char* tempArr2 = new unsigned char[16];

	for (int k = 0; k < 8; k++) {

		tempArr2[k] = 255;

	}

	for (int k = 8; k < 16; k++) {

		tempArr2[k] = 0;

	}

	DPLKYL002::Image m(4, 4, tempArr1);

	// THRESHOLD
	DPLKYL002::Image m1 = m * 160;

	DPLKYL002::Image m2(4, 4, tempArr2);

	REQUIRE(m1 == m2); // verify upper half white and lower half black after threshold operation

}
