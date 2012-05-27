#pragma once

#include "Histogram.h"

namespace quantserver
{
	class makehistogram
	{
	protected:
		int nSegments;
		HistogramPtr histogramPtr;
	public:
		makehistogram(int segments = 100);
		~makehistogram(void);

		Histogram& operator() (TimeSeries& timeSeries);
		HistogramPtr getHistogramPtr();
	};
}

