#include "QuantEvalController.h"
#include <boost/lexical_cast.hpp>
#include <iostream>

using namespace quantserver ;

QuantEvalController::QuantEvalController(void)
{
	env = ScriptEnvironment();
}


QuantEvalController::~QuantEvalController(void)
{
}

ControllerReturnType QuantEvalController::operator() (const std::string& path , ModelMap& modelMap)
{
	try
	{
		const std::string& str = modelMap["chai"] ;
		ScriptManager& script = env() ;

		std::cout << "Gonna run (" << str << ")" << std::endl ;

		double contents = script.engine().eval<double>(str) ;

		std::cout << "Chai says: " << contents << std::endl ;

		std::string c = boost::lexical_cast<std::string>(contents) ;
		return ControllerReturnType(STATUS_OK , c ) ;
	}
	catch(std::exception e)
	{
		return ControllerReturnType(STATUS_ERROR , e.what()) ;
	}
}
