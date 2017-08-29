/*
 * RedisConnectPool.h
 *
 *  Created on: Aug 8, 2017
 *      Author: root
 */

#ifndef REDISCONNECTPOOL_H_
#define REDISCONNECTPOOL_H_
#include "NameSpace.h"
#include "Macro.h"
#include "AbstractEventHandle.h"
#include <hiredis.h>
#include <string.h>
BEGIN_NAMESPACE
namespace CONNECTPOOL{

typedef struct __config
{
    char ip[16] ;
    unsigned int port ; 
	__config( const char * ip , unsigned int port  )
	{
		memset(this->ip,0x00 , sizeof( this->ip ) ) ;
		strcpy( this->ip , ip ) ;
		this->port = port ; 
        
	}
}__attribute__((packed)) config;

typedef struct __node__
{
	char ip[16] ;
	unsigned int port ;
	unsigned char status ;
	redisContext* c;
    __node__( const char *ip , unsigned int port  )
    {
        strcpy( this->ip , ip ) ; 
        this->port=port ; 
        status=1 ; 
        c=redisConnect(this->ip , port )  ; 
        if( c->err )
        {
            status=0 ;
			std::cout << __FILE__ << ":" << __func__ << ":" << c->errstr  << std::endl ; 
        }
    }
    ~__node__()
    {
        if( status)
        {
            redisFree( c ) ; 
        }
    }
}__attribute__((packed)) _node_ ,*p__node_;

typedef struct __node_group__
{
	struct __node__* master ;
	struct __node__* slave ;
    unsigned short id ; 
    __node_group__():master( NULL)\
    ,slave(NULL)\
    ,id(0)
    {
        
    }
    __node_group__(struct __node__* l ,struct __node__* r ,unsigned short _id ):master( l)\
    ,slave(r)\
    ,id(_id)
    {
        
    }  
    ~__node_group__()
    {
        if( master )
        {
            delete master ; 
        }
        if( slave)
        {
            delete slave ; 
        }
    }
    int set( const char * command )
    {
        struct __node__ *_p = (master->status)?(master):( (slave->status)?(slave):(NULL ) ) ;  
        return (redisCommand(_p->c, command) )?(0):(-1) ; 
    }
}_node_group_ ,*p_node_group_;

typedef struct __list_node__
{
	p_node_group_ g ;
	__list_node__* next ;
	__list_node__( p_node_group_   _p):g(_p),next(NULL){ }
    ~__list_node__()
    {
        if( g)
        {
            delete g ; 
        }
    }
}*p__list_node__;

class DLLEXPORT ConnectPool{
private:
	ConnectPool();
	~ConnectPool() ;
public:
    static ConnectPool* _instance ; 
public:
    static ConnectPool* Instance() ;
    static void Release() ; 
public:
	void AddNode(config* master , int groupid  , config* slave=NULL ) ;
	int size() const  ; 
    int ExcuteCommand( char * data , char ** response , unsigned int(* HASH)(char * ) =NULL ) ;
private:
    int WakeUp(int msgid  ) ; 
private:
	p__list_node__ m_p ; 
	int _size ; 
};
}

END_NAMESPACE


#endif /* REDISCONNECTPOOL_H_ */
