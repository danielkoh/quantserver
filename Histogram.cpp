#include "Histogram.h"
#include "minval.h"
#include "maxval.h"


using namespace quantserver;


Histogram::Histogram(TimeSeries& timeSeries , int numberOfSegments)
{
	histogramItems = HistogramItemVectorPtr(new std::vector<HistogramItemPtr>());

	minval minv; maxval maxv;
	BIGDECIMAL min = minv(timeSeries);
	BIGDECIMAL max = maxv(timeSeries);

	BIGDECIMAL interval = (max - min)/numberOfSegments ;
	BIGDECIMAL curr = min;

	int i = 0 ;

	//Initiate the buckets
	for(i = 0 ; i < numberOfSegments ; i++ )
	{
		HistogramItemPtr itemToAdd(new RangedHistogramItem(curr,curr + interval));
		curr += interval;
		histogramItems->push_back(itemToAdd);
	}

	//Register the items of the time series
	int seriesSize = timeSeries.size();
	int halfPoint = seriesSize/2;
	for(i = 0 ; i < seriesSize ; i++)
	{
		PriceAtDate& currRef = timeSeries[i] ;

		for(int j = 0 ; j < numberOfSegments ; j++ )
		{
			HistogramItemPtr item = histogramItems->at(j);

			if(item->accept(currRef))
			{
				break;
			}
		}
	}


	//Find the median. The histogram currently has all its members sorted
	unsigned int accumulateItems = 0;
	for(i = 0 ; i < numberOfSegments ; i++ )
	{
		HistogramItemPtr item = histogramItems->at(i);

		if(accumulateItems <= halfPoint && (accumulateItems + item->getCount()) >= halfPoint )
		{
			medianIndex = i;
			break;
		}

		accumulateItems += item->getCount();
	}
}
Histogram::~Histogram(void)
{
	histogramItems->clear();
}

int Histogram::size()
{
	return histogramItems->size();
}

unsigned int Histogram::getMedianIndex()
{
	return medianIndex;
}


BIGDECIMAL Histogram::median()
{
	return (*this)[medianIndex].val();
}
HistogramItem& Histogram::operator[](unsigned int i)
{
	unsigned int arraySz = size();

	if( i < 0 ) {i = 0;};
	if( i >= arraySz ) {i = arraySz -1;};

	return *(histogramItems->at(i)) ;
}
