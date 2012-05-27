#include "series_to_number.h"

using namespace quantserver;
series_to_number::series_to_number(void)
{
}


series_to_number::~series_to_number(void)
{
}

boost::function<BIGDECIMAL (TimeSeries&) > series_to_number::f()
{
	boost::function<BIGDECIMAL (TimeSeries&)> f = boost::ref(*this);
	return f;
}