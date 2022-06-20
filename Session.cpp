#include "Session.h"
#include "Image.h"
#include "PPMImage.h"
#include "PGMImage.h"
#include "PBMImage.h"
#include <fstream>
#include <iostream>

Session::Session(int sessionID)
{
    this->sessionID = sessionID;
}

int Session::getSessionID()
{
    return this->sessionID;
}

void Session::addLog(std::string message)
{
    this->log.push_back(message);
}

void Session::add(std::string image)
{
    if (image.find(".ppm") != -1)
    {
        PPMImage* toAdd = new PPMImage();
        std::ifstream fileInput(image);
        if (fileInput.is_open())
        {
            std::cout << "Successfully opened" << std::endl;
            toAdd->readFile(fileInput, image);
            fileInput.close();
            images.push_back(toAdd);
        }
        else
        {
            std::cout << "File could not open." << std::endl;
            return;
        }
    }
    else if (image.find(".pbm") != -1)
    {
        PBMImage* toAdd = new PBMImage();
        std::ifstream fileInput(image);
        if (fileInput.is_open())
        {
            std::cout << "Successfully opened" << std::endl;
            toAdd->readFile(fileInput, image);
            fileInput.close();
            images.push_back(toAdd);
        }
         else
         {
             std::cout << "File could not open." << std::endl;
             return;
         }
    }
    else if (image.find(".pgm") != -1)
    {
        PGMImage* toAdd = new PGMImage();
        std::ifstream fileInput(image);
        if (fileInput.is_open())
        {
            std::cout << "Successfully opened" << std::endl;
            toAdd->readFile(fileInput, image);
            fileInput.close();
            images.push_back(toAdd);
        }
        else
        {
            std::cout << "File could not open." << std::endl;
            return;
        }
    }
}
