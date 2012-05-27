#pragma once

#include "Stock.h"
#include "AdditionalInformation.h"
#include "FinanceDataLoader.h"
#include <vector>
#include <boost/shared_ptr.hpp>

namespace quantserver
{
	typedef boost::shared_ptr<Stock> StockPtr;
	typedef std::vector<StockPtr> StockPtrVector ;
	typedef boost::shared_ptr<StockPtrVector> PtrStockVector ;


	class EquityLoader
	{
	public:
		static ScriptManager& chai(ScriptManager& scriptManager);

		EquityLoader(void);
		virtual ~EquityLoader(void);
		StockPtr loadStock(std::string& stock);
		PtrStockVector loadStock(std::vector<std::string>& stocks);

	protected:
		AdditionalInformation additionalInfoLoader;
	};
}

