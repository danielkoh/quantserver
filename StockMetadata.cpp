#include "StockMetadata.h"
#include <boost/lexical_cast.hpp>
#include <chaiscript/utility/utility.hpp>


using namespace quantserver;

ScriptManager& StockMetadata::chai(ScriptManager& scriptManager)
{
	chaiscript::ModulePtr m = chaiscript::ModulePtr(new chaiscript::Module());

	CHAISCRIPT_CLASS( m, 
       StockMetadata,
       (StockMetadata())
	   (StockMetadata(const StockMetadata&)),
	   ((symbol))
	   ((name))
	   ((eps))
	   ((epsEstimate))
	   ((epsEstimateNextYr))
	   ((ebitda))
	   ((pe_ratio))
	   ((peg_ratio))
	   ((ps_ratio))
	   ((bookValue))
	   ((outstandingShares))
	   ((targetPrice))
	   ((marketCap))
	   ((dividendYield))
	   ((dividendPerShare))
	   ((bid))
	   ((ask))
	);

	scriptManager.engine().add(m) ;
	return scriptManager ;
}

PtrStringVector StockMetadata::getRequiredItems()
{
	
	PtrStringVector vec(new std::vector<std::string>()) ;

	vec->push_back(std::string("symbol"));
	vec->push_back(std::string("error"));
	vec->push_back(std::string("name"));
	vec->push_back(std::string("eps"));
	vec->push_back(std::string("epsEstimate"));
	vec->push_back(std::string("epsEstimateNextYr"));
	vec->push_back(std::string("ebitda"));
	vec->push_back(std::string("P/E_Ratio"));
	vec->push_back(std::string("PEG_Ratio"));
	vec->push_back(std::string("PS_Ratio"));
	vec->push_back(std::string("bookValue"));
	vec->push_back(std::string("outstandingShares"));
	vec->push_back(std::string("targetPrice"));
	vec->push_back(std::string("marketCap"));
	vec->push_back(std::string("dividendYield"));
	vec->push_back(std::string("dividendPerShare"));
	vec->push_back(std::string("bid"));
	vec->push_back(std::string("ask"));
	return vec;
}

StockMetadata::StockMetadata(void)
{
	_symbol = "" ;
	_name = "" ;
	_eps = 0.0;
	_epsEstimate = 0.0 ;
	_epsEstimateNextYr = 0.0;
	_ebitda = 0.0 ;
	_pe_ratio = 0.0;
	_peg_ratio = 0.0;
	_ps_ratio = 0.0;
	_bookValue = 0.0;
	_outstandingShares = 0.0; 
	_targetPrice = 0.0; 
	_marketCap = 0.0; 
	_bid = 0.0;
	_ask = 0.0;
}

StockMetadata::StockMetadata(std::string& s , PtrStringVector& data)
{
	_symbol = s ;

	//Index 1 is error indicator

	int start = 2 ;
	_name = data->at(start++);
	_eps = parseValAt(data , start++);
	_epsEstimate = parseValAt(data , start++);
	_epsEstimateNextYr = parseValAt(data , start++);
	_ebitda = parseValAt(data , start++); 
	_pe_ratio = parseValAt(data , start++);
	_peg_ratio = parseValAt(data , start++);
	_ps_ratio = parseValAt(data , start++);
	_bookValue = parseValAt(data , start++);
	_outstandingShares = 0.0; parseValAt(data , start++);
	_targetPrice = parseValAt(data , start++); 
	_marketCap = parseValAt(data , start++);
	_dividendYield = parseValAt(data , start++);
	_dividendPerShare = parseValAt(data , start++);
	_dividendPerShare = parseValAt(data , start++);
	_dividendPerShare = parseValAt(data , 16);
}

BIGDECIMAL StockMetadata::parseValAt(PtrStringVector& data , int i)
{
	if(i < data->size())
	{
		std::string& str = data->at(i);
		if(str.length() > 0 )
		{
			try
			{
				return boost::lexical_cast<BIGDECIMAL>(str);
			}
			catch(boost::bad_lexical_cast& )
			{
				return ERROR_VAL ;
			}
		}
	}

	return ERROR_VAL ;
}


StockMetadata::~StockMetadata(void)
{
}




const std::string& StockMetadata::symbol(){return _symbol;}
const std::string& StockMetadata::name(){return _name;}
BIGDECIMAL StockMetadata::eps(){return _eps;}
BIGDECIMAL StockMetadata::epsEstimate(){return _epsEstimate;}
BIGDECIMAL StockMetadata::epsEstimateNextYr(){return _epsEstimateNextYr;}
BIGDECIMAL StockMetadata::ebitda(){return _ebitda;}
BIGDECIMAL StockMetadata::pe_ratio(){return _pe_ratio;}
BIGDECIMAL StockMetadata::ps_ratio(){return _ps_ratio;}
BIGDECIMAL StockMetadata::peg_ratio(){return _peg_ratio;}
BIGDECIMAL StockMetadata::bookValue(){return _bookValue;}
BIGDECIMAL StockMetadata::outstandingShares(){return _outstandingShares;}
BIGDECIMAL StockMetadata::targetPrice(){return _targetPrice;} 
BIGDECIMAL StockMetadata::marketCap(){return _marketCap;} 
BIGDECIMAL StockMetadata::dividendYield(){return _dividendYield;}  
BIGDECIMAL StockMetadata::dividendPerShare(){return _dividendPerShare;} 
BIGDECIMAL StockMetadata::bid(){return _bid;}
BIGDECIMAL StockMetadata::ask(){return _ask;}