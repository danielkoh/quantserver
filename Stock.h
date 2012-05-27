#pragma once

#include <map>
#include <string>
#include "CSVParser.h"
#include "TimeSeries.h"
#include "StockMetadata.h"
#include <boost/shared_ptr.hpp>


namespace quantserver
{
	typedef boost::shared_ptr<TimeSeries> TimeSeriesPtr;
	typedef boost::shared_ptr<StockMetadata> StockMetaDataPtr;


	class Stock
	{
	public:
		static ScriptManager& chai(ScriptManager& scriptManager);

		
		Stock(const std::string& symbol);
		Stock(const std::string& symbol , const StockMetaDataPtr& meta);
		virtual ~Stock(void);
		
		Stock& loadData(CSVParser& data);
		const std::string& getSymbol() ;
		void addTimeSeriesData(const std::string& key , TimeSeriesPtr& data);
		TimeSeriesPtr getTimeSeriesData(const std::string& key);

		PriceAtDate& getCurrentPrice();
		TimeSeries& getMostRelevantTimeSeries();

		void setMetaData(const StockMetaDataPtr& meta) ;
		StockMetadata& meta();
		bool hasMetaData();

		//operator overloads
		TimeSeries& operator[](const std::string& key);


	protected:
		std::map<std::string,TimeSeriesPtr> priceData;
		std::string symbol ;
		StockMetaDataPtr metaData;
	};
}

