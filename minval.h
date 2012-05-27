#pragma once
#include "series_to_number.h"
namespace quantserver
{
	class minval :
		public series_to_number
	{
	public:
		minval(void);
		virtual ~minval(void);

		virtual BIGDECIMAL operator() (TimeSeries& timeSeries);
	};
}

