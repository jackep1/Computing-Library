/*  NAME:
        CSC450Exception.cpp

    DESCRIPTION:
        implementation of the CSC450Lib CSC450Exception class

    COPYRIGHT:
        (c) 2003-2018, 3D Group for Interactive Visualization
                       University of Rhode Island.

        Licensed under the Academic Free License - v. 3.0
        For more information see http://opensource.org/licenses/academic.php
*/

#include <iostream>
#include <cstring>
#include <cstdlib>
//
#include "CSC450Exception.h"

using namespace std;
using namespace csc450lib;


CSC450Exception::CSC450Exception(ErrorCode theCode, const string& theMessage)
	:	code_(theCode),
        message_(theMessage)
{
}

CSC450Exception::CSC450Exception(CSC450Exception&& err)
	:	code_(err.code_),
		message_(err.message_)
{
	err.code_ = ErrorCode::NO_450_ERROR;
	err.message_ = "";
}

ErrorCode CSC450Exception::getCode(void) const
{
    return code_;
}

const string& CSC450Exception::getMessage(void) const
{
    return message_;
}


void CSC450Exception::appendToMessage(const string& addMsg) 
{
	message_ = message_ + "\r\t" + addMsg;
}
