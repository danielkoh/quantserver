#pragma once

#include "Controller.h"

namespace quantserver
{
	class DefaultController : Controller
	{
	public:
		DefaultController(void);
		~DefaultController(void);

		virtual ControllerReturnType operator() (const std::string& path , ModelMap& modelMap);


	};
}

