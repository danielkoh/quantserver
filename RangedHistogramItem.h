#pragma once
#include "HistogramItem.h"

namespace quantserver
{
	class RangedHistogramItem : public HistogramItem 
	{
	protected:
		BIGDECIMAL minValue ;
		BIGDECIMAL maxValue ;
	public:
		RangedHistogramItem(BIGDECIMAL min , BIGDECIMAL max);

		~RangedHistogramItem(void);

		virtual bool accept(PriceAtDate& priceItem) ;
		virtual BIGDECIMAL min();
		virtual BIGDECIMAL max();
		virtual BIGDECIMAL val();
	};
}

