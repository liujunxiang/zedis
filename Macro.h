/*
 * Macro.h
 *
 *  Created on: Aug 7, 2017
 *      Author: root
 */

#ifndef MACRO_H_
#define MACRO_H_
#define EXPORT
#define DLLEXPORT
#define Safe_del( __STR__ ) do{\
	if(__STR__  != NULL  )\
	{\
		delete __STR__ ; \
		__STR__ = NULL ; \
	}\
}while(0 ) ;
#define FILE_TRACER
#if defined(FILE_TRACER) 
    #define DEBUG_FORMAT "[FILE=%s] [LINE=%d]"
    #define DEBUG_VALIST __FILE__,__LINE__
#else
    #define DEBUG_FORMAT            
    #define DEBUG_VALIST 
#endif 

#define MAX_ARRAY_SIZE 65536
#define MIDDLE_ARRAY_SIZE 8192
#define MIN_ARRAY_SIZE 64
#endif /* MACRO_H_ */
