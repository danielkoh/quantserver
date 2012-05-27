#include "Dispatcher.h"
#include "QuantEvalController.h"

using namespace quantserver ;

Dispatcher::Dispatcher(void)
{
	controllerMap = ControllerMap() ;
	registerControllers() ;

}


Dispatcher::~Dispatcher(void)
{
}

void Dispatcher::registerControllers()
{
	Controller* controllerp = new QuantEvalController() ;
	controllerMap["/eval"] = ControllerPtr(controllerp) ;

	defaultController = DefaultController();
}

ControllerReturnType Dispatcher::dispatch(const std::string& path , ModelMap& modelMap)
{
	if(controllerMap.count(path) > 0 )
	{
		ControllerPtr controllerPtr = controllerMap[path] ;
		Controller& controller = *controllerPtr ;
		return controller(path , modelMap) ;
	}

	return defaultController(path , modelMap) ;
}