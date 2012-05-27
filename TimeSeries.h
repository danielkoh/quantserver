#pragma once

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "PriceAtDate.h"

namespace quantserver
{
	typedef boost::shared_ptr<quantserver::PriceAtDate> PricePtr;
	typedef boost::shared_ptr<std::vector<PricePtr>> PriceVectorPtr;
	
	class TimeSeries
	{
	public:
		static ScriptManager& chai(ScriptManager& scriptManager);

		TimeSeries();
		TimeSeries(const std::string& label);
		TimeSeries(const TimeSeries& copy);
		virtual ~TimeSeries(void);

		const std::string& getLabel();
		void setLabel(const std::string& l);
		PricePtr& getPriceAt(unsigned int index);
		void addPriceData(PricePtr& price);
		void addPriceData(PriceAtDate& price);
		TimeSeries& resetOffset();
		unsigned int size();

		//operations
		TimeSeries copy();
		TimeSeries& clear();

		//Note: log(x/y) = logx - logy
		//logreturns(series) = log(series) - log(series-1)
		TimeSeries log();
		//Note: exp(log(x)) = x ; exp(x) = integrate(exp(x)) and exp(x) = differentiate(exp(x))
		TimeSeries exp();


		//Operator overloads
		PriceAtDate& operator[](unsigned int index);
		TimeSeries& operator<<(PricePtr& price);
		TimeSeries& operator<<(PriceAtDate& price);
		TimeSeries& operator=(TimeSeries& copy);

		//Do time series math
		TimeSeries& operator+=(TimeSeries& rhs);
		TimeSeries& operator-=(TimeSeries& rhs);
		TimeSeries& operator/=(TimeSeries& rhs);
		TimeSeries& operator*=(TimeSeries& rhs);

		TimeSeries operator+(TimeSeries& rhs);
		TimeSeries operator-(TimeSeries& rhs);
		TimeSeries operator/(TimeSeries& rhs);
		TimeSeries operator*(TimeSeries& rhs);

		//Shift the time series
		TimeSeries operator+(int offsetAmount);
		TimeSeries& operator+=(int offsetAmount);
		TimeSeries operator-(int offsetAmount);
		TimeSeries& operator-=(int offsetAmount);
		TimeSeries& operator++();
		TimeSeries& operator--();

		
		//Times or Divide the time series
		TimeSeries operator*(const BIGDECIMAL& amount);
		TimeSeries& operator*=(const BIGDECIMAL& amount);
		TimeSeries operator/(const BIGDECIMAL& amount);
		TimeSeries& operator/=(const BIGDECIMAL& amount);

	protected:
		std::string label;
		//Use smart ptr to reference time series data to prevent huge memory copies
		PriceVectorPtr ptrToTimeSeriesData ;
		int offset ;
	};
}

