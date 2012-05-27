#include "log_series.h"
#include <sstream>

using namespace quantserver;

log_series::log_series(void)
{
	labelf = "log";
	timeSeries = TimeSeries(labelf);
}


log_series::~log_series(void)
{
}

TimeSeries& log_series::operator() (TimeSeries& operand)
{
	timeSeries.clear();
	timeSeries.setLabel(makeLabel(operand));

	for(int i = 0 ; i < operand.size() ; i++ )
	{
		PriceAtDate toAdd = operand[i].log() ;
		timeSeries << toAdd ;
	}

	return timeSeries;
}
TimeSeries& log_series::series()
{
	return timeSeries;
}
