#pragma once

#include <chaiscript/chaiscript.hpp>
#include <boost/shared_ptr.hpp>

namespace quantserver
{
	typedef boost::shared_ptr<chaiscript::ChaiScript> ScriptEnginePtr;

	class ScriptManager
	{
	public:
		ScriptManager(void);
		~ScriptManager(void);

		chaiscript::ChaiScript& engine();
	protected:
		ScriptEnginePtr scriptEnginePtr; 
		
	};

	typedef boost::shared_ptr<ScriptManager> ScriptManagerPtr ;
}

