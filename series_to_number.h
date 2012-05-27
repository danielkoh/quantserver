#pragma once

#include <boost/function.hpp>
#include "TimeSeries.h"

namespace quantserver
{
	class series_to_number
	{
	public:
		series_to_number(void);
		virtual ~series_to_number(void);

	public:
		virtual BIGDECIMAL operator() (TimeSeries& timeSeries) = 0;

		boost::function<BIGDECIMAL (TimeSeries&) > f();
	};
}

