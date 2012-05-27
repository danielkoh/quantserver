#pragma once
#include "series_to_series.h"
#include <string>

namespace quantserver
{
	class mvg :
		public series_to_series
	{
	protected:
		unsigned int days;
	public:
		
		mvg(unsigned int moving_days = 3);
		virtual ~mvg(void);

		virtual TimeSeries& operator() (TimeSeries& timeSeries);

		virtual TimeSeries& series();
	};
}

