/*
 * EventDemultiplexer.h
 *
 *  Created on: Aug 8, 2017
 *      Author: root
 */

#ifndef EVENTDEMULTIPLEXER_H_
#define EVENTDEMULTIPLEXER_H_
#include "NameSpace.h"
#include "Macro.h"
BEGIN_NAMESPACE
class AbstractEventHandle ;
class EventDemultiplexer
{
public:

    virtual ~EventDemultiplexer() {}

    virtual int WaitEvents(std::map<SOCKET_T, AbstractEventHandle *> * handlers,
                           int timeout = 0) = 0;

    virtual int RequestEvent(SOCKET_T handle, Event evt) = 0;

    virtual int UnrequestEvent(SOCKET_T handle) = 0;
};
END_NAMESPACE
#endif /* EVENTDEMULTIPLEXER_H_ */
