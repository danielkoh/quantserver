#pragma once

#include "DefaultController.h"

namespace quantserver
{
	typedef boost::shared_ptr<Controller> ControllerPtr ;
	typedef std::map<std::string , ControllerPtr> ControllerMap ;
	class Dispatcher
	{
	public:
		Dispatcher(void);
		~Dispatcher(void);

		ControllerReturnType dispatch(const std::string& path , ModelMap& modelMap) ;

	protected:
		void registerControllers() ;
		ControllerMap controllerMap ;


		DefaultController defaultController ;
	};
}

