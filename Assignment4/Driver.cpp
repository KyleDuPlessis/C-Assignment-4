//=====================================================================================
// Name        : Driver.cpp
// Author      : Kyle du Plessis [DPLKYL002]
// Date:       : 16/04/2019
// Description : An image processing tool to manipulate 2D arrays of numbers (images)
// 				 using various operations - written in C++, Ansi-style
//=====================================================================================

#include <iostream>
#include <sstream>
#include <string>

#include "Image.h"

using namespace std;

// main function
int main(int argc, char* argv[]) { // argc and argv values passed into main

	// argc - number of all items on command line
	// argv array - contains simple C-strings for each of these items
	// argv[0] is always the application name, and argv[1] the first argument

	string imageOp, oFileName, input1, input2, fValue;

	if (argc == 4 || argc == 5) {

		// image operation
		imageOp = string(argv[1]);

		//-a I1 I2 (add I1 and I2)
		if (imageOp == "-a") {

			oFileName = string(argv[4]);

			input1 = string(argv[2]);

			input2 = string(argv[3]);

			//-s I1 I2 (subtract I2 from I1)
		} else if (imageOp == "-s") {

			oFileName = string(argv[4]);

			input1 = string(argv[2]);

			input2 = string(argv[3]);

			//-i I1 (invert I1)
		} else if (imageOp == "-i") {

			oFileName = string(argv[3]);

			input1 = string(argv[2]);

			//-l I1 I2 (mask I1 with I2)
		} else if (imageOp == "-l") {

			oFileName = string(argv[4]);

			input1 = string(argv[2]);

			input2 = string(argv[3]);

			//-t I1 f (threshold I1 with integer value f)
		} else if (imageOp == "-t") {

			oFileName = string(argv[4]);

			input1 = string(argv[2]);

			fValue = string(argv[3]);


		}

	}

	stringstream ssf(fValue);
	int fVal;
	ssf >> fVal;

	//-a I1 I2 (add I1 and I2)
	if (imageOp == "-a") {

		DPLKYL002::Image x(input1);

		DPLKYL002::Image y(input2);

		DPLKYL002::Image total = x + y;

		total.save(oFileName);

		//-s I1 I2 (subtract I2 from I1)
	} else if (imageOp == "-s") {

		DPLKYL002::Image x(input1);

		DPLKYL002::Image y(input2);

		DPLKYL002::Image total = x - y;

		total.save(oFileName);

		//-i I1 (invert I1)
	} else if (imageOp == "-i") {

		DPLKYL002::Image x(input1);

		DPLKYL002::Image i = !x;

		i.save(oFileName);

		//-l I1 I2 (mask I1 with I2)
	} else if (imageOp == "-l") {

		DPLKYL002::Image x(input1);

		DPLKYL002::Image y(input2);

		DPLKYL002::Image m = x / y;

		m.save(oFileName);

		//-t I1 f (threshold I1 with integer value f)
	} else if (imageOp == "-t") {

		DPLKYL002::Image x(input1);

		DPLKYL002::Image t = x * fVal;

		t.save(oFileName);


	}

	return 0;

}
