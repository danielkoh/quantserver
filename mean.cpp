#include "mean.h"

using namespace quantserver;

mean::mean(void)
{
	accumulatedValue = 0.0;
}


mean::~mean(void)
{
}


BIGDECIMAL mean::operator() (TimeSeries& timeSeries)
{
	accumulatedValue = 0.0;

	for(unsigned int i = 0 ; i < timeSeries.size() ; i++ )
	{
		accumulatedValue += timeSeries[i].val();
	}

	return (accumulatedValue/timeSeries.size()) ;
}