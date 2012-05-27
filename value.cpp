#include "value.h"

using namespace quantserver;

BIGDECIMAL value::operator() (PriceAtDate& priceAtDate)
{
	accumulatedValue = priceAtDate.val();
	return accumulatedValue;
}
BIGDECIMAL value::operator() (const BIGDECIMAL& price)
{
	accumulatedValue = price;
	return accumulatedValue;
}