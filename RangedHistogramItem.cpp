#include "RangedHistogramItem.h"

using namespace quantserver;
RangedHistogramItem::RangedHistogramItem(BIGDECIMAL min , BIGDECIMAL max)
{
	minValue = min;
	maxValue = max;
}


RangedHistogramItem::~RangedHistogramItem(void)
{
}

bool RangedHistogramItem::accept(PriceAtDate& priceItem)
{
	if(priceItem.val() >= minValue && priceItem.val() < maxValue)
	{
		count++ ;
		return true ;
	}
	else
	{
		return false;
	}
}

BIGDECIMAL RangedHistogramItem::min()
{
	return minValue ;
}
BIGDECIMAL RangedHistogramItem::max()
{
	return maxValue;
}

BIGDECIMAL RangedHistogramItem::val()
{
	return (minValue + maxValue)/2;
}
