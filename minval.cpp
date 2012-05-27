#include "minval.h"

using namespace quantserver;

minval::minval(void)
{
}


minval::~minval(void)
{
}

BIGDECIMAL minval::operator() (TimeSeries& timeSeries)
{
	int size = timeSeries.size();
	BIGDECIMAL currentMin = 10000000000000.0;
	for(int i = 0 ; i < size ; i++ )
	{
		if(timeSeries[i].val() < currentMin)
		{
			currentMin = timeSeries[i].val();
		}
	}

	return currentMin ;
}
