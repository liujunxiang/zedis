/*
 * Epoll_Demultiplexer.cpp
 *
 *  Created on: Aug 7, 2017
 *      Author: root
 */

#include "Epoll_Demultiplexer.h"
#include <vector>
#include <sys/epoll.h>
#include <iostream>
#include <errno.h>
#include <unistd.h>
#include "AbstractEventHandle.h"
BEGIN_NAMESPACE
Epoll_Demultiplexer::Epoll_Demultiplexer()
{
    m_epoll_fd = ::epoll_create(FD_SETSIZE);
    m_fd_num = 0;
}

Epoll_Demultiplexer::~Epoll_Demultiplexer()
{
    ::close(m_epoll_fd);
}

int Epoll_Demultiplexer::WaitEvents(std::map<SOCKET_T, AbstractEventHandle *> * handlers, int timeout)
{
    std::vector<epoll_event> ep_evts(m_fd_num);
    int num = epoll_wait(m_epoll_fd, &ep_evts[0], ep_evts.size(), timeout);
    if (num > 0)
    {
        for (int idx = 0; idx < num; ++idx)
        {
        	SOCKET_T handle = ep_evts[idx].data.fd;
            if ((ep_evts[idx].events & EPOLLERR) ||
                    (ep_evts[idx].events & EPOLLHUP))
            {
                (*handlers)[handle]->HandleError();
            }
            else
            {
                if (ep_evts[idx].events & EPOLLIN)
                {
                    (*handlers)[handle]->HandleRead();
                }
                if (ep_evts[idx].events & EPOLLOUT)
                {
                    (*handlers)[handle]->HandleWrite();
                }
            }
        }
    }

    return num;
}

int Epoll_Demultiplexer::RequestEvent(SOCKET_T handle, Event evt)
{
    epoll_event ep_evt;
    ep_evt.data.fd = handle;
    ep_evt.events = 0;

    if (evt & e_READEVENT)
    {
        ep_evt.events |= EPOLLIN;
    }
    if (evt & e_WRITEEVENT)
    {
        ep_evt.events |= EPOLLOUT;
    }
    ep_evt.events |= EPOLLONESHOT;

    if (epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, handle, &ep_evt) != 0)
    {
        if (errno == ENOENT)
        {
            if (epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, handle, &ep_evt) != 0)
            {
                return -errno;
            }
            ++m_fd_num;
        }
    }
    return 0;
}


int Epoll_Demultiplexer::UnrequestEvent(SOCKET_T handle)
{
    epoll_event ep_evt;
    if (epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, handle, &ep_evt) != 0)
    {
        return -errno;
    }
    --m_fd_num;
    return 0;
}
END_NAMESPACE

