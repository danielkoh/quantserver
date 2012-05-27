#include "TimeSeries.h"
#include <chaiscript/utility/utility.hpp>

using namespace quantserver;

ScriptManager& TimeSeries::chai(ScriptManager& scriptManager)
{
	chaiscript::ModulePtr m = chaiscript::ModulePtr(new chaiscript::Module());
	CHAISCRIPT_CLASS( m, 
       TimeSeries,
       (TimeSeries())
	   (TimeSeries (const std::string&))
	   (TimeSeries (const TimeSeries &)),
	   ((getLabel))
	   ((setLabel))
	   ((resetOffset))
	   ((size))
	   ((copy))
	   ((clear))
	   ((log))
	   ((exp))
	   ((operator[]))
	   ((operator=))
	   ((operator++))
	   ((operator--))
	   ((operator<<)(TimeSeries& (TimeSeries::*)(PricePtr&)))
	   ((operator<<)(TimeSeries& (TimeSeries::*)(PriceAtDate&)))
	   ((operator*=)(TimeSeries& (TimeSeries::*)(TimeSeries& )))
	   ((operator*=)(TimeSeries& (TimeSeries::*)(const BIGDECIMAL& )))
	   ((operator/=)(TimeSeries& (TimeSeries::*)(TimeSeries& )))
	   ((operator/=)(TimeSeries& (TimeSeries::*)(const BIGDECIMAL& )))
	   ((operator+=)(TimeSeries& (TimeSeries::*)(TimeSeries& )))
	   ((operator+=)(TimeSeries& (TimeSeries::*)(int)))
	   ((operator-=)(TimeSeries& (TimeSeries::*)(TimeSeries& )))
	   ((operator-=)(TimeSeries& (TimeSeries::*)(int)))
	   ((operator+)(TimeSeries (TimeSeries::*)(TimeSeries& )))
	   ((operator+)(TimeSeries (TimeSeries::*)(int)))
	   ((operator-)(TimeSeries (TimeSeries::*)(TimeSeries& )))
	   ((operator-)(TimeSeries (TimeSeries::*)(int)))
	   ((operator/)(TimeSeries (TimeSeries::*)(TimeSeries& )))
	   ((operator/)(TimeSeries (TimeSeries::*)(const BIGDECIMAL& )))
	   ((operator*)(TimeSeries (TimeSeries::*)(TimeSeries& )))
	   ((operator/)(TimeSeries (TimeSeries::*)(const BIGDECIMAL& )))
	   
     );

	
	scriptManager.engine().add(m) ;
	return scriptManager ;
}

TimeSeries::TimeSeries()
{
	label = "timeSeries";
	ptrToTimeSeriesData = PriceVectorPtr(new std::vector<PricePtr>());
	offset = 0;
}

TimeSeries::TimeSeries(const std::string& l)
{
	label = l;
	ptrToTimeSeriesData = PriceVectorPtr(new std::vector<PricePtr>());
	offset = 0;
}

TimeSeries::TimeSeries(const TimeSeries& copy)
{
	label = copy.label;
	offset = copy.offset;
	ptrToTimeSeriesData = copy.ptrToTimeSeriesData;
}

TimeSeries& TimeSeries::operator=(TimeSeries& copy)
{
	label = copy.label;
	offset = copy.offset;
	ptrToTimeSeriesData = copy.ptrToTimeSeriesData;

	return *this;
}

TimeSeries::~TimeSeries(void)
{
}

TimeSeries& TimeSeries::clear()
{
	ptrToTimeSeriesData->clear();
	return *this;
}


const std::string& TimeSeries::getLabel()
{
	return label;
}

void TimeSeries::setLabel(const std::string& l)
{
	label = l;
}
PricePtr& TimeSeries::getPriceAt(unsigned int index)
{
	index += offset;
	if(index < 0){index = 0;}
	if(index >= ptrToTimeSeriesData->size()){index = ptrToTimeSeriesData->size()-1;}

	return ptrToTimeSeriesData->at(index);
}
void TimeSeries::addPriceData(PricePtr& price)
{
	ptrToTimeSeriesData->push_back(price);
}

void TimeSeries::addPriceData(PriceAtDate& price)
{
	PricePtr pricePtr = PricePtr(new PriceAtDate(price));
	ptrToTimeSeriesData->push_back(pricePtr);
}

TimeSeries& TimeSeries::resetOffset()
{
	offset = 0;
	return *this;
}

unsigned int TimeSeries::size()
{
	return (ptrToTimeSeriesData->size() - offset);
}


//Make a deep copy of the time series
TimeSeries TimeSeries::copy()
{
	TimeSeries toRt(this->label);

	//Do a raw copy irregardless of offset
	for(unsigned int i = 0 ; i < ptrToTimeSeriesData->size() ; i++ )
	{
		toRt.addPriceData(*(ptrToTimeSeriesData->at(i))) ;
	}

	return toRt ;
}

//Operator overloads
PriceAtDate& TimeSeries::operator[](unsigned int index)
{
	//index must be safe. Unless we do not have data
	index += offset;
	if(index < 0){index = 0;}
	if(index >= ptrToTimeSeriesData->size()){index = ptrToTimeSeriesData->size()-1;}

	return *(ptrToTimeSeriesData->at(index));
}

TimeSeries& TimeSeries::operator<<(PricePtr& price)
{
	ptrToTimeSeriesData->push_back(price);
	return *this;
}

TimeSeries& TimeSeries::operator<<(PriceAtDate& price)
{
	PricePtr pricePtr = PricePtr(new PriceAtDate(price));
	ptrToTimeSeriesData->push_back(pricePtr);
	return *this;
}


//Offset to the front
TimeSeries& TimeSeries::operator+=(int offsetAmount)
{
	offset += offsetAmount;
	return *this;
}
TimeSeries TimeSeries::operator+(int offsetAmount)
{
	TimeSeries toRt(*this);
	toRt.offset += offsetAmount;
	return toRt ;
}
TimeSeries& TimeSeries::operator++()
{
	return ((*this)+=1);
}



//Offset to the back
TimeSeries& TimeSeries::operator-=(int offsetAmount)
{
	offset -= offsetAmount;
	return *this;
}
TimeSeries TimeSeries::operator-(int offsetAmount)
{
	TimeSeries toRt(*this);
	toRt.offset -= offsetAmount;
	return toRt ;
}
TimeSeries& TimeSeries::operator--()
{
	return ((*this)-=1);
}


//Multiply everything by some amount (Rather inefficient)
TimeSeries TimeSeries::operator*(const BIGDECIMAL& offsetAmount)
{
	TimeSeries toRt(this->label);

	//Do a raw copy irregardless of offset
	for(unsigned int i = 0 ; i < ptrToTimeSeriesData->size() ; i++ )
	{
		toRt.addPriceData( *(ptrToTimeSeriesData->at(i)) * offsetAmount ) ;
	}

	return toRt ;
}



TimeSeries& TimeSeries::operator*=(const BIGDECIMAL& amount)
{
	for(unsigned int i = 0 ; i < ptrToTimeSeriesData->size() ; i++ )
	{
		*(ptrToTimeSeriesData->at(i)) *= amount  ;
	}
	return *this;
}

TimeSeries TimeSeries::operator/(const BIGDECIMAL& offsetAmount)
{
	TimeSeries toRt(this->label);

	//Do a raw copy irregardless of offset
	for(unsigned int i = 0 ; i < ptrToTimeSeriesData->size() ; i++ )
	{
		toRt.addPriceData( *(ptrToTimeSeriesData->at(i)) / offsetAmount ) ;
	}

	return toRt ;
}

TimeSeries& TimeSeries::operator/=(const BIGDECIMAL& amount)
{
	for(unsigned int i = 0 ; i < ptrToTimeSeriesData->size() ; i++ )
	{
		*(ptrToTimeSeriesData->at(i)) /= amount  ;
	}
	return *this;
}

//Time series math
//Do time series math
TimeSeries& TimeSeries::operator+=(TimeSeries& rhs)
{
	for(unsigned int i = 0 ; i < size() ; i++ )
	{
		(*this)[i] += rhs[i] ;
	}

	return *this;
}
TimeSeries& TimeSeries::operator-=(TimeSeries& rhs)
{
	for(unsigned int i = 0 ; i < size() ; i++ )
	{
		(*this)[i] -= rhs[i] ;
	}

	return *this;
}
TimeSeries& TimeSeries::operator/=(TimeSeries& rhs)
{
	for(unsigned int i = 0 ; i < size() ; i++ )
	{
		if(rhs[i].val() != 0.0)
		{
			(*this)[i] /= rhs[i] ;
		}
	}

	return *this;
}
TimeSeries& TimeSeries::operator*=(TimeSeries& rhs)
{
	for(unsigned int i = 0 ; i < size() ; i++ )
	{
		if(rhs[i].val() != 0.0)
		{
			(*this)[i] /= rhs[i] ;
		}
	}

	return *this;
}

//The binary operators rely on the copy function and the mutating operators
TimeSeries TimeSeries::operator+(TimeSeries& rhs)
{
	TimeSeries toRt = this->copy();
	return toRt += rhs;
}
TimeSeries TimeSeries::operator-(TimeSeries& rhs)
{
	TimeSeries toRt = this->copy();
	return toRt -= rhs;
}
TimeSeries TimeSeries::operator/(TimeSeries& rhs)
{
	TimeSeries toRt = this->copy();
	return toRt /= rhs;
}
TimeSeries TimeSeries::operator*(TimeSeries& rhs)
{
	TimeSeries toRt = this->copy();
	return toRt *= rhs;
}


//Copy++ functions. I.e. to copying and do natural log
TimeSeries TimeSeries::log()
{
	TimeSeries toRt(this->label);

	//Do a raw copy irregardless of offset
	for(unsigned int i = 0 ; i < ptrToTimeSeriesData->size() ; i++ )
	{
		toRt.addPriceData(ptrToTimeSeriesData->at(i)->log()) ;
	}

	return toRt ;
}

//Copy++ functions. I.e. to copying and do natural exp
TimeSeries TimeSeries::exp()
{
	TimeSeries toRt(this->label);

	//Do a raw copy irregardless of offset
	for(unsigned int i = 0 ; i < ptrToTimeSeriesData->size() ; i++ )
	{
		toRt.addPriceData(ptrToTimeSeriesData->at(i)->exp()) ;
	}

	return toRt ;
}

