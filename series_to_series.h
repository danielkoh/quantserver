#pragma once

#include <boost/function.hpp>
#include "TimeSeries.h"

namespace quantserver
{
	class series_to_series
	{
	protected:
		TimeSeries timeSeries ;
		std::string labelf;
		std::string label;
		virtual const std::string& makeLabel(TimeSeries& operand);
	public:
		series_to_series(void);
		virtual ~series_to_series(void);

		virtual TimeSeries& operator() (TimeSeries& operand) = 0;
		virtual TimeSeries& series() = 0;

		boost::function<TimeSeries& (TimeSeries&) > f();
	};
}

