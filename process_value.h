#pragma once

#include "PriceAtDate.h"
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

namespace quantserver
{
	class process_value;
	typedef boost::shared_ptr<process_value> process_value_ptr;

	class process_value
	{
	protected:
		BIGDECIMAL accumulatedValue;
		process_value_ptr preprocess;
	public:
		process_value(process_value_ptr pre = process_value_ptr() , BIGDECIMAL val = 0.0) ;
		virtual ~process_value(void);
		BIGDECIMAL val();
		virtual BIGDECIMAL operator() (PriceAtDate& priceAtDate) = 0;
		virtual BIGDECIMAL operator() (const BIGDECIMAL& price) = 0;


		boost::function<BIGDECIMAL (BIGDECIMAL&) > f();
		

	};
}

