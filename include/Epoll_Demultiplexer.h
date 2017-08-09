/*
 * Epll_Demultiplexer.h
 *
 *  Created on: Aug 7, 2017
 *      Author: root
 */

#ifndef EPLL_DEMULTIPLEXER_H_
#define EPLL_DEMULTIPLEXER_H_
#include "ReactorImp.h"
#include "NameSpace.h"
#include "Macro.h"
#include "EventDemultiplexer.h"
BEGIN_NAMESPACE
class AbstractEventHandle ;
class Epoll_Demultiplexer:public EventDemultiplexer
{
public:
	Epoll_Demultiplexer();
	~Epoll_Demultiplexer() ;
public:
    virtual int WaitEvents(std::map<SOCKET_T, AbstractEventHandle *> * handlers,                           int timeout = 0) ;

    virtual int RequestEvent(SOCKET_T handle, Event evt) ;

    virtual int UnrequestEvent(SOCKET_T handle) ;;
private:
    int  m_epoll_fd;
    int  m_fd_num;
} ;
END_NAMESPACE
#endif /* EPLL_DEMULTIPLEXER_H_ */
