#pragma once

#include <boost/network/protocol/http/server.hpp>
#include "Dispatcher.h"

namespace http = boost::network::http;


namespace quantserver
{
	class HttpProcessServer ;
	typedef http::server<HttpProcessServer> server;

	class HttpProcessServer
	{
	public:
		HttpProcessServer(void);
		virtual ~HttpProcessServer(void);

		void operator() (server::request const &request, server::response &response);
		void log(const char* c_str);
		static void start() ;

	protected:
		Dispatcher dispatcher ;
	};
}

