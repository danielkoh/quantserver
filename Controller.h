#pragma once

#include <string>
#include <map>
#include <boost/shared_ptr.hpp>
#include "ControllerReturnType.h"

namespace quantserver
{
	typedef std::map<std::string , std::string> ModelMap ;
	typedef boost::shared_ptr<std::map<std::string , std::string>> ModelMapPtr ;

	class Controller
	{
	public:
		Controller(void);
		virtual ~Controller(void) ;
		virtual ControllerReturnType operator() (const std::string& path , ModelMap& modelMap) = 0 ;

	};
}

