#include "ControllerReturnType.h"

using namespace quantserver ;
ControllerReturnType::ControllerReturnType()
{
	code = STATUS_ERROR ;
	payload = "" ;
}

ControllerReturnType::ControllerReturnType(QS_STATUS_CODE _code , const std::string& _payload)
{
	code = _code ;
	payload = _payload ;
}


ControllerReturnType::~ControllerReturnType(void)
{
}
