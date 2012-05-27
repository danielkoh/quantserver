#pragma once
#include "Controller.h"
#include "ScriptEnvironment.h"

namespace quantserver
{
	class QuantEvalController : public Controller
	{
	public:
		QuantEvalController(void);
		~QuantEvalController(void);
		virtual ControllerReturnType operator() (const std::string& path , ModelMap& modelMap);

	protected:
		ScriptEnvironment env ;
	};
}

