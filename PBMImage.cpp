#include "PBMImage.h"
#include <iostream>

void PBMImage::clear()
{
	this->magicNumber = "";
	this->row = 0;
	this->col = 0;
	this->maxValue = 1;
	this->pixels.clear();
}

void PBMImage::readFile(std::ifstream& fileOpener, std::string fileName)
{
	this->fileName = fileName;
	fileOpener >> this->magicNumber;
	fileOpener >> this->row >> this->col;
	this->maxValue = 1;
	int temp = 0;
	for (int i = 0; i < row * col; i++)
	{
		fileOpener >> temp;
		pixels.push_back(temp);
	}
}

void PBMImage::printPixels()
{
	for (int i = 0; i < col * row; i++)
	{
		std::cout << pixels[i] << " " ;
		if (i != 0 && (i + 1) % col == 0)
		{
			std::cout << std::endl;
		}
	}
}

void PBMImage::saveAs(std::string)
{
	std::ofstream file(fileName);
	if (file.is_open()) {

		file << this->magicNumber << std::endl;
		file << this->row << std::endl;
		file << this->col << std::endl;

		for (int i = 0; i < row*col; i++)
		{
			file << pixels[i] << " ";
			if(i != 0 && i % (row - 1)  == 0)
				file << std::endl;
		}
		file.close();
	}
}

void PBMImage::grayscale()
{
	std::cout << "Could not convert P1 to grayscale." << std::endl;
}

void PBMImage::monochrome()
{
	std::cout << "Could not convert P1 to monochrome." << std::endl;
}

void PBMImage::negative()
{
		for (int i = 0; i < this->pixels.size(); i++)
		{
			int grayShade = this->maxValue - pixels[i];
			pixels[i] = grayShade;
		}
}

void PBMImage::rotate(int direction)
{
	int** arrayPixels = new int* [row];
	int** transpose = new int* [col];
	for (int i = 0; i < row; i++)
	{
		arrayPixels[i] = new int[col];
		for (int j = 0; j < col; j++)
		{
			arrayPixels[i][j] = pixels[i * col + j];
		}
	}
	for (int i = 0; i < col; i++)
	{
		transpose[i] = new int[row];
	}
	if (direction == 0) {
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				transpose[j][i] = arrayPixels[i][j];
			}
		}


		int tempCol = col;
		col = row;
		row = tempCol;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				std::cout << transpose[i][j] << " ";
			}std::cout << std::endl;
		}
		/*for (int i = 0; i < row; i++) {

			int start = 0;
			int end = col - 1;

			while (start < end) {
				int temp = transpose[i][start];
				transpose[i][start] = transpose[i][end];
				transpose[i][end] = temp;

				start++;
				end--;
			}
		}*/
		pixels.clear();
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				pixels.push_back(transpose[i][j]);
			}
		}

		for (int i = 0; i < col; i++)
		{
			delete[] arrayPixels[i];
		}
		delete[] arrayPixels;
		for (int i = 0; i < row; i++)
		{
			delete[] transpose[i];
		}
		delete[] transpose;
	}
	if (direction == 1) {

		for (int i = 0; i < col; i++)
		{
			transpose[i] = new int[row];
			int start = 0;
			int end = row - 1;

			while (start < end) {
				int temp = transpose[i][start];
				transpose[i][start] = transpose[i][end];
				transpose[i][end] = temp;

				start++;
				end--;
			}
		}


		for (int i = 0; i < col; i++)
		{
			for (int j = 0; j < row; j++)
			{
				transpose[i][j] = arrayPixels[j][i];
			}
		}

		for (int i = 0; i < row; i++)
		{
			delete[] arrayPixels[i];
		}
		delete[] arrayPixels;
		for (int i = 0; i < col; i++)
		{
			delete[] transpose[i];
		}
		delete[] transpose;
	}
}
