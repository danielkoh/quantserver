#pragma once

#include <map>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "StockMetadata.h"

namespace quantserver
{
	typedef boost::shared_ptr<StockMetadata> ptr_stockMetaData;
	typedef std::vector<ptr_stockMetaData> vec_metadata_ptr ;
	typedef boost::shared_ptr<vec_metadata_ptr> ptr_stockMetaDataPtrCollection;

	class AdditionalInformation
	{
	protected:
		std::map<std::string , std::string> yahooDataQueryElements;
		std::string constructYahooMetadataUrl(std::vector<std::string>& symbols);
		bool isError(PtrStringVector& data);

	public:
		AdditionalInformation(void);
		~AdditionalInformation(void);

		ptr_stockMetaDataPtrCollection getStockMetaData(std::vector<std::string>& symbols); 
	};
}

