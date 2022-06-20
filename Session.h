#pragma once
#include <vector>
#include <string>
#include "Image.h"
class Session
{
private:
	int sessionID;
	std::vector <std::string> log;
	std::vector <std::string> commands;
	std::vector<Image*> images;
public:
	friend class SessionManager;
	Session(int sessionID);
	int getSessionID();

	void addLog(std::string message);
	/*! Adds the image to the current session. Not all transformations applied so far are applied to it*/
	void add(std::string image);
};

