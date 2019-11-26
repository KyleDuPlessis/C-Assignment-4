//=====================================================================================
// Name        : Image.cpp
// Author      : Kyle du Plessis [DPLKYL002]
// Date:       : 16/04/2019
// Description : An image processing tool to manipulate 2D arrays of numbers (images)
// 				 using various operations - written in C++, Ansi-style
//=====================================================================================

#include "Image.h"

#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

// THE BIG 6

// CONSTRUCTORS
DPLKYL002::Image::Image(int w, int h, unsigned char* d) :
		width(w), height(h) {

	data.reset(d);

}

DPLKYL002::Image::Image(string imgName) {

	load(imgName);

}

// DESTRUCTOR
DPLKYL002::Image::~Image() {

	width = 0;

	height = 0;

	data = nullptr;

}

// MOVE CONTRUCTOR
DPLKYL002::Image::Image(DPLKYL002::Image&& oImg) :
		width(oImg.width), height(oImg.height) {

	unsigned char* tmpArr = new unsigned char[width * height];

	for (int k = 0; k < height * width; k++) {

		tmpArr[k] = oImg.data[k];

	}

	data.reset(tmpArr);

	oImg.height = 0;

	oImg.width = 0;

	oImg.data = nullptr;

}

// MOVE ASSIGNMENT OPERATOR
DPLKYL002::Image& DPLKYL002::Image::operator=(DPLKYL002::Image&& oImg) {

	if (this == &oImg){

		return *this;

	}

	if (data != nullptr){

		data = nullptr;

	}

	width = oImg.width;

	height = oImg.height;

	unsigned char* tmpArr = new unsigned char[width * height];

	for (int k = 0; k < height * width; k++) {

		tmpArr[k] = oImg.data[k];

	}

	data.reset(tmpArr);

	oImg.data = nullptr;

	oImg.height = 0;

	oImg.width = 0;

	return *this;

}

// COPY CONTRUCTOR
DPLKYL002::Image::Image(const DPLKYL002::Image& oImg) :
		width(oImg.width), height(oImg.height) {

	unsigned char* tmpArr = new unsigned char[oImg.width
			* oImg.height];

	for (int k = 0; k < height * width; k++) {

		tmpArr[k] = oImg.data[k];

	}

	data.reset(tmpArr);

}

// COPY ASSIGNMENT OPERATOR
DPLKYL002::Image& DPLKYL002::Image::operator=(const DPLKYL002::Image& oImg) {

	if (this == &oImg){

		return *this;

	}

	if (data != nullptr){

		data = nullptr;

	}

	width = oImg.width;

	height = oImg.height;

	unsigned char* tmpArr = new unsigned char[width * height];

	for (int k = 0; k < height * width; k++) {

		tmpArr[k] = oImg.data[k];

	}

	data.reset(tmpArr);

	return *this;

}

// OPERATORS

// ADD
//Add I1 I2 : add the pixel values of I1 to I2 (i.e. at every corresponding 2D position you add the two values)
DPLKYL002::Image DPLKYL002::Image::operator +(const DPLKYL002::Image& oImage) {

	Image img(*this);

	Image::Iterator imgPtr = img.begin(), imgEnd = img.end();

	Image::Iterator tempPtr = oImage.begin(), oEnd = oImage.end();

	while (imgPtr != imgEnd) {

		int total = (*imgPtr + *tempPtr);

		if (total > 255) {

			total = 255;

		}

		*imgPtr = total;

		++imgPtr;

		++tempPtr;

	}

	return img;

}

// SUBTRACT
// Subtract I1 I2 : subtract pixel values of I2 from I1
DPLKYL002::Image DPLKYL002::Image::operator -(const DPLKYL002::Image& oImage) {

	Image img(*this);

	Image::Iterator imgPtr = img.begin(), imgEnd = img.end();

	Image::Iterator tempPtr = oImage.begin(), oEnd = oImage.end();

	while (imgPtr != imgEnd) {

		int total = (*imgPtr - *tempPtr);

		if (total < 0) {

			total = 0;

		}

		*imgPtr = total;

		++imgPtr;

		++tempPtr;

	}

	return img;

}

// INVERT
// Invert I1 : replace each pixel value p with (255 - p)
DPLKYL002::Image DPLKYL002::Image::operator !() {

	Image img(*this);

	Image::Iterator imgPtr = img.begin(), imgEnd = img.end();

	while (imgPtr != imgEnd) {

		*imgPtr = 255 - *imgPtr;

		++imgPtr;

	}

	return img;

}

// MASK
// Mask I1 I2 : given I1 and an image I2, copy across values from I1 where I2 has a value of 255.
// All other output values are set to 0.
DPLKYL002::Image DPLKYL002::Image::operator /(const DPLKYL002::Image& oImage) {

	Image img(*this);

	Image::Iterator imgPtr = img.begin(), imgEnd = img.end();

	Image::Iterator tempPtr = oImage.begin(), oEnd = oImage.end();

	while (imgPtr != imgEnd) {

		bool temp = (*tempPtr == 255);

		if (!temp) {

			*imgPtr = 0;

		}

		++imgPtr;

		++tempPtr;

	}

	return img;

}

// THRESHOLD
// Threshold I1 f : for all pixels in I1 > f, set the result to the integer 255, otherwise set the value to 0.
DPLKYL002::Image DPLKYL002::Image::operator *(int value) {

	Image img(*this);

	Image::Iterator imgPtr = img.begin(), imgEnd = img.end();

	while (imgPtr != imgEnd) {

		bool temp = (*imgPtr > value);

		if (temp) {

			*imgPtr = 255;

		} else {

			*imgPtr = 0;

		}

		++imgPtr;

	}

	return img;

}

// INPUT
istream& DPLKYL002::operator >>(istream& iFile, DPLKYL002::Image& oImage) {

	string input;

	if (iFile) {

		iFile.seekg(0, iFile.end);

		streampos temp = iFile.tellg();

		iFile.seekg(0, iFile.beg);

		getline(iFile, input);

		do {

			getline(iFile, input);

		} while (input.substr(0, 1).compare("#") == 0);

		string h = input.substr(0, input.find(" "));

		string w = input.substr(input.find(" ") + 1);

		stringstream ssHeight(h);

		ssHeight >> oImage.height;

		stringstream ssWidth(w);

		ssWidth >> oImage.width;

		getline(iFile, input);

		streampos oTemp = 0;

		oTemp = iFile.tellg();

		temp = iFile.tellg() - oTemp;

		oImage.data.reset(new unsigned char[oImage.width * oImage.height]);

		skipws(iFile);

		iFile.read((char*) (&(oImage.data[0])), oImage.width * oImage.height);

	} else {

		cout << "Unable to open file. " << endl;

	}
}

// OUTPUT
ostream& DPLKYL002::operator <<(ostream& iFile, const DPLKYL002::Image& oImage) {

	if (iFile) {

		iFile << "P5" << endl;

		iFile << "# output image" << endl;

		iFile << oImage.height << " " << oImage.width << endl;

		iFile << "255" << endl;

		unsigned char temp;

		for (auto k = oImage.begin(); k != oImage.end(); ++k) {

			temp = *k;

			iFile.write((char*) &temp, 1);

		}

		return iFile;

	} else {

		cout << "Unable to open file. " << endl;

	}

}

// EQUIVALENCE
bool DPLKYL002::Image::operator ==(const DPLKYL002::Image& oImage) {

	if (sizeof(oImage.data.get()) != sizeof(data.get())){

		return false;

	}

	for (int k = 0; k < sizeof(data.get()); k++) {

		if (data[k] != oImage.data[k]){

			return false;

		}

	}

	return true;

}

// UTILITY FUNCTIONS

// LOAD
void DPLKYL002::Image::load(string imgName) {

	string input;

	ifstream iFile;

	iFile.open(imgName, ios::binary);

	if (iFile.is_open()) {

		iFile.seekg(0, iFile.end);

		streampos temp = iFile.tellg();

		iFile.seekg(0, iFile.beg);

		getline(iFile, input);

		do {

			getline(iFile, input);

		} while (input.substr(0, 1).compare("#") == 0);

		string h = input.substr(0, input.find(" "));

		string w = input.substr(input.find(" ") + 1);

		stringstream ssHeight(h);

		ssHeight >> height;

		stringstream ssWidth(w);

		ssWidth >> width;

		getline(iFile, input);

		streampos oTemp = 0;

		oTemp = iFile.tellg();

		temp = iFile.tellg() - oTemp;

		data.reset(new unsigned char[width * height]);

		iFile.read((char*) &data[0], width * height);

		iFile.close();

	} else {

		cout << "Unable to open " << imgName << endl;

	}
}

// SAVE
void DPLKYL002::Image::save(string imgName) {

	ofstream oFile(imgName, ios::binary);

	if (oFile) {


		oFile << "P5" << endl;

		oFile << "# output image" << endl;

		oFile << height << " " << width << endl;

		oFile << "255" << endl;


		unsigned char temp;

		for (auto k = this->begin(); k != end(); ++k) {

			temp = *k;

			oFile.write((char*) &temp, 1);

		}

		oFile.close();

	} else {

		cout << "Unable to open " << imgName << endl;

	}
}

// ITERATOR CLASS

// THE BIG 6

// CONSTRUCTOR
DPLKYL002::Image::Iterator::Iterator(unsigned char *oPtr) :
		ptr(oPtr) {
}

// DESTRUCTOR
DPLKYL002::Image::Iterator::~Iterator() {

	ptr = nullptr;

}

// MOVE CONSTRUCTOR
DPLKYL002::Image::Iterator::Iterator(Iterator&& oPtr) {

	ptr = oPtr.ptr;

	oPtr = nullptr;

}

// MOVE ASSIGNMENT OPERATOR
DPLKYL002::Image::Iterator& DPLKYL002::Image::Iterator::operator =(
		Iterator&& oPtr) {

	if (this != &oPtr) {

		ptr = oPtr.ptr;

	}

	oPtr = nullptr;

	return *this;

}

// COPY CONSTRUCTOR
DPLKYL002::Image::Iterator::Iterator(const Iterator& oPtr) :
		ptr(oPtr.ptr) {
}

// COPY ASSIGNMENT OPERATOR
DPLKYL002::Image::Iterator& DPLKYL002::Image::Iterator::operator =(
		const Iterator& oPtr) {

	if (this != &oPtr) {

		ptr = oPtr.ptr;

	}

	return *this;

}

// OPERATORS

DPLKYL002::Image::Iterator DPLKYL002::Image::begin(void) const {

	return Iterator(&(data.get()[0]));

}

DPLKYL002::Image::Iterator DPLKYL002::Image::end(void) const {

	return Iterator(&(data.get()[width * height]));

}

unsigned char& DPLKYL002::Image::Iterator::operator *() {

	return *ptr;

}

bool DPLKYL002::Image::Iterator::operator !=(const Iterator& oPtr) {

	return (ptr != oPtr.ptr);

}

DPLKYL002::Image::Iterator& DPLKYL002::Image::Iterator::operator +=(int oPtr) {

	ptr = ptr + oPtr;

	return *this;

}

const DPLKYL002::Image::Iterator& DPLKYL002::Image::Iterator::operator ++() {

	++ptr;

	return *this;

}

const DPLKYL002::Image::Iterator& DPLKYL002::Image::Iterator::operator --() {

	ptr--;

	return *this;

}
