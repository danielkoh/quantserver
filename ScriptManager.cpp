#include "ScriptManager.h"
//#include "Stock.h"

using namespace quantserver;


ScriptManager::ScriptManager(void)
{
	scriptEnginePtr = ScriptEnginePtr(new chaiscript::ChaiScript());
}


ScriptManager::~ScriptManager(void)
{
}


chaiscript::ChaiScript& ScriptManager::engine()
{
	return *scriptEnginePtr;
}
