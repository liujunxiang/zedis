/*
 * Acceptor.cpp
 *
 *  Created on: Aug 7, 2017
 *      Author: root
 */

#include "AbstractEventHandle.h"
#include "Acceptor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <string>
#include "Global.h"
#include "RedisConnectPool.h"
BEGIN_NAMESPACE

class RequestHandler : public AbstractEventHandle
{
public:

    RequestHandler(SOCKET_T handle) :
    	AbstractEventHandle(),\
        m_handle(handle)
    {}

    virtual SOCKET_T GetHandle()
    {
        return m_handle;
    }

    virtual void HandleWrite()
    {
    }

    virtual void HandleRead()
    {
        char g_read_buffer[1024]={0} ;

        int len = recv(m_handle, g_read_buffer, sizeof(g_read_buffer ), 0);
        if (len > 0)
        {
            #if 1
                //printf("read buf:%s" , g_read_buffer ) ; 
                
                char response[MAX_ARRAY_SIZE]={0} ; 
				CONNECTPOOL::ConnectPool::Instance()->ExcuteCommand( g_read_buffer ,response ) ;
                write(m_handle , response  ,strlen(response)) ;
            #endif 
                REACTOR_MANAGER_INSTANCE.RegistEvent(this, e_READEVENT);

        }
        else
        {
            //perror("recv");
        }
    }

    virtual void HandleError()
    {
        fprintf(stderr, "client %d closed\n", m_handle);
        close(m_handle);
        REACTOR_MANAGER_INSTANCE.RemoveEvent(this);
        delete this;
    }

private:
    SOCKET_T m_handle;
};


Acceptor::Acceptor( const char *ip ,unsigned int port ):AbstractEventHandle()\
		,m_ip( ip)\
,m_port( port )
{
    m_handle = socket(AF_INET, SOCK_STREAM, 0);
    if (!m_handle < 0)
    {
    	std::cout << __FILE__ << ":" << __LINE__ << std::endl;
        perror("socket");
    }
    int opt = SO_REUSEADDR;
    setsockopt(m_handle, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(m_port);
    addr.sin_addr.s_addr = inet_addr(m_ip.c_str());
    if (bind(m_handle, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
    	std::cout << __FILE__ << ":" << __LINE__ << std::endl;
    	perror("bind");
    }

    if (listen(m_handle, 10) < 0)
    {
    	std::cout << __FILE__ << ":" << __LINE__ << std::endl;
    	perror("listen");
    }
}
Acceptor::~Acceptor()
{
	close(m_handle) ;
}
SOCKET_T Acceptor::GetHandle()
{
	return m_handle ;
}
void Acceptor::HandleRead()
{
    struct sockaddr addr;
    socklen_t addrlen = sizeof(addr);

    SOCKET_T handle = accept(m_handle, &addr, &addrlen);
    ///std::cout << __FILE__ << ":" << __LINE__ << std::endl;
    if (handle < 0 )
    {
        perror("accept");
        std::cout << __FILE__ << ":" << __LINE__ << std::endl;
    }
    else
    {
    	AbstractEventHandle * handler = new RequestHandler(handle);
    	///std::cout << __FILE__ << ":" << __LINE__ << std::endl;
        if (REACTOR_MANAGER_INSTANCE.RegistEvent(handler, e_READEVENT) != 0)
        {
            perror("error: register handler failed\n");
            delete handler;
        }

    }
}
void Acceptor::HandleWrite()
{
}
void Acceptor::HandleError()
{

}
END_NAMESPACE
