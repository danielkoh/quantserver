#pragma once
#include "variance.h"

namespace quantserver
{
	class stdev :
		public series_to_number
	{
	protected:
		variance variance_op ;
		BIGDECIMAL calculated_variance;
	public:
		stdev(void);
		virtual ~stdev(void);

		virtual BIGDECIMAL operator() (TimeSeries& timeSeries);
		const BIGDECIMAL& getLastCalculatedVariance();
		variance& getVariance();

	};
}

