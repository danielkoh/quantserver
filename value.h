#pragma once
#include "process_value.h"

namespace quantserver
{
	class value :
		public process_value
	{
	public:
		virtual BIGDECIMAL operator() (PriceAtDate& priceAtDate);
		virtual BIGDECIMAL operator() (const BIGDECIMAL& price);
	};
}

