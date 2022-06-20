#pragma once
#include<string>
#include <vector>
#include <fstream>

#include "RGB.h"
class Image
{
protected:
	std::string fileName;
	std::string magicNumber;
	int row;
	int col;
	int maxValue;
public:
	void setMagicNumber(std::string magicNumber);
	std::string getMagicNumber();
	void setMaxValue(int maxValue);
	int getMaxValue();
	int getRow();
	void setRow(int row);
	int getCol();
	void setCol(int col);
	std::string getFileName();
	void setFileName(std::string fileName);

	virtual void clear() = 0;
	
	virtual void readFile(std::ifstream&, std::string) = 0;
	virtual void printPixels() = 0;
	virtual void saveAs(std::string) = 0;

	/*! Convert all color images in the current session to those using shades of gray.
If black and white images are included in the current session, they should not be modified.*/
	virtual void grayscale() = 0;
	/*! Convert all color images in the current session to ones that have only black and white pixels,
without any shades of gray. If the image is already monochrome, this transformation does not change it.*/
	virtual void monochrome() = 0;
	/*! A the negative transformation(color inversion) of the images in the current session.*/
	virtual void negative() = 0;
	/*! This command applies a 90 degree rotation in the appropriate direction.0 - left 1 - right*/
	virtual void rotate(int direction) = 0;
};

