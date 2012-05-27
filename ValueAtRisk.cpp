#include "ValueAtRisk.h"
#include <boost/math/distributions/normal.hpp>
#include "stdev.h"


using namespace quantserver ;
using namespace boost::math;

ValueAtRisk::ValueAtRisk(BIGDECIMAL sig)
{
	significance = sig ;

	//Make the significance figure bounded
	if(significance > 1.0)
		significance = 1.0 ;

	if(significance < 0.0)
		significance = 0.0 ;
}


ValueAtRisk::~ValueAtRisk(void)
{
}

BIGDECIMAL ValueAtRisk::operator() (TimeSeries& timeSeries)
{
	//Assuming that timeSeries is normally distributed. Probably need to log the timeSeries first...
	stdev stdev_func ;
	BIGDECIMAL s = stdev_func(timeSeries) ;
	BIGDECIMAL n = stdev_func.getVariance().getLastMean();

	normal_distribution<BIGDECIMAL> normalDist(n,s);

	return quantile(normalDist,1.0-significance) ; 
}
