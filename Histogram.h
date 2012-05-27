#pragma once
#include "TimeSeries.h"
#include "RangedHistogramItem.h"
#include <vector>
#include <boost/shared_ptr.hpp>

namespace quantserver
{
	typedef boost::shared_ptr<RangedHistogramItem> HistogramItemPtr;
	typedef boost::shared_ptr<std::vector<HistogramItemPtr>> HistogramItemVectorPtr;

	class Histogram
	{
	protected:
		HistogramItemVectorPtr histogramItems;
		unsigned int medianIndex ;
	public:
		Histogram(TimeSeries& timeSeries , int numberOfSegments = 100);
		virtual ~Histogram(void);

		int size();
		unsigned int getMedianIndex();
		BIGDECIMAL median();
		HistogramItem& operator[](unsigned int i);
	};

	typedef boost::shared_ptr<Histogram> HistogramPtr;
}

