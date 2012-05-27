#pragma once
#include "series_to_number.h"

namespace quantserver
{
	class mean :
		public series_to_number
	{
	protected:
		BIGDECIMAL accumulatedValue;
	public:
		mean(void);
		virtual ~mean(void);

		virtual BIGDECIMAL operator() (TimeSeries& timeSeries);
	};
}

