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

#endif /* MACRO_H_ */
