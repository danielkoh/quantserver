#pragma once
#include "process_value.h"

namespace quantserver
{
	class log :
		public process_value
	{
	public:
		BIGDECIMAL operator() (PriceAtDate& priceAtDate);
		BIGDECIMAL operator() (const BIGDECIMAL& price);
	};
}

