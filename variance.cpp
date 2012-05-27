#include "variance.h"
#include "mean.h"
#include <math.h>

using namespace quantserver ;

variance::variance()
	:series_to_number()
{
	average = 0.0 ;
	accumulated_difference_square = 0.0 ;
	mean_op = mean();
	calculated_variance = 0.0 ;
}



variance::~variance(void)
{
}

mean& variance::getMean()
{
	return mean_op;
}

BIGDECIMAL variance::operator() (TimeSeries& timeSeries)
{
	
	average = mean_op(timeSeries);


	for(unsigned int i = 0 ; i < timeSeries.size() ; i++ )
	{
		BIGDECIMAL diff = average - timeSeries[i].val() ;
		accumulated_difference_square += (diff * diff) ;
	}

	calculated_variance = accumulated_difference_square/timeSeries.size();

	return calculated_variance ;

}

const BIGDECIMAL& variance::getLastAccumulatedDifferenceSquare()
{
	return accumulated_difference_square ;
}


const BIGDECIMAL& variance::getLastMean()
{
	return average;
}