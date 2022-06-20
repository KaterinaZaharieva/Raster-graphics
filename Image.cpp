#include "Image.h"
#include <fstream>
#include <iostream>

void Image::setMagicNumber(std::string magicNumber)
{
	if (magicNumber.compare("P1") || magicNumber.compare("P2") || magicNumber.compare("P3"))
	{
		this->magicNumber = magicNumber;
	}
}

std::string Image::getMagicNumber()
{
	return this->magicNumber;
}

void Image::setMaxValue(int maxValue)
{
	if (maxValue >= 0 && maxValue <= 255)
	{
		this->maxValue = maxValue;
	}
}

int Image::getMaxValue()
{
	return this->maxValue;
}

int Image::getRow()
{
	return this->row;
}

void Image::setRow(int row)
{
	this->row = row;
}

int Image::getCol()
{
	return this->col;
}

void Image::setCol(int col)
{
	this->col = col;
}

std::string Image::getFileName()
{
	return this->fileName;
}

void Image::setFileName(std::string fileName)
{
	this->fileName = fileName;
}
