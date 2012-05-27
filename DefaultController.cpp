#include "DefaultController.h"
#include <iostream>
#include <fstream>
#include <sstream>



using namespace quantserver ;

#define FILEBASEPATH "C:\\workspaces\\cppFinance\\www\\"

std::string convertToFilePath(const std::string& path) ;

DefaultController::DefaultController(void)
{
}


DefaultController::~DefaultController(void)
{
}

//Grabs and return the contents of a file
ControllerReturnType DefaultController::operator() (const std::string& path , ModelMap& modelMap)
{
	std::string fpath = convertToFilePath(path) ;

	std::ifstream fileToRead(fpath) ;

	if(fileToRead.good())
	{
		std::stringstream payload ;
		//fileToRead.
		payload << fileToRead.rdbuf() ;

		return ControllerReturnType(STATUS_OK , payload.str() ) ;
	}
	else
	{
		return ControllerReturnType(STATUS_NOT_FOUND , "File Not Found") ;
	}
}

std::string convertToFilePath(const std::string& path)
{
	int lastOfPath = path.find_last_of("/") ;
	std::string filename = path.substr(lastOfPath) ;
	std::string toRt = FILEBASEPATH ;
	return toRt.append(filename) ;
}
