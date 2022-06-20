#pragma once
#include "Image.h"
#include <vector> 
class PGMImage : public Image
{
protected:
	std::vector <int> pixels;
public:
	void clear() override;
	void readFile(std::ifstream&, std::string)  override;
	void printPixels() override;
	void saveAs(std::string) override;


	void grayscale() override;
	void monochrome() override;
	void negative() override;
	void rotate(int direction) override;

};

