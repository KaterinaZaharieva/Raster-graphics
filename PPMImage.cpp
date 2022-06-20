#include "PPMImage.h"
#include <iostream>

void PPMImage::clear()
{
	this->magicNumber = "";
	this->row = 0;
	this->col = 0;
	this->maxValue = 1;
	this->pixels.clear();
}
void PPMImage::readFile(std::ifstream& file, std::string fileName)
{
	this->fileName = fileName;
	char buf[4];
	file.getline(buf, 4);
	buf[3] = '\0';
	this->magicNumber = buf;
	file >> row;
	file >> col;
	file >> maxValue;
	RGB pixel;
	for (int i = 0; i < col * row; i++)
	{
		file >> pixel.red;
		file >> pixel.green;
		file >> pixel.blue;
		pixels.push_back(pixel);
	}
}

void PPMImage::printPixels()
{
	for (int i = 0; i < col * row; i++)
	{
		std::cout << pixels[i].red << " " << pixels[i].green << " " << pixels[i].blue << "  ";
		if (i != 0 && (i + 1) % col == 0)
		{
			std::cout << std::endl;
		}
	}
}

void PPMImage::saveAs(std::string fileName)
{
	std::ofstream file(fileName);
	if (file.is_open()){

		file << this->magicNumber << std::endl;
		file << this->row << std::endl;
		file << this->col << std::endl;
		file << this->maxValue << std::endl;
		for (int i = 0; i < col * row; i++)
		{
			file << pixels[i].red<< " " << pixels[i].green << " " << pixels[i].blue << std::endl;
		}

		file.close();
	}
}

void PPMImage::grayscale()
{
	if (this->magicNumber.compare("P3") == 0)
	{
		for (int i = 0; i < this->pixels.size(); i++)
		{
			int grayShade = (pixels[i].red + pixels[i].green + pixels[i].blue) / 3;
			pixels[i].red = grayShade;
			pixels[i].green = grayShade;
			pixels[i].blue = grayShade;
		}
	}
	else
	{
		std::cout << "The image is in P1 format(black and white) and can not be converted!" << std::endl;
	}
}

void PPMImage::monochrome()
{
		for (int i = 0; i < this->pixels.size(); i++)
		{
			int grayShade = (pixels[i].red + pixels[i].green + pixels[i].blue) / 3;
			if (grayShade > this->maxValue / 2)
			{
				grayShade = this->maxValue;
			}
			else
			{
				grayShade = 0;
			}
			pixels[i].red = grayShade;
			pixels[i].green = grayShade;
			pixels[i].blue = grayShade;
		}
}

void PPMImage::negative()
{
	if (this->magicNumber.compare("P3") == 0)
	{
		for (int i = 0; i < this->pixels.size(); i++)
		{
			int grayShade = this->maxValue - ((pixels[i].red + pixels[i].green + pixels[i].blue) / 3);
			pixels[i].red = grayShade;
			pixels[i].green = grayShade;
			pixels[i].blue = grayShade;
		}
	}

}

void PPMImage::rotate(int direction)
{
}
