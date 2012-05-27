#pragma once

#include <string>

namespace quantserver
{
	class FinanceDataLoader
	{
	public:
		FinanceDataLoader(std::string& fileLocation , bool isRemote = false);
		virtual ~FinanceDataLoader(void);
		std::string& getLocalReadable();
		static std::string getYahooHistoricalDataUrl(const std::string& symbol);

	protected:
		std::string remoteUrl ;
		std::string localUrl ;
		bool isRemoteRead;
		bool downloadRemote(const std::string& url);
	};
}

