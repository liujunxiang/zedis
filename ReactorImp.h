/*
 * ReactorImp.h
 *
 *  Created on: Aug 7, 2017
 *      Author: root
 */

#ifndef REACTORIMP_H_
#define REACTORIMP_H_
#include "NameSpace.h"
#include "Macro.h"
#include <vector>
#include <map>
BEGIN_NAMESPACE
class EventDemultiplexer ;
class AbstractEventHandle ;
class ReactorImp
{
public:
	ReactorImp();
	virtual ~ReactorImp() ;
public:
	 int RegistEvent(AbstractEventHandle * p  ,Event e )  ;
	 int RemoveEvent(AbstractEventHandle * p )  ;
	 void  HandleEvent()   ;
protected :
	 EventDemultiplexer *                m_demultiplexer;
    std::map<SOCKET_T, AbstractEventHandle *>  m_handlers;
} ;
END_NAMESPACE
#endif /* REACTORIMP_H_ */
