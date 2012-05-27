#include "FunctionRegistrator.h"
#include "value.h"
#include "accumulate.h"
#include "maxval.h"
#include "minval.h"
#include "mean.h"
#include "stdev.h"
#include "variance.h"
#include "mvg.h"

using namespace quantserver;

FunctionRegistrator::FunctionRegistrator(void)
{
	value_functions = std::map<std::string, ptr_val_func>();
	stov_functions = std::map<std::string, ptr_stov_func>()  ;
	stos_functions = std::map<std::string, ptr_stos_func>()  ;


	addAllValueFunctions() ;
	addAllStoVFunctions() ;
	addAllStoSFunctions() ;

}


FunctionRegistrator::~FunctionRegistrator(void)
{
	value_functions.clear();
	stov_functions.clear();
	stos_functions.clear();
}


ScriptManager& FunctionRegistrator::registerAll(ScriptManager& scriptManager)
{
	//Register the value functions
	for(std::map<std::string, ptr_val_func>::iterator it = value_functions.begin(); it != value_functions.end(); ++it) {
		
		scriptManager.engine().add(chaiscript::fun(it->second->f()) , it->first) ;
	}

	//Register the series to value functions
	for(std::map<std::string, ptr_stov_func>::iterator it = stov_functions.begin(); it != stov_functions.end(); ++it) {
		
		scriptManager.engine().add(chaiscript::fun(it->second->f()) , it->first) ;
	}

	//Register the series to series functions
	for(std::map<std::string, ptr_stos_func>::iterator it = stos_functions.begin(); it != stos_functions.end(); ++it) {
		
		scriptManager.engine().add(chaiscript::fun(it->second->f()) , it->first) ;
	}
	
	return scriptManager ;

}


void FunctionRegistrator::addAllValueFunctions()
{
	value_functions.clear();

	ptr_val_func value_function(new value());
	value_functions[std::string("value")] = value_function ;

	ptr_val_func accumulate_function(new accumulate());
	value_functions[std::string("accumulate")] = accumulate_function ;

}
void FunctionRegistrator::addAllStoVFunctions()
{
	stov_functions.clear();

	ptr_stov_func maxval_function(new maxval());
	stov_functions[std::string("maxval")] = maxval_function ;

	ptr_stov_func minval_function(new minval());
	stov_functions[std::string("minval")] = minval_function ;

	ptr_stov_func mean_function(new mean());
	stov_functions[std::string("mean")] = mean_function ;

	ptr_stov_func stdev_function(new stdev());
	stov_functions[std::string("stdev")] = stdev_function ;

	ptr_stov_func variance_function(new variance());
	stov_functions[std::string("variance")] = variance_function ;

}
void FunctionRegistrator::addAllStoSFunctions()
{
	stos_functions.clear();

	ptr_stos_func mvg_function(new mvg());
	stos_functions[std::string("mvg")] = mvg_function ; 

	ptr_stos_func mvg3_function(new mvg(3));
	stos_functions[std::string("mvg3")] = mvg3_function ; 

	ptr_stos_func mvg5_function(new mvg(5));
	stos_functions[std::string("mvg5")] = mvg5_function ; 

	ptr_stos_func mvg50_function(new mvg(50));
	stos_functions[std::string("mvg50")] = mvg50_function ; 

	ptr_stos_func mvg100_function(new mvg(100));
	stos_functions[std::string("mvg100")] = mvg100_function ; 
}