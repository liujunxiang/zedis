/*
 * ReactorImp.cpp
 *
 *  Created on: Aug 7, 2017
 *      Author: root
 */
#include "ReactorImp.h"
#include "Epoll_Demultiplexer.h"
#include "AbstractEventHandle.h"
BEGIN_NAMESPACE


ReactorImp::ReactorImp()
{
    m_demultiplexer = new Epoll_Demultiplexer();
}

ReactorImp::~ReactorImp()
{
    delete m_demultiplexer;
}

int ReactorImp::RegistEvent(AbstractEventHandle * handler  ,Event e)
{
    SOCKET_T handle = handler->GetHandle();
    std::map<SOCKET_T, AbstractEventHandle *>::iterator it = m_handlers.find(handle);
    if (it == m_handlers.end())
    {
        m_handlers[handle] = handler;
    }
    return m_demultiplexer->RequestEvent(handle, e);
}

int ReactorImp::RemoveEvent(AbstractEventHandle * handler)
{
	SOCKET_T handle = handler->GetHandle();
    m_handlers.erase(handle);
    return m_demultiplexer->UnrequestEvent(handle);
}

void ReactorImp::HandleEvent()
{
    m_demultiplexer->WaitEvents(&m_handlers, -1);
}



END_NAMESPACE
