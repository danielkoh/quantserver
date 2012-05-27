#pragma once

#include "PriceAtDate.h"


namespace quantserver
{
	class HistogramItem
	{
	protected:
		int count;
	public:
		HistogramItem(void);
		virtual ~HistogramItem(void);

		virtual bool accept(PriceAtDate& priceItem) = 0 ;
		virtual BIGDECIMAL min() = 0;
		virtual BIGDECIMAL max() = 0;
		virtual BIGDECIMAL val() = 0;
		int getCount() ;


	};
}

