#pragma once
#include "series_to_number.h"

namespace quantserver
{
	class ValueAtRisk :
		public series_to_number
	{
	public:
		ValueAtRisk(BIGDECIMAL sig = 0.95);
		virtual ~ValueAtRisk(void);

		virtual BIGDECIMAL operator() (TimeSeries& timeSeries) ;

	protected:
		BIGDECIMAL significance ; 
	};
}

