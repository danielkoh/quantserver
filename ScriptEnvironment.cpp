#include "ScriptEnvironment.h"

#include "EquityLoader.h"

using namespace quantserver ;

ScriptEnvironment::ScriptEnvironment(void)
{
	functionRegister = FunctionRegistratorPtr(new FunctionRegistrator()) ;
	scriptManager =  ScriptManagerPtr(new ScriptManager()) ;
	(*this)(*scriptManager) ;
}


ScriptEnvironment::~ScriptEnvironment(void)
{
}

ScriptEnvironment ScriptEnvironment::initialized()
{
	ScriptEnvironment env ;
	return env ;
}

ScriptManager& ScriptEnvironment::operator() ()
{
	return *scriptManager;
}

ScriptManager& ScriptEnvironment::operator() (ScriptManager& scriptManager)
{
	//Add in the modules
	scriptManager = PriceAtDate::chai(scriptManager) ;
	scriptManager = TimeSeries::chai(scriptManager) ;
	scriptManager = StockMetadata::chai(scriptManager) ;
	scriptManager = Stock::chai(scriptManager) ;
	scriptManager = EquityLoader::chai(scriptManager) ;
	
	//Add in the functions
	scriptManager = functionRegister->registerAll(scriptManager) ;

	//Add in some global vars
	EquityLoader loader ;
	scriptManager.engine().add(chaiscript::var(loader) , "equity" );

	return scriptManager ;

}