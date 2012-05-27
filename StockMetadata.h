#pragma once

#include "PriceAtDate.h"
#include "CSVParser.h"


namespace quantserver
{
	#define ERROR_VAL -99.99

	class StockMetadata
	{
		//Qualitative analyst-ish data to expose for calculation. For example, close > 10% less than book value
	protected:
		std::string _symbol ;
		std::string _name ;
		BIGDECIMAL _eps;
		BIGDECIMAL _epsEstimate ;
		BIGDECIMAL _epsEstimateNextYr;
		BIGDECIMAL _ebitda;
		BIGDECIMAL _pe_ratio;
		BIGDECIMAL _peg_ratio;
		BIGDECIMAL _ps_ratio;
		BIGDECIMAL _bookValue;
		BIGDECIMAL _outstandingShares; 
		BIGDECIMAL _targetPrice; 
		BIGDECIMAL _marketCap; 
		BIGDECIMAL _dividendYield;
		BIGDECIMAL _dividendPerShare;
		BIGDECIMAL _bid;
		BIGDECIMAL _ask;


		BIGDECIMAL parseValAt(PtrStringVector& data , int i);
		
		
	public:
		static ScriptManager& chai(ScriptManager& scriptManager);

		StockMetadata(void);
		StockMetadata(std::string& symbol , PtrStringVector& data);
		virtual ~StockMetadata(void);

		//Getters
		const std::string& symbol() ;
		const std::string& name() ;
		BIGDECIMAL eps();
		BIGDECIMAL epsEstimate() ;
		BIGDECIMAL epsEstimateNextYr();
		BIGDECIMAL ebitda();
		BIGDECIMAL pe_ratio();
		BIGDECIMAL peg_ratio();
		BIGDECIMAL ps_ratio();
		BIGDECIMAL bookValue();
		BIGDECIMAL outstandingShares(); 
		BIGDECIMAL targetPrice(); 
		BIGDECIMAL marketCap(); 
		BIGDECIMAL dividendYield(); 
		BIGDECIMAL dividendPerShare(); 
		BIGDECIMAL bid(); 
		BIGDECIMAL ask(); 



		static PtrStringVector getRequiredItems();
	};
}

