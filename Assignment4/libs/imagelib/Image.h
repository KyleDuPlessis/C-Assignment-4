//=====================================================================================
// Name        : Image.h
// Author      : Kyle du Plessis [DPLKYL002]
// Date:       : 16/04/2019
// Description : An image processing tool to manipulate 2D arrays of numbers (images)
// 				 using various operations - written in C++, Ansi-style
//=====================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#ifndef LIBS_IMAGE_H
#define LIBS_IMAGE_H

using namespace std;

namespace DPLKYL002 {

// Image class - wraps image operations and data.
// The image data is a block of width x height unsigned char values.

class Image {

private:

	int width, height;
	std::unique_ptr<unsigned char[]> data;

public:

	// THE BIG 6

	// CONSTRUCTORS
	Image(int w, int h, unsigned char* d);
	Image(std::string imgName);

	// DESTRUCTOR
	~Image();

	// MOVE CONTRUCTOR
	Image(Image&& oImg);

	// MOVE ASSIGNMENT OPERATOR
	Image& operator=(Image&& oImg);

	// COPY CONTRUCTOR
	Image(const Image& oImg);

	// COPY ASSIGNMENT OPERATOR
	Image& operator=(const Image& oImg);

	// OPERATORS

	// ADD
	Image operator +(const Image& oImage);

	// SUBTRACT
	Image operator -(const Image& oImage);

	// INVERT
	Image operator !();

	// MASK
	Image operator /(const Image& oImage);

	// THRESHOLD
	Image operator *(int value);

	// INPUT
	friend istream& operator >>(istream& iFile, Image& oImage);

	// OUTPUT
	friend ostream& operator <<(ostream& iFile, const Image& oImage);

	// EQUIVALENCE
	bool operator ==(const Image& oImage);

	// UTILITY FUNCTIONS

	// LOAD
	void load(string imgName);

	// SAVE
	void save(string imgName);

	/*Image container: you must create an iterator for your Image class. This
	 iterator should be used to gain access to the underlying image data and will
	 support the * and ++/-- operators. Appropriate begin() and end() methods must
	 be written for Image to return a reference to an iterator to which these
	 operators can be applied. We have provided a code skeleton showing some
	 features of this “nested class” – you must fill in the remaining functionality. Note
	 that it requires the use of friend to work correctly. Your algorithms for image
	 operations should be expressed in terms of these iterators.*/

	// ITERATOR CLASS
	class Iterator {

	private:

		unsigned char *ptr;
		friend class Image;

		// THE BIG 6

		// CONSTRUCTOR
		Iterator(u_char *oPtr);

	public:

		// DESTRUCTOR
		~Iterator();

		// MOVE CONSTRUCTOR
		Iterator(Iterator&& oPtr);

		// MOVE ASSIGNMENT OPERATOR
		Iterator& operator =(Iterator&& oPtr);

		// COPY CONSTRUCTOR
		Iterator(const Iterator& oPtr);

		// COPY ASSIGNMENT OPERATOR
		Iterator& operator =(const Iterator& oPtr);

		// OPERATORS

		unsigned char& operator *();

		bool operator !=(const Iterator& oPtr);

		Iterator& operator +=(int oPtr);

		const Iterator& operator ++();

		const Iterator& operator --();

	};

	// BEGIN (the first element)
	Image::Iterator begin(void) const;

	// END (one past the last element)
	Image::Iterator end(void) const;

	// accessor methods
	int getWidth() {

		return width;

	}

	int getHeight() {

		return height;

	}

	unsigned char * getData() {

		return data.get();

	}

};

}

#endif
