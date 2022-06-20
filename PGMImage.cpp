#include "PGMImage.h"
#include <iostream>

void PGMImage::clear()
{
	this->magicNumber = "";
	this->row = 0;
	this->col = 0;
	this->maxValue = 1;
	this->pixels.clear();
}

void PGMImage::readFile(std::ifstream& fileOpener, std::string fileName)
{
	this->fileName = fileName;
	fileOpener >> this->magicNumber;
	fileOpener >> this->row >> this->col;
	fileOpener >> this->maxValue;
	int temp = 0;
	for(int i = 0; i < row*col; i++)
	{
		fileOpener >> temp;
		pixels.push_back(temp);
	}
}

void PGMImage::printPixels()
{
	for (int i = 0; i < col * row; i++)
	{
		std::cout << pixels[i] << " ";
		if (i != 0 && (i + 1) % col == 0)
		{
			std::cout << std::endl;
		}
	}
}

void PGMImage::saveAs(std::string)
{
	std::ofstream file(fileName);
	if (file.is_open()) {

		file << this->magicNumber << std::endl;
		file << this->row << std::endl;
		file << this->col << std::endl;
		file << this->maxValue << std::endl;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				file << pixels[i * row + j] << " ";
			}
			file << std::endl;
		}

		file.close();
	}
}

void PGMImage::grayscale()
{
	std::cout << "Could not convert P2 to grayscale." << std::endl;
}

void PGMImage::monochrome()
{
	for (int i = 0; i < this->pixels.size(); i++)
	{
		if (pixels[i] > this->maxValue / 2)
		{
			pixels[i] = this->maxValue;
		}
		else
		{
			pixels[i] = 0;
		}
	}
}

void PGMImage::negative()
{
		for (int i = 0; i < this->pixels.size(); i++)
		{
			int grayShade = this->maxValue - pixels[i];
			pixels[i] = grayShade;
		}
}

void PGMImage::rotate(int direction)
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

	if (direction == 0) {
		for (int i = 0; i < col; i++)
		{
			transpose[i] = new int[row];
			for (int j = 0; j < row; j++)
			{
				transpose[i][j] = arrayPixels[j][i];
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
		for (int i = 0; i < row; i++) {

			int start = 0;
			int end = col - 1;

			while (start < end) {
				int temp = transpose[i][start];
				transpose[i][start] = transpose[i][end];
				transpose[i][end] = temp;

				start++;
				end--;
			}
		}
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


		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				transpose[j][i] = arrayPixels[i][j];
			}
		}
		pixels.clear();
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				pixels.push_back(transpose[i][j]);
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
