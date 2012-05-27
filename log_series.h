#pragma once
#include "series_to_series.h"

namespace quantserver
{
	class log_series :
		public series_to_series
	{
	protected:
		std::string labelf;
		TimeSeries timeSeries ;
	public:
		log_series(void);
		virtual ~log_series(void);

		virtual TimeSeries& operator() (TimeSeries& operand);
		virtual TimeSeries& series() ;
	};
}

