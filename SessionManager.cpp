#include "SessionManager.h"
#include <iostream>
#include <algorithm>
void SessionManager::menu()
{
	std::string command;
	std::vector<std::string> arguments;
	while (command != "exit")
	{
		std::cout << ">";
		command.clear();
		std::getline(std::cin, command);
		int counter = 0;
		arguments.clear();
		for (int i = 0; i < command.size() + 1; i++)
		{
			if (command[i] == ' ' || command[i] == '\0')
			{
				arguments.push_back(command.substr(i - counter, counter));
				counter = 0;
			}
			else {
				counter++;
			}
		}
		std::for_each(command.begin(), command.end(), [](char& c)
			{
				c = ::tolower(c);
			});
		
		if (command.find("load") != -1)
		{

			currentSessionID = sessions.size() + 1;
			Session session(currentSessionID);
			std::cout << "Session with ID: " << currentSessionID << " started" << std::endl;
			sessions.push_back(session);
			for (int i = 1; i < arguments.size(); i++)
			{
				std::string fileName = arguments[i];
				sessions[currentSessionID - 1].add(fileName);
			}
			sessions[currentSessionID - 1].commands.push_back(command);
		}
		else if (command.find("add") != -1)
		{
			std::string fileName = arguments[1];
			if (currentSessionID == 0)
			{
				std::cout << "You cannot add images without loading 1 or more images, there is not started session." << std::endl;
				return;
			}
			else 
			{
				for (int i = 1; i < arguments.size(); i++)
				{
					sessions[currentSessionID - 1].add(fileName);
				}
				std::string message("Image ");
				message += fileName;
				message += " added.";
				std::cout << message << std::endl;
			}
		}
		else if (command.find("grayscale") != -1)
		{
			sessions[currentSessionID - 1].addLog("grayscale");
			sessions[currentSessionID - 1].commands.push_back(command);
		}
		else if (command.find("monochrome") != -1)
		{
			sessions[currentSessionID - 1].addLog("monochrome");
			sessions[currentSessionID - 1].commands.push_back(command);
		}
		else if (command.find("negative") != -1)
		{
			sessions[currentSessionID - 1].addLog("negative");
			sessions[currentSessionID - 1].commands.push_back(command);
		}
		else if (command.find("rotate") != -1)
		{
			sessions[currentSessionID - 1].addLog("rotate");
			sessions[currentSessionID - 1].commands.push_back(command);
		}
		else if (command.find("undo") != -1)
		{
			undo();
		}
		else if (command.find("session info") != -1)
		{
			std::cout << "Name of images in the session: ";
			for (int i = 0; i < sessions[currentSessionID - 1].images.size(); i++)
			{
				std::cout << sessions[currentSessionID - 1].images[i]->getFileName() << " ";
			} 
			std::cout << std::endl;
			std::cout << "Pending transformations: ";
			for (int i = 0; i < sessions[currentSessionID - 1].log.size(); i++)
			{
				std::cout << sessions[currentSessionID - 1].log[i] << " ";
			}
			std::cout << std::endl;
		}
		else if (command.find("switch") != -1)
		{
			switchSession(atoi(arguments[1].c_str()));
		}
		else if (command.find("collage") != -1)
		{
			int direction = 0;
			int image1ID, image2ID;
			for (int i = 0; i < sessions[currentSessionID - 1].images.size(); i++)
			{
				if (sessions[currentSessionID - 1].images[i]->getFileName() == arguments[1])
				{
					image1ID = i;
				}
				if (sessions[currentSessionID - 1].images[i]->getFileName() == arguments[2])
				{
					image2ID = i;
				}
			}
			if (command.find("horizontal") != -1)
			{
				direction = 0;
					collage(direction, image1ID, image2ID, arguments[3]);
			}
			if (command.find("vertical") != -1)
			{
				direction = 1;
				collage(direction, image1ID, image2ID, arguments[3]);
			}
		}
		else if (command.find("help") != -1)
		{
			std::cout << "open <file>" << "      " << "opens <file>" << std::endl;
			std::cout << "close" << "       " << "closes currently opened file" << std::endl;
			std::cout << "save" <<"       " << "saves the currently open file" << std::endl;
			std::cout << "saveas <file>" << "     "<< "saves the currently open file in <file>" << std::endl;
			std::cout << "help" << "      " << "prints this information" << std::endl;
			std::cout << "exit" << "      " << "exists the program" << std::endl;
			std::cout << "grayscale" << "      " << "Convert all color images in the current session to those using shades of gray.If black and white images are included in the current session, they should not be modified" << std::endl;
			std::cout << "monochrome" << "      " << " Convert all color images in the current session to ones that have only black and white pixels,without any shades of gray.If the image is already monochrome, this transformation does not change it." << std::endl;
			std::cout << "negative" << "      " << "A the negative transformation(color inversion) of the images in the current session." << std::endl;
			std::cout << "rotate <direction>" << "      " << "This command applies a 90 degree rotation in the appropriate direction." << std::endl;
			std::cout << "undo" << "      " << "Undo command that removes the last transformation in the current session.If a new session is started and then the undo command is entered immediately, it should have no effect." << std::endl;
			std::cout << "add <image>" << "      " << "Adds the image to the current session. Not all transformations applied so far are applied to it" << std::endl;
			std::cout << "session info" << "      " << "Enables the user to receive detailed information about the current user session, its identification number,the participating images, as well as the set of transformations that are to be applied to the respective images participating in the session." << std::endl;
			std::cout << "switch <session> " << "      " << "Switches to a session with an ID number. If a session with such a number does not exist, display an appropriate error message" << std::endl;
			std::cout << "collage <direction> <image1> <image2><outimage>" << "      " << "Creates a collage of two images (in the same format and the same dimension) available in the current session.The result is saved in a new image, which is added to the current session." << std::endl;
		}
		else if (command.find("save") != -1)
		{
			for (int i = 0; i < sessions[currentSessionID - 1].images.size(); i++)
			{
				for (int j = 0; j < sessions[currentSessionID - 1].commands.size(); j++)
				{
					modify(j);
				}
			}
			for (int i = 0; i < sessions[currentSessionID - 1].images.size(); i++)
			{
				sessions[currentSessionID - 1].images[i]->saveAs(sessions[currentSessionID - 1].images[i]->getFileName());
			}
		}
		else if (command.find("saveas") != -1)
		{
			for (int j = 0; j < sessions[currentSessionID - 1].commands.size(); j++)
			{
				if (sessions[currentSessionID - 1].commands[j].find("grayscale") != -1)
				{
						sessions[currentSessionID - 1].images[0]->grayscale();
				}
				else 	if (sessions[currentSessionID - 1].commands[j].find("monochrome") != -1)
				{
						sessions[currentSessionID - 1].images[0]->monochrome();
				}
				else  if (sessions[currentSessionID - 1].commands[j].find("negative") != -1)
				{

						sessions[currentSessionID - 1].images[0]->negative();
					
				}
				else if (sessions[currentSessionID - 1].commands[j].find("rotate") != -1)
				{
					int direction = 0;
					if (sessions[currentSessionID - 1].commands[j].find("left") != -1)
					{
						direction = 0;
					}
					else if (sessions[currentSessionID - 1].commands[j].find("right") != -1)
					{
						direction = 1;
					}
						sessions[currentSessionID - 1].images[0]->rotate(direction);
				}
			}
			sessions[currentSessionID - 1].images[0]->saveAs(sessions[currentSessionID - 1].images[0]->getFileName());
			///sessions[currentSessionID - 1].images[0]->setFileName(arguments[1]);
		}
		else if (command.find("exit") != -1)
		{
			return;
		}
		else
		{
			std::cout << "There is no such command! Type help to see all the commands" << std::endl;
		}
		
	}
}

SessionManager::SessionManager()
{
	this->currentSessionID = 0;
}

void SessionManager::modify(int commandIndex)
{
	if (sessions[currentSessionID - 1].commands[commandIndex].find("grayscale") != -1)
	{
		for (int i = 0; i < sessions[currentSessionID - 1].images.size(); i++)
		{
			sessions[currentSessionID - 1].images[i]->grayscale();
		}
	}
	else if (sessions[currentSessionID - 1].commands[commandIndex].find("monochrome") != -1)
	{
		for (int i = 0; i < sessions[currentSessionID - 1].images.size(); i++)
		{
			sessions[currentSessionID - 1].images[i]->monochrome();
		}
	}
	else  if (sessions[currentSessionID - 1].commands[commandIndex].find("negative") != -1)
	{
		for (int i = 0; i < sessions[currentSessionID - 1].images.size(); i++)
		{
			sessions[currentSessionID - 1].images[i]->negative();
		}
	}
	else if (sessions[currentSessionID - 1].commands[commandIndex].find("rotate") != -1)
	{
		int direction = 0;
		if (sessions[currentSessionID - 1].commands[commandIndex].find("left") != -1)
		{
			direction = 0;
		}
		else if (sessions[currentSessionID - 1].commands[commandIndex].find("right") != -1)
		{
			direction = 1;
		}
		for (int i = 0; i < sessions[currentSessionID - 1].images.size(); i++)
		{
			sessions[currentSessionID - 1].images[i]->rotate(direction);

		}
	}
}

void SessionManager::switchSession(int sessionID)
{
	for (int i = 0; i < sessions.size(); i++)
	{
		if (sessions[i].getSessionID() == sessionID)
		{
			currentSessionID = i;
			return;
		}
	}
	std::cout << "There is not a session with this id" << std::endl;
}

void SessionManager::undo()
{
	sessions[currentSessionID - 1].commands.pop_back();
}

void SessionManager::collage(int direction, int image1ID, int image2ID, std::string outimage)
{
	if (sessions[currentSessionID - 1].images[image1ID]->getFileName().find(".ppm") != -1 && sessions[currentSessionID - 1].images[image2ID]->getFileName().find(".ppm") != -1 && outimage.find(".ppm") != -1)
	{
		if (direction == 0)
		{
			std::ofstream file(outimage);
			file << sessions[currentSessionID - 1].images[image1ID]->getMagicNumber() << std::endl;
			file << sessions[currentSessionID - 1].images[image1ID]->getRow() << " " << sessions[currentSessionID - 1].images[image1ID]->getCol() << std::endl;
			file << sessions[currentSessionID - 1].images[image1ID]->getMaxValue() << std::endl;
			file.close();
		}
		if (direction == 1)
		{
			std::ofstream file(outimage);
			file << sessions[currentSessionID - 1].images[image1ID]->getMagicNumber() << std::endl;
			file << sessions[currentSessionID - 1].images[image1ID]->getRow() << " " << sessions[currentSessionID - 1].images[image1ID]->getCol() << std::endl;
			file << sessions[currentSessionID - 1].images[image1ID]->getMaxValue() << std::endl;
			file.close();
		}
	}
	else if (sessions[currentSessionID - 1].images[image1ID]->getFileName().find(".pbm") != -1 && sessions[currentSessionID - 1].images[image2ID]->getFileName().find(".pbm") != -1 && outimage.find(".pbm") != -1)
	{
		if (direction == 0)
		{
			std::ofstream file(outimage);
			file << sessions[currentSessionID - 1].images[image1ID]->getMagicNumber() << std::endl;
			file << sessions[currentSessionID - 1].images[image1ID]->getRow() << " " << sessions[currentSessionID - 1].images[image1ID]->getCol() << std::endl;
		}
		if (direction == 0)
		{
			std::ofstream file(outimage);
			file << sessions[currentSessionID - 1].images[image1ID]->getMagicNumber() << std::endl;
			file << sessions[currentSessionID - 1].images[image1ID]->getRow() << " " << sessions[currentSessionID - 1].images[image1ID]->getCol() << std::endl;
		}
	}
	else if (sessions[currentSessionID - 1].images[image1ID]->getFileName().find(".pgm") != -1 && sessions[currentSessionID - 1].images[image2ID]->getFileName().find(".pgm") != -1 && outimage.find(".pgm") != -1)
	{
		if (direction == 0)
		{
			std::ofstream file(outimage);
			file << sessions[currentSessionID - 1].images[image1ID]->getMagicNumber() << std::endl;
			file << sessions[currentSessionID - 1].images[image1ID]->getRow() << " " << sessions[currentSessionID - 1].images[image1ID]->getCol() << std::endl;
			file << sessions[currentSessionID - 1].images[image1ID]->getMaxValue() << std::endl;

		}
		if (direction == 1)
		{
			std::ofstream file(outimage);
			file << sessions[currentSessionID - 1].images[image1ID]->getMagicNumber() << std::endl;
			file << sessions[currentSessionID - 1].images[image1ID]->getRow() << " " << sessions[currentSessionID - 1].images[image1ID]->getCol() << std::endl;
			file << sessions[currentSessionID - 1].images[image1ID]->getMaxValue() << std::endl;
		}
	}
	else
	{
		std::cout << "Cannot make a collage from different types!" << std::endl;
	}
}

