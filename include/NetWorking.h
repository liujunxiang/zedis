/*
 * NetWorking.h
 *
 *  Created on: Aug 7, 2017
 *      Author: root
 */

#ifndef NETWORKING_H_
#define NETWORKING_H_

#include "NameSpace.h"
#include "Macro.h"
BEGIN_NAMESPACE
class NetWorkingUtil
{
public:
	NetWorkingUtil() ;
	~NetWorkingUtil() ;
public:
	SOCKET_T Sock( const char * ip ,unsigned port  );
} ;
END_NAMESPACE
#endif /* NETWORKING_H_ */
