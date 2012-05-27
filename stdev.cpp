#include "stdev.h"
#include <math.h>

using namespace quantserver;

stdev::stdev(void)
{
	variance_op = variance();
	calculated_variance = 0.0 ;
}


stdev::~stdev(void)
{
}

BIGDECIMAL stdev::operator() (TimeSeries& timeSeries)
{
	calculated_variance = variance_op(timeSeries) ;
	return sqrt(calculated_variance);

}

const BIGDECIMAL& stdev::getLastCalculatedVariance()
{
	return calculated_variance;
}
variance& stdev::getVariance()
{
	return variance_op;
}
