/*  NAME:
        CSC450Exception.h

    DESCRIPTION:
        CSC450Exception public header.

    COPYRIGHT:
        (c) 2019, URI CSC450 Development Group
                       University of Rhode Island.

        Licensed under the Academic Free License - v. 3.0
        For more information see http://opensource.org/licenses/academic.php
*/
#ifndef CSC450LIB_ERROR_REPORT_H
#define CSC450LIB_ERROR_REPORT_H

#include <string>
#include <cstdlib>
//
#ifdef  CSC450LIB_DEBUG_ASSERT
    #include <cassert>
#endif

#include "CSC450Lib.h"

namespace csc450lib
{
    /** List of all the error codes for the library
     */
    enum class ErrorCode
    {
		//	0-99 error codes for generic errors
		NO_450_ERROR = 0,
		//
		UNKNOWN_ERROR = 1,
		
		//	100-199 error codes for calculus-related exceptions
		FUNCTION_NOT_DEFINED_AT_EVALUATION_POINT = 100
	
		//	200-299 error codes for linear algebra-related exceptions
    };


    /** Implements the CSC450Exception class.
     *
     *  A CSC450Exception is a form of exception.  Instead of defining a class hierarchy for
	 *	exceptions in the library, we have chosen the path of having a single class with
	 *	an error code and an error string as instance variables.
     *
     *  @author   URI CSC450 Development Group, University of Rhode Island.

     */
    class CSC450LIB_EXPORT CSC450Exception
    {
        public:
		
			//	deleted constructors and operators
			CSC450Exception(void) = delete;
			CSC450Exception(const CSC450Exception& err) = delete;
			CSC450Exception& operator = (const CSC450Exception& obj) = delete;
			CSC450Exception& operator = (CSC450Exception&& obj) = delete;
		
			/**	Move constructor
			 *	@param	err		the object to move
			 */
			CSC450Exception(CSC450Exception&& err);

			/**	Creates a new ErrorCode object to throw.
			 *	@param	theCode		code identifying the type of error encountered
			 *	@param	theMessage	string with an error message
			 */
            CSC450Exception(ErrorCode theCode, const std::string& theMessage);
			
			/**	Destructor
			 */
            ~CSC450Exception(void) { }
            
			/**	Returns this object's error code
			 *	@return		this object's error code
			 */
            ErrorCode getCode(void ) const;
			
			
			/**	Appends a string to the error message
			 *	@param	addMsg the string to add to the message
			 */
			void appendToMessage(const std::string& addMsg);
			

            /** When you call this, you're responsible for delete[]'ing the 
             * returned pointer.
			 *	@return a const C-style error string with an error message
			 */
            const std::string&  getMessage(void) const;

			/**	Prints the full stack trace collected by this exception,
			 *	attempting to replicate the behavior of Java's Exception class.
			 */
			void printStackTrace(void) const;

        private:

			/**	Code identifying the type of error encountered
			 */
            ErrorCode   code_;
			
			/**	String giving the type of the error and its call sequence 
			 */
			std::string message_;
			
    };


	//	see __FILE__   __LINE__
    #if CSC450LIB_DEBUG_ASSERT
        #define FAIL_CONDITION(a, b, c) assert(!(a))
        #define REPORTS_EXCEPTIONS
    #else
        #define FAIL_CONDITION(a, b, c) if (a) throw CSC450Exception(b, c)
        #define REPORTS_EXCEPTIONS throw(CSC450Exception)
    #endif


}   //  namespace csc450lib

#endif  //  ERROR_REPORT_H
