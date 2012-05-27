#include "mvg.h"
#include <string>
#include <sstream>
using namespace quantserver;


mvg::mvg(unsigned int moving_days)
{
	if(moving_days < 1)
	{
		moving_days = 1;
	}
	days = moving_days;
	std::stringstream stringStream ;
	stringStream << "mvg" << moving_days ;
	
	labelf = stringStream.str();
	timeSeries = TimeSeries(labelf);
}


mvg::~mvg(void)
{
}

TimeSeries& mvg::operator() (TimeSeries& operand)
{
	timeSeries.clear();
	timeSeries.setLabel(makeLabel(operand));

	for(int i = 0 ; i < operand.size() ; i++ )
	{
		PriceAtDate toAdd(operand[i]) ;

		for(int j = 1 ; j < days ; j++ )
		{
			toAdd += operand[i + j] ;
		}

		toAdd /= days;

		timeSeries << toAdd ;
	}

	return timeSeries ;
}

TimeSeries& mvg::series()
{
	return timeSeries ;
}