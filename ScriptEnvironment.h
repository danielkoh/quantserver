#pragma once

#include "ScriptManager.h"
#include "FunctionRegistrator.h"
#include "Stock.h"

namespace quantserver
{
	//To be used as a functor to initialize ScriptManager
	class ScriptEnvironment
	{
	public:
		ScriptEnvironment(void);
		virtual ~ScriptEnvironment(void);

		ScriptManager& operator() (ScriptManager& scriptManager) ;
		ScriptManager& ScriptEnvironment::operator() ();

		static ScriptEnvironment initialized() ;

	protected:
		FunctionRegistratorPtr functionRegister ;
		ScriptManagerPtr scriptManager ;
	};
}

