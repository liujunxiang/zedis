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
    CONNECTPOOL::ConnectPool *pool=new CONNECTPOOL::ConnectPool() ; 
	Acceptor oAcceptor( "127.0.0.1" ,3456 ) ;

    while (1)
    {
    	REACTOR_MANAGER_INSTANCE.RegistEvent(&oAcceptor, e_READEVENT);
    	REACTOR_MANAGER_INSTANCE.HandleEvent();
    }
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
