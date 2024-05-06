/*  NAME:
        CSC450Lib.h

    DESCRIPTION:
        CSC450Lib public header.

    COPYRIGHT:
        (c) 2019, URI CSC450 Development Group
                       University of Rhode Island.

        Licensed under the Academic Free License - v. 3.0
        For more information see http://opensource.org/licenses/academic.php
*/
#ifndef CSC450LIB_H
#define CSC450LIB_H

namespace csc450lib
{
#if 0
//----------------------------------------
#pragma mark Currently not supported
//----------------------------------------
#endif

// temporary hack
#define	CSC450LIB_USE_SOURCE		1
#define	CSC450LIB_BUILD_LIBRARY		0

#if 0
//----------------------------------------
#pragma mark Reset some constants
//----------------------------------------
#endif

    //--------------------------------------------------------------------------------
    //  Undefine all CSC450LIB symbols that could have been defined by error or improperly
    //  in a precompiled header file
    //--------------------------------------------------------------------------------

    //  OS
    #ifdef CSC450LIB_OS_WIN32
        #undef CSC450LIB_OS_WIN32
    #endif
    #ifdef CSC450LIB_OS_MACOS
        #undef CSC450LIB_OS_MACOS
    #endif
    #ifdef CSC450LIB_OS_UNIX
        #undef CSC450LIB_OS_UNIX
    #endif

    //  Compiler/IDE
    #ifdef CSC450LIB_VISUAL
        #undef CSC450LIB_VISUAL
    #endif
    #ifdef CSC450LIB_MINGW
        #undef CSC450LIB_MINGW
    #endif
    #ifdef CSC450LIB_CYGWIN
        #undef CSC450LIB_CYGWIN
    #endif
    #ifdef CSC450LIB_XCODE
        #undef CSC450LIB_XCODE
    #endif
    
    //  Are we running on PPC or Intel? [should be obsolete by now]
	#undef CSC450LIB_SMALL_ENDIAN
	#undef CSC450LIB_BIG_ENDIAN
    #ifdef __LITTLE_ENDIAN__
        #define CSC450LIB_SMALL_ENDIAN		1
        #define CSC450LIB_BIG_ENDIAN		0
    #else
        #define CSC450LIB_SMALL_ENDIAN		0
        #define CSC450LIB_BIG_ENDIAN		1
    #endif

    //----------------------------------------------------------------------------------------
    //	This section is only useful for development environments that support multiple
    //	"targets" or modes for a given project.  Here, we use this functionality to build the
    //	code of a test application either against the source of the library (while developing
    //	and debugging a new class) or against the built library.
	//	CSC450LIB_USE_SOURCE and CSC450LIB_USE_LIBRARY are mutually exclusive and one must be set
	//	If building against the source,
	//		CSC450LIB_BUILD_LIBRARY must be set to 1 to build the library.
	//									set to 0 (default) to build a demo against source
	//
    //      - build the library  --------------------------------> CSC450LIB_USE_SOURCE = 1
	//															   CSC450LIB_BUILD_LIBRARY = 1
    //      - build a demo against the source of the library ----> CSC450LIB_USE_SOURCE = 1
	//															   [CSC450LIB_BUILD_LIBRARY = 0]
    //      - build a demo against a binary of the library ------> CSC450LIB_USE_LIBRARY = 1
	//															   [CSC450LIB_USE_SOURCE = 0]
    //----------------------------------------------------------------------------------------

	// Verify that only one of CSC450LIB_USE_SOURCE and CSC450LIB_USE_LIBRARY is set
    #if CSC450LIB_USE_SOURCE && CSC450LIB_USE_LIBRARY
		#error conflicting build modes: against source or library?
	#elif !(CSC450LIB_USE_SOURCE || CSC450LIB_USE_LIBRARY)
		#error undefined build mode: against source or lib?
	#endif

	//	CSC450LIB_BUILD_LIBRARY can only be defined in CSC450LIB_USE_SOURCE mode
	#if CSC450LIB_USE_LIBRARY && CSC450LIB_BUILD_LIBRARY
		#error cannot use and build the library in the same target
	#endif
	
	
	#if 0
	//----------------------------------------
	#pragma mark Build against the source
	//----------------------------------------
	#endif
    //------------------------------------------------------------------------------
    //  In use source mode, we expect the user to define some environment
	//	variables
    //------------------------------------------------------------------------------
	#if	CSC450LIB_USE_SOURCE

		//	nothing specific to do at this point
	
	#if 0
	//----------------------------------------
	#pragma mark Build against the library
	//----------------------------------------
	#endif

    //------------------------------------------------------------------------------
    //  In library use mode, all the relavant settings were defined when the
	//	libvrary was built
    //------------------------------------------------------------------------------
	#else	//	CSC450LIB_USE_LIBRARY
	
		//	nothing specific to do at this point

    #endif
    
	
	#if 0
	//----------------------------------------
	#pragma mark Determine the platform
	//----------------------------------------
	#endif

    //  Windows platform
    #if (defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__MINGW64__))

        #define CSC450LIB_OS_WIN32                          1
        #define CSC450LIB_OS_MACOS                          0
        #define CSC450LIB_OS_UNIX                           0
      
        #if (defined(_MSC_VER))
            #define CSC450LIB_VISUAL                        1
            #define CSC450LIB_MINGW                       0
            #define CSC450LIB_MINGW64                       0
            #define CSC450LIB_CYGWIN                        0
            #define CSC450LIB_XCODE                         0
            #define CSC450LIB_GCC_MAKE                      0
        
        #elif (defined(__MINGW32__))
            #define CSC450LIB_VISUAL                        0
            #define CSC450LIB_MINGW                       1
            #define CSC450LIB_MINGW64                       0
            #define CSC450LIB_CYGWIN                        0
            #define CSC450LIB_XCODE                         0
            #define CSC450LIB_GCC_MAKE                      0

        #elif (defined(__MINGW64__))
            #define CSC450LIB_VISUAL                        0
            #define CSC450LIB_MINGW                       0
            #define CSC450LIB_MINGW64                       1
            #define CSC450LIB_CYGWIN                        0
            #define CSC450LIB_XCODE                         0
            #define CSC450LIB_GCC_MAKE                      0

        #elif (defined(__CYGWIN__))
            #define CSC450LIB_VISUAL                        0
            #define CSC450LIB_MINGW                       0
            #define CSC450LIB_MINGW64                       0
            #define CSC450LIB_CYGWIN                        1
            #define CSC450LIB_XCODE                         0
            #define CSC450LIB_GCC_MAKE                      0
        #endif
   
    // Mac OS platform
    #elif (defined(__dest_os) && (__dest_os == __mac_os )) || \
          ((defined(__GNUC__) && (defined(__APPLE_CPP__) || defined(__APPLE_CC__))))
        #define CSC450LIB_OS_MACOS                          1
        #define CSC450LIB_OS_WIN32                          0
        #define CSC450LIB_OS_UNIX                           0

        #if ((defined(__GNUC__) && (defined(__APPLE_CPP__) || defined(__APPLE_CC__))))
            #define CSC450LIB_VISUAL                        0
            #define CSC450LIB_MINGW                       0
            #define CSC450LIB_MINGW64                       0
            #define CSC450LIB_CYGWIN                        0
            #define CSC450LIB_XCODE                         1
            #define CSC450LIB_GCC_MAKE                      0
        #endif

    // Unix
    #elif (defined(__FreeBSD__) || defined(linux) || defined(sgi) || defined(__NetBSD__) \
                              || defined(__OpenBSD) || defined(__QNX__) || defined(__GNUC__))

        #define CSC450LIB_OS_UNIX                           1
        #define CSC450LIB_OS_WIN32                          0
        #define CSC450LIB_OS_MACOS                          0

        #define CSC450LIB_VISUAL                            0
        #define CSC450LIB_MINGW64                           0
        #define CSC450LIB_MINGW                           	0
        #define CSC450LIB_CYGWIN                            0
        #define CSC450LIB_XCODE                             0
        #define CSC450LIB_GCC_MAKE                          1

    #endif

    //=============================================================================
    //      Platform selection verification
    //-----------------------------------------------------------------------------
    #if ! (CSC450LIB_OS_MACOS || CSC450LIB_OS_WIN32  || CSC450LIB_OS_UNIX)
        #error Target OS not detected!
    #endif

    #if (   (CSC450LIB_OS_MACOS && (CSC450LIB_OS_WIN32 || CSC450LIB_OS_UNIX)) || \
            (CSC450LIB_OS_WIN32 && (CSC450LIB_OS_MACOS || CSC450LIB_OS_UNIX)) || \
            (CSC450LIB_OS_UNIX  && (CSC450LIB_OS_MACOS || CSC450LIB_OS_WIN32)) )
        #error More than one target OS has been selected!
    #endif

    #if !( CSC450LIB_VISUAL || CSC450LIB_MINGW || CSC450LIB_CYGWIN || \
           CSC450LIB_XCODE || CSC450LIB_GCC_MAKE )
        #error Compiler not detected!
    #endif

    #if (  (CSC450LIB_VISUAL && \
    			(CSC450LIB_MINGW || CSC450LIB_CYGWIN || CSC450LIB_XCODE ||CSC450LIB_GCC_MAKE)) || \
           (CSC450LIB_MINGW && \
           		(CSC450LIB_VISUAL || CSC450LIB_CYGWIN || CSC450LIB_XCODE ||CSC450LIB_GCC_MAKE)) || \
           (CSC450LIB_CYGWIN && \
           		(CSC450LIB_MINGW || CSC450LIB_VISUAL || CSC450LIB_XCODE ||CSC450LIB_GCC_MAKE)) || \
           (CSC450LIB_XCODE && \
           		(CSC450LIB_MINGW || CSC450LIB_CYGWIN || CSC450LIB_VISUAL ||CSC450LIB_GCC_MAKE)) || \
           (CSC450LIB_GCC_MAKE && \
           		(CSC450LIB_MINGW || CSC450LIB_CYGWIN || CSC450LIB_XCODE ||CSC450LIB_VISUAL)) )
        #error More than one compiler/IDE has ben selected!
    #endif
}


#if 0
//----------------------------------------
#pragma mark MacOS-specific
//----------------------------------------
#endif

#if (CSC450LIB_OS_MACOS)

	#include <cmath>

	//	Developing on Xcode
    #if CSC450LIB_XCODE

    //  Other than Xcode?
    #else

    #endif

	//	This is an old trace of the original Mac OS (pre-OSX).
	//	By now this should be completely unnecessary.  I just keep it in
	//	in for sentimental reasons. :-)
    #ifndef PASCAL_RTN
    	#define PASCAL_RTN			pascal
    #endif

	#define CSC450LIB_EXPORT

#endif // CSC450LIB_OS_MACOS

#if 0
//----------------------------------------
#pragma mark Windows-specific
//----------------------------------------
#endif


#if CSC450LIB_OS_WIN32

    #define CSC450LIB_SMALL_ENDIAN			1
    #define CSC450LIB_BIG_ENDIAN			0

    // Includes for VC++ (Win CW builds should use the Win32Headers prefix)
    #if CSC450LIB_VISUAL
        #include <Windows.h>
		#include <float.h> // to get FLT_MAX amongst many things
        #include <cmath>

        #pragma warning(disable:4068)       // ignore unknown pragmas
        //#pragma warning(disable:4244)       // ignore conversion from "long" to "int", possible loss of data
        //#pragma warning(disable:4267)		// ignore conversion from "size_t" to "int", possible loss of data
        #pragma warning(disable:4761)       // ignore integral size mismatch in argument: conversion supplied
        #pragma warning(disable:4129)       // ignore 'p': unrecognized character escape sequence
        #pragma warning(disable:4229)       // ignore anachronism used: modifiers on data are ignored
        #pragma warning(disable:4996)       // ignore the deprecated functions for visual (qualified as unsafe by the compiler)
        #pragma warning(disable:4800)		// ignore the forced boolean conversion ("true" or "false")
        #pragma warning(disable:4251)       // ignore dll interface warning
        #pragma warning(disable:4275)       // ignore dll interface warning

        #ifndef round
            #define round(x) (x<0?ceil((x)-0.5):floor((x)+0.5))
        #endif

		#ifndef roundf
			#define roundf(value) round(value)
        #endif

	// CSC450LIB_MINGW still relies on the Windows SDK so it shares many similarities
	// to the CSC450LIB_VISUAL macro; however, pragma warnings are handled differently.
	#elif CSC450LIB_MINGW

		#include <Windows.h>
        #include <cmath>
		
		//	ConditionalMacros.h for some reason defines TYPE_LONGLONG 1 and so causes the
		//	Math64.h file to use the i64 MSVC-only post-fix on their macros.  This ensures
		//	that it instead uses LL for i64 and ULL for ui64.
		#ifdef TYPE_LONGLONG
			#undef TYPE_LONGLONG
			#define TYPE_LONGLONG	0
		#endif


    #elif CSC450LIB_CYGWIN

        #include <cmath>

    #endif

    #ifdef PASCAL_RTN
        #undef PASCAL_RTN
    #endif


	#if CSC450LIB_BUILD_LIBRARY
	#   define CSC450LIB_EXPORT   __declspec(dllexport)
	# else
	#   if CSC450LIB_USE_SOURCE
	#       define CSC450LIB_EXPORT
	#   else
	#       define CSC450LIB_EXPORT   __declspec(dllimport)
	#   endif
	#endif

#endif  //  CSC450LIB_OS_WIN32




#if 0
//----------------------------------------
#pragma mark Linux & Unix-specific
//----------------------------------------
#endif
#if CSC450LIB_OS_UNIX

    #define CSC450LIB_EXPORT

    #include <cmath>


#endif  //  CSC450LIB_OS_UNIX



#if 0
//-----------------------------------------------------
#pragma mark Common macros, functions, and data types
//-----------------------------------------------------
#endif

namespace csc450lib
{
	#ifndef PI_F
		#define		PI_F				3.1415926f
	#endif
		
	//	generally used for normalization tests
	#define	STD_RELATIVE_TOLERANCE		1E-06f
	#define	LARGE_RELATIVE_TOLERANCE	1E-04f

}

#endif  //  CSC450LIB_H
