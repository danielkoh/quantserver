#include "log.h"
#include <math.h>

using namespace quantserver;

BIGDECIMAL log::operator() (PriceAtDate& priceAtDate)
{
	accumulatedValue = ::log(priceAtDate.val()) ;
	return accumulatedValue;

}
BIGDECIMAL log::operator() (const BIGDECIMAL& price)
{
	accumulatedValue = ::log(price) ;
	return accumulatedValue;
}