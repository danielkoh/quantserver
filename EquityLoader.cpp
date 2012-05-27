#include "EquityLoader.h"
#include <chaiscript/utility/utility.hpp>

using namespace quantserver;

ScriptManager& EquityLoader::chai(ScriptManager& scriptManager)
{
	chaiscript::ModulePtr m = chaiscript::ModulePtr(new chaiscript::Module());

	CHAISCRIPT_CLASS( m, 
       EquityLoader,
       (EquityLoader())
	   (EquityLoader(const EquityLoader&)),
	   ((loadStock)(StockPtr (EquityLoader::*)(std::string&)))
	   ((loadStock)(PtrStockVector (EquityLoader::*)(std::vector<std::string>& )))
	
	);

	scriptManager.engine().add(m) ;
	return scriptManager ;
}

EquityLoader::EquityLoader(void)
{
}


EquityLoader::~EquityLoader(void)
{
}

StockPtr EquityLoader::loadStock(std::string& stock)
{
	std::vector<std::string> singleSymbol ;
	singleSymbol.push_back(stock) ;

	PtrStockVector loaded = loadStock(singleSymbol);

	if(loaded->size() > 0 )
	{
		return loaded->at(0);
	}
	else
	{
		return StockPtr();
	}
}

PtrStockVector EquityLoader::loadStock(std::vector<std::string>& stocks)
{
	ptr_stockMetaDataPtrCollection stockMetaDatas = additionalInfoLoader.getStockMetaData(stocks) ;

	PtrStockVector toRt(new StockPtrVector);

	for(int i = 0 ; i < stockMetaDatas->size() ; i++ )
	{
		const ptr_stockMetaData& meta = stockMetaDatas->at(i);
		std::string historicalDataUrl = FinanceDataLoader::getYahooHistoricalDataUrl(meta->symbol());
		FinanceDataLoader financeDataLoader(historicalDataUrl , true);

		CSVParser csvParser(financeDataLoader.getLocalReadable());
		StockPtr stockPtr(new Stock(meta->symbol() , meta));
		stockPtr->loadData(csvParser);
		toRt->push_back(stockPtr) ;
	}

	return toRt ;
}
