#pragma once
#include "series_to_number.h"

namespace quantserver
{
	class maxval :
		public series_to_number
	{
	public:
		maxval(void);
		virtual ~maxval(void);

		virtual BIGDECIMAL operator() (TimeSeries& timeSeries);
	};
}

