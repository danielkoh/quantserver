#include "maxval.h"

using namespace quantserver;
maxval::maxval(void)
{
}


maxval::~maxval(void)
{
}


BIGDECIMAL maxval::operator() (TimeSeries& timeSeries)
{
	int size = timeSeries.size();
	BIGDECIMAL currentMax = -10000000000000.0;
	for(int i = 0 ; i < size ; i++ )
	{
		if(timeSeries[i].val() > currentMax)
		{
			currentMax = timeSeries[i].val();
		}
	}

	return currentMax ;
}
