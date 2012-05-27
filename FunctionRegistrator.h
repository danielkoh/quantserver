#pragma once

#include <map>
#include <string>
#include <boost/shared_ptr.hpp>
#include "process_value.h"
#include "series_to_series.h"
#include "series_to_number.h"


namespace quantserver
{
	typedef boost::shared_ptr<process_value> ptr_val_func ;
	typedef boost::shared_ptr<series_to_number> ptr_stov_func ;
	typedef boost::shared_ptr<series_to_series> ptr_stos_func ;


	class FunctionRegistrator
	{
	public:
		FunctionRegistrator(void);
		virtual ~FunctionRegistrator(void);

		ScriptManager& registerAll(ScriptManager& scriptManager);

	protected:
		std::map<std::string, ptr_val_func> value_functions ;
		std::map<std::string, ptr_stov_func> stov_functions ;
		std::map<std::string, ptr_stos_func> stos_functions ;

		void addAllValueFunctions() ;
		void addAllStoVFunctions() ;
		void addAllStoSFunctions() ;
	};

	typedef boost::shared_ptr<FunctionRegistrator> FunctionRegistratorPtr ;
}

