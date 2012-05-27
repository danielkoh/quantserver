#include "makehistogram.h"

using namespace quantserver;

makehistogram::makehistogram(int segments)
{
	histogramPtr = HistogramPtr();
	nSegments = segments;
}
makehistogram::~makehistogram(void)
{
	nSegments = 0;
}

Histogram& makehistogram::operator() (TimeSeries& timeSeries)
{
	histogramPtr = HistogramPtr( new Histogram(timeSeries , nSegments));
	return *histogramPtr;
}
HistogramPtr makehistogram::getHistogramPtr()
{
	return histogramPtr;
}