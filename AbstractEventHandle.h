/*
 * AbstractEventHandle.h
 *
 *  Created on: Aug 7, 2017
 *      Author: root
 */

#ifndef ABSTRACTEVENTHANDLE_H_
#define ABSTRACTEVENTHANDLE_H_
#include "NameSpace.h"
#include "Macro.h"
BEGIN_NAMESPACE
class AbstractEventHandle
{
public:
    virtual SOCKET_T GetHandle() =0;
    virtual void HandleRead() =0 ;
    virtual void HandleWrite() =0;
    virtual void HandleError() =0;
public:
    AbstractEventHandle() ;
    virtual ~AbstractEventHandle() ;
} ;

END_NAMESPACE

#endif /* ABSTRACTEVENTHANDLE_H_ */
