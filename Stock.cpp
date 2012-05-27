#include "Stock.h"
#include <chaiscript/utility/utility.hpp>

#define MOST_RELEVANT std::string("Close")

using namespace quantserver;

ScriptManager& Stock::chai(ScriptManager& scriptManager)
{
	chaiscript::ModulePtr m = chaiscript::ModulePtr(new chaiscript::Module());

	CHAISCRIPT_CLASS( m, 
       Stock,
       (Stock(const std::string&))
	   (Stock(const std::string& , const StockMetaDataPtr&))
	   (Stock(const Stock&)),
	   ((getSymbol))
	   ((addTimeSeriesData))
	   ((getTimeSeriesData))
	   ((getCurrentPrice))
	   ((getMostRelevantTimeSeries))
	   ((meta))
	   ((hasMetaData))
	   ((operator[]))
	);

	scriptManager.engine().add(m) ;
	return scriptManager ;
}



Stock::Stock(const std::string& s)
{
	symbol = s ;
	metaData = StockMetaDataPtr();
}

Stock::Stock(const std::string& s , const StockMetaDataPtr& meta)
{
	symbol = s ;
	metaData = meta ;
}


Stock::~Stock(void)
{
	priceData.clear();
}

Stock& Stock::loadData(CSVParser& data)
{
	//Assume that the first column of data is the date data
	int numberOfColumns = data.getNumberOfColumns();
	int rowsOfData = data.getNumberOfLines();
	
	//Initialize the indicators
	for(int i = 1 ; i < numberOfColumns ; i++ )
	{
		const std::string& headerString = data.getHeaderOfIndex(i);
		priceData[headerString] = TimeSeriesPtr(new TimeSeries(headerString));
	}

	//Load up the data
	for(int i = 0 ; i < rowsOfData ; i++ )
	{
		PtrStringVector rowData = data.getDataAt(i);
		std::string dateData = rowData->at(0);
		DatePtr date = PriceAtDate::parseDateIso(dateData);

		//std::cout << "Date is: " << *date ;

		for(int j = 1 ; j < numberOfColumns ; j++ )
		{	
			std::string dataString = rowData->at(j);
			const std::string& headerString = data.getHeaderOfIndex(j);
			PricePtr price = PricePtr(new PriceAtDate(date , dataString)) ;
			priceData[headerString]->addPriceData(price);
		}
	}
	
	return *this;
}

const std::string& Stock::getSymbol()
{
	return symbol;
}

PriceAtDate& Stock::getCurrentPrice()
{
	return getMostRelevantTimeSeries()[0];
}
TimeSeries& Stock::getMostRelevantTimeSeries()
{
	return *(priceData[MOST_RELEVANT]) ;
}

void Stock::addTimeSeriesData(const std::string& key , TimeSeriesPtr& data)
{
	priceData[key] = data ;
}


TimeSeriesPtr Stock::getTimeSeriesData(const std::string& key)
{
	return priceData[key];
}

TimeSeries& Stock::operator[](const std::string& key)
{
	return *(priceData[key]);
}

void Stock::setMetaData(const StockMetaDataPtr& meta)
{
	metaData = meta;
}

StockMetadata& Stock::meta()
{
	return *metaData;
}

bool Stock::hasMetaData()
{
	return !(!metaData) ;
}