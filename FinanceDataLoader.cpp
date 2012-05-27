#include "FinanceDataLoader.h"
#include <boost/network/protocol/http/client.hpp>
#include <boost/functional/hash.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <fstream>


using namespace boost::network;
using namespace boost::network::http;
using namespace quantserver;


#define LOCAL_FILE_LOCATION "C:\\workspaces\\cppFinance\\localfiles\\"
#define YAHOOFINURL "http://ichart.finance.yahoo.com/table.csv?s=" 

using boost::asio::ip::tcp;

FinanceDataLoader::FinanceDataLoader(std::string& fileLocation , bool isRemote)
{
	isRemoteRead = isRemote ;

	if(isRemoteRead)
	{
		remoteUrl = fileLocation;
		localUrl = std::string(LOCAL_FILE_LOCATION);
		boost::hash<std::string> string_hash;
		
		//Hash localUrl to "hash_<somehash>.csv"
		localUrl += "hash_";
		localUrl += boost::lexical_cast< std::string >( string_hash(remoteUrl) );
		localUrl += ".csv";

	}
	else
	{
		localUrl = fileLocation;
	}
}


FinanceDataLoader::~FinanceDataLoader(void)
{
}

std::string FinanceDataLoader::getYahooHistoricalDataUrl(const std::string& symbol)
{
	std::string url(YAHOOFINURL);
	url.append(symbol);
	return url;
}

std::string& FinanceDataLoader::getLocalReadable()
{
	if(isRemoteRead)
	{
		downloadRemote(remoteUrl);
	}
	return localUrl;
}

bool FinanceDataLoader::downloadRemote(const std::string& url)
{
	try {
		http::client client;
		http::client::request request(url);
		request << header("Connection", "close");
		http::client::response response = client.get(request);

		std::cout << "Saving file to " << localUrl << std::endl;

		std::ofstream localFile;
		localFile.open (localUrl);
	
		//Open local file URL to start writing to it
		localFile << static_cast<std::string>(body(response)) ;

		//Close local file
		localFile.flush();
		localFile.close();
	}
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
	
	//Everything happened successfully
	return true;
}
