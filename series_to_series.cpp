#include "series_to_series.h"
#include <boost/ref.hpp>

using namespace quantserver;
series_to_series::series_to_series(void)
{
}


series_to_series::~series_to_series(void)
{
}

const std::string& series_to_series::makeLabel(TimeSeries& operand)
{
	std::stringstream stringStream ;
	stringStream << labelf << "(" << operand.getLabel() << ")" ;
	label = stringStream.str();
	return label;
}

boost::function<TimeSeries& (TimeSeries&) > series_to_series::f()
{
	boost::function<TimeSeries& (TimeSeries&)> f = boost::ref(*this);
	return f;
}