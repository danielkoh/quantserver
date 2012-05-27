#include "HttpProcessServer.h"
#include <boost/network/uri/decode.hpp>

#include <iostream>
using namespace quantserver ;

ModelMapPtr parseQuery(server::request const &request) ;
std::string getQueryString(server::request const &request) ;
std::string getPath(server::request const &request) ;

void HttpProcessServer::start()
{
	try {
		HttpProcessServer processor ;
		server s("0.0.0.0" , "8000" , processor);
		s.run();
	}
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

HttpProcessServer::HttpProcessServer(void)
{
	dispatcher = Dispatcher() ;
}


HttpProcessServer::~HttpProcessServer(void)
{
}

void HttpProcessServer::operator() (server::request const &request, server::response &response)
{
	std::string ip = source(request);
	ModelMapPtr mapPtr = parseQuery(request) ;
	ModelMap& map = *mapPtr ;

	std::string app = getPath(request) ;
	
	std::cout << "Routing to (" << app << ") " << std::endl ;
	std::cout << "running (" << map["chai"] << ") " << std::endl ;
	
	ControllerReturnType r = dispatcher.dispatch(app , map) ;

	if(r.code == STATUS_OK )
	{
		response = server::response::stock_reply(
			server::response::ok, r.payload
		);
	}
	else
	{
		if(r.code == STATUS_BAD_REQUEST)
		{
			response = server::response::stock_reply(
				server::response::bad_request, r.payload
			);
		}
		else if(r.code == STATUS_NOT_FOUND)
		{
			response = server::response::stock_reply(
				server::response::not_found, r.payload
			);
		}
		else
		{
			response = server::response::stock_reply(
				server::response::internal_server_error, r.payload
			);
		}
	}


    /*response = server::response::stock_reply(
        server::response::ok, std::string("Hello, ") + ip + "!"
	);*/

}

void HttpProcessServer::log(const char* c_str)
{
}

std::string getPath(server::request const &request)
{
	int breaker = request.destination.find("?" , 0) ;

	if(breaker != std::string::npos )
	{
		return request.destination.substr(0 , breaker) ;
	}
	else
	{
		return request.destination ;
	}
}

ModelMapPtr parseQuery(server::request const &request)
{
	//Parse all the request & respose elements
	ModelMapPtr mapPtr = ModelMapPtr( new ModelMap()) ;
	ModelMap& map = *mapPtr ;
	std::string queryString = getQueryString(request) ;

	std::vector<std::string> strs;
	boost::split(strs, queryString, boost::is_any_of("&"));

	for(int i = 0 ; i < strs.size() ; i++ )
	{
		int eqPos = strs[i].find("=");

		if(eqPos != std::string::npos )
		{
			map[ strs[i].substr(0 , eqPos) ] = boost::network::uri::decoded(strs[i].substr(eqPos + 1 )) ;
		}
		else
		{
			map[ strs[i].substr(0 , eqPos) ] = "" ;
		}
	}

	return mapPtr ;
}

std::string getQueryString(server::request const &request)
{
	if( request.method == "GET" ) //HTTP POST, get by body
	{
		int breaker = request.destination.find("?" , 0) ;

		if(breaker != std::string::npos )
		{
			return request.destination.substr(breaker+1) ;
		}
		else
		{
			return "" ;
		}
	}
	else
	{
		return request.body;
	}
}
