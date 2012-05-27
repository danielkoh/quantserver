#include "process_value.h"

using namespace quantserver;

process_value::process_value(process_value_ptr pre , BIGDECIMAL val)
{
	preprocess = pre;
	accumulatedValue = val;
}


process_value::~process_value(void)
{
}

BIGDECIMAL process_value::val()
{
	return accumulatedValue;
}

boost::function<BIGDECIMAL (BIGDECIMAL&) > process_value::f()
{
	boost::function<BIGDECIMAL (BIGDECIMAL&)> f = boost::ref(*this);
	return f;
}
