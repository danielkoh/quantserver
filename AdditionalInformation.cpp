#include "AdditionalInformation.h"
#include "FinanceDataLoader.h"
#include "CSVParser.h"

using namespace quantserver;

AdditionalInformation::AdditionalInformation(void)
{
	yahooDataQueryElements.clear();

	yahooDataQueryElements["symbol"] = std::string("s") ;
	yahooDataQueryElements["name"] = std::string("n") ;
	yahooDataQueryElements["dividendYield"] = std::string("y") ;
	yahooDataQueryElements["dividendPerShare"] = std::string("d") ;
	yahooDataQueryElements["eps"] = std::string("e") ;
	yahooDataQueryElements["epsEstimate"] = std::string("e7") ;
	yahooDataQueryElements["epsEstimateNextYr"] = std::string("e8") ;
	yahooDataQueryElements["bookValue"] = std::string("b4") ;
	yahooDataQueryElements["marketCap"] = std::string("j1") ;
	yahooDataQueryElements["ebitda"] = std::string("j4") ;
	yahooDataQueryElements["P/E_Ratio"] = std::string("r") ;
	yahooDataQueryElements["targetPrice"] = std::string("t4") ;
	yahooDataQueryElements["outstandingShares"] = std::string("f6") ;
	yahooDataQueryElements["PEG_Ratio"] = std::string("r5") ;	
	yahooDataQueryElements["PS_Ratio"] = std::string("p5") ;	
	yahooDataQueryElements["bid"] = std::string("b2") ;	
	yahooDataQueryElements["ask"] = std::string("b3") ;	
	yahooDataQueryElements["error"] = std::string("e1") ;	
}


AdditionalInformation::~AdditionalInformation(void)
{
}

std::string AdditionalInformation::constructYahooMetadataUrl(std::vector<std::string>& symbols)
{
	std::string str("http://finance.yahoo.com/d/quotes.csv?s=");

	//http://finance.yahoo.com/d/quotes.csv?s=XOM+EK+JNJ+MSFT&f=snd1t1l1ohgvwdyr

	int i = 0 ;
	for(i = 0 ; i < symbols.size() ; i++ )
	{
		str.append(symbols[i]);

		if(i < symbols.size() -1 )
		{
			str.append(std::string("+"));
		}
	}
	str.append(std::string("&f="));
	PtrStringVector ptrStringVector = StockMetadata::getRequiredItems();
	for(int i = 0 ; i < ptrStringVector->size() ; i++ )
	{
		str.append(yahooDataQueryElements[
			ptrStringVector->at(i)
		]);
	}

	return str;
}

bool AdditionalInformation::isError(PtrStringVector& data)
{
	if(data->at(1).size() > 5)
	{
		return true;
	}
	else
	{
		return false;
	}
}

ptr_stockMetaDataPtrCollection AdditionalInformation::getStockMetaData(std::vector<std::string>& symbols)
{
	std::string url = constructYahooMetadataUrl(symbols);
	FinanceDataLoader dataLoader(url,true);
	std::string& localFile = dataLoader.getLocalReadable();

	CSVParser csvParser(localFile, 1 , false) ;
	ptr_stockMetaDataPtrCollection metaCollection( new vec_metadata_ptr() ) ;

	int s_read= 0 ;

	for( int i = 0 ; i < csvParser.getNumberOfLines() ; i++ )
	{
		PtrStringVector sv = csvParser.getDataAt(i) ;

		if(sv->size() > 1 )
		{
			std::string& readSymbol = sv->at(0);
			if(readSymbol == symbols[s_read] )
			{
				if(!isError(sv))
				{
					ptr_stockMetaData metaData( new StockMetadata(readSymbol , sv) ) ;
					metaCollection->push_back(metaData) ;
				}
				s_read++ ;
			}
		}
	}



	return metaCollection;
}
