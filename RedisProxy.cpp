//============================================================================
// Name        : RedisProxy.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Reactor.h"
#include "ReactorImp.h"
#include "Epoll_Demultiplexer.h"
#include "AbstractEventHandle.h"
#include "RedisConnectPool.h"
#include "AutoPtr.h"
#include "NetWorking.h"
#include "Acceptor.h"
#include "Global.h"
#include <error.h>
#include <errno.h>
#include <stdio.h>

using namespace std;

int main() {
	printf("start service ,pid is %d\n" ,getpid() ) ; 
    CONNECTPOOL::ConnectPool *pool=CONNECTPOOL::ConnectPool::Instance() ;  
	CONNECTPOOL::config oconfig1( "127.0.0.1" ,7000 ) ;
	CONNECTPOOL::config oconfig2( "127.0.0.1" ,7001 ) ;
	CONNECTPOOL::config oconfig3( "127.0.0.1" ,7002 ) ;
	CONNECTPOOL::config oconfig4( "127.0.0.1" ,7003 ) ;
	pool->AddNode( &oconfig1 , 1  , &oconfig2) ; 
	pool->AddNode( &oconfig3 , 2  , &oconfig4) ; 
    #if 1
	Acceptor oAcceptor( "127.0.0.1" ,3456 ) ;
    while (1)
    {
    	REACTOR_MANAGER_INSTANCE.RegistEvent(&oAcceptor, e_READEVENT);
    	REACTOR_MANAGER_INSTANCE.HandleEvent();
    }
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	#endif
	return 0;
}
