#pragma once
#include "mean.h"

namespace quantserver
{
	class variance :
		public series_to_number
	{
		mean mean_op;
		BIGDECIMAL average;
		BIGDECIMAL accumulated_difference_square;
		BIGDECIMAL calculated_variance;

	public:
		variance();
		virtual ~variance(void);

		virtual BIGDECIMAL operator() (TimeSeries& timeSeries);
		mean& getMean();

		const BIGDECIMAL& getLastMean();
		const BIGDECIMAL& getLastAccumulatedDifferenceSquare();
	};
}

