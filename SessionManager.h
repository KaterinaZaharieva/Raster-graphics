#pragma once
#include <vector>
#include "Session.h"
class SessionManager
{
private:
	int currentSessionID;
	std::vector <Session> sessions;
public:
	void menu();

	SessionManager();
	/*! modifies every image in the session*/
	void modify(int commandIndex);

	/*! Switches to a session with an ID number. If a session with such a number does not exist, display an
appropriate error message*/
	void switchSession(int sessionID);
	/*! Undo command that removes the last transformation in the current session.
If a new session is started and then the undo command is entered immediately, it should have no effect.*/
	void undo();
	/*! Enables the user to receive detailed information about the current user session, its identification number,
	the participating images, as well as the set of transformations that are to be applied to the respective images
	participating in the session.*/
	void sessionInfo();
	/*! Creates a collage of two images (in the same format and the same dimension) available in the current session.
	The result is saved in a new image, which is added to the current session. horizontal - 0  vertical - 1 */
	void collage(int direction, int image1ID, int image2ID, std::string outimage);
};

