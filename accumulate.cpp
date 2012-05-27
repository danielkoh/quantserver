#include "accumulate.h"

using namespace quantserver;

BIGDECIMAL accumulate::operator() (PriceAtDate& priceAtDate)
{
	accumulatedValue += priceAtDate.val();
	return accumulatedValue;
}
BIGDECIMAL accumulate::operator() (const BIGDECIMAL& price)
{
	accumulatedValue += price;
	return accumulatedValue;
}