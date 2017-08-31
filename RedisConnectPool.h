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
            printf(DEBUG_FORMAT" %s:%d connect failed ,error[%s]!!!\n" , DEBUG_VALIST  ,this->ip , this->port   , c->errstr  ) ; 
        }
    }
    ~__node__()
    {
        if( status)
        {
            #if DEBUG
                printf(DEBUG_FORMAT" %s:%d recyle!!!\n" , DEBUG_VALIST  ,this->ip , this->port  ) ;
            #endif 
            redisFree( c ) ; 
        }
    }
    int set( char * command ) 
    {
         #if DEBUG
            printf(DEBUG_FORMAT" %s:%d command[%s]!!!\n" , DEBUG_VALIST  ,this->ip , this->port , command   ) ;
         #endif 
        redisReply* r = (redisReply*)redisCommand(c, command); 
        if(!r)
        {
            return -1 ; 
        }
        freeReplyObject(r); 
        return 0;
    }
    
    int get( char * command  ,char *response ) 
    {
         #if DEBUG
            printf(DEBUG_FORMAT" %s:%d command[%s]!!!\n" , DEBUG_VALIST  ,this->ip , this->port , command   ) ;
         #endif 
        redisReply* r = (redisReply*)redisCommand(c, command); 
        if ( r->type == REDIS_REPLY_NIL)
        {
            strcpy(response ,  "$-1\r\n") ; 
        }
        else
        {
            sprintf(response , "$%d\r\n%s\r\n" , (int)strlen( r->str ) ,  r->str ) ; 
        }
        freeReplyObject(r); 
        return 0;
    }
    
    
    void info( char * p )
    {
        
        if( status )
        {
            redisReply* r = (redisReply*)redisCommand(c, "info");
            strcpy( p , r->str ) ; 
            freeReplyObject(r);  
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
        #if DEBUG
            printf(DEBUG_FORMAT" groupid[%d] created!!!with detail{[master=%s:%d] [slave:%s,%d]}\n" , \
            DEBUG_VALIST ,this->id\
            ,this->master->ip \
            ,this->master->port \
            ,this->slave->ip \
            ,this->slave->port) ; 
        #endif
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
    struct __node__*  active_node()
    {
        return ( this->master->status )?( this->master ):( this->slave) ; 
    }
}_node_group_ ,*p_node_group_;

typedef struct __list_node__
{
	p_node_group_ g ;
	struct __list_node__* next ;
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
    int ExcuteCommand( char * data , char * response , unsigned int(* HASH)(char * ) =NULL ) ;
private:
    int WakeUp(int msgid  ) ; 
    int set(  char * key , char * command  ,char *out) ; 
    int get(  char * key , char * command  ,char *out) ; 
    void info( char *out ) ; 
private:
	p__list_node__ m_p ; 
	int _size ; 
};
}

END_NAMESPACE


#endif /* REDISCONNECTPOOL_H_ */
