#pragma once

#include <string>

namespace quantserver
{
	typedef enum QS_STATUS_CODE
	{
		STATUS_OK = 200 ,
		STATUS_BAD_REQUEST = 400 ,
		STATUS_NOT_FOUND = 404 ,
		STATUS_ERROR = 500

	} CONTROLLER_STATUS_CODE ;

	struct ControllerReturnType
	{
		ControllerReturnType();
		ControllerReturnType(QS_STATUS_CODE _code , const std::string& _payload);
		virtual ~ControllerReturnType(void);
		QS_STATUS_CODE code ;
		std::string payload ;
	};
}

