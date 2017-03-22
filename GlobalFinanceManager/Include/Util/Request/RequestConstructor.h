#ifndef __REQUEST_CONSTRUCTOR_H__
#define __REQUEST_CONSTRUCTOR_H__

#include "..\..\..\Include\Util\Request\Request.h"

class RequestConstructor
{
	static Request* ConstructRequest(const std::string& params_string);
};

#endif