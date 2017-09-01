/*
 * Acceptor.h
 *
 *  Created on: Aug 8, 2017
 *      Author: root
 */

#ifndef ACCEPTOR_H_
#define ACCEPTOR_H_
#include "NameSpace.h"
#include "Macro.h"
#include "AbstractEventHandle.h"
BEGIN_NAMESPACE
class EXPORT Acceptor:public AbstractEventHandle{
private:
    SOCKET_T     m_handle;
    std::string           m_ip;
    unsigned short        m_port;
public:
    explicit Acceptor( const char * ip , unsigned int port ) ;
    virtual ~Acceptor( ) ;
public:
     SOCKET_T GetHandle()  ;
     void HandleRead() ;
     void HandleWrite() ;
     void HandleError() ;
};


END_NAMESPACE
#endif /* ACCEPTOR_H_ */
