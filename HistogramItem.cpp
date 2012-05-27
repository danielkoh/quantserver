#include "HistogramItem.h"

using namespace quantserver;

HistogramItem::HistogramItem(void)
{
	count = 0 ;
}


HistogramItem::~HistogramItem(void)
{
}

int HistogramItem::getCount()
{
	return count;
}

