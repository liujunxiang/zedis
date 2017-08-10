#include "RedisConnectPool.h"

BEGIN_NAMESPACE

unsigned int SDBMHash(char *str)
{
    unsigned int hash = 0;
 
    while (*str)
    {
        // equivalent to: hash = 65599*hash + (*str++);
        hash = (*str++) + (hash << 6) + (hash << 16) - hash;
    }
 
    return (hash & 0x7FFFFFFF);
}
 
// RS Hash Function
unsigned int RSHash(char *str)
{
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;
 
    while (*str)
    {
        hash = hash * a + (*str++);
        a *= b;
    }
 
    return (hash & 0x7FFFFFFF);
}
 
// JS Hash Function
unsigned int JSHash(char *str)
{
    unsigned int hash = 1315423911;
 
    while (*str)
    {
        hash ^= ((hash << 5) + (*str++) + (hash >> 2));
    }
 
    return (hash & 0x7FFFFFFF);
}
 
// P. J. Weinberger Hash Function
unsigned int PJWHash(char *str)
{
    unsigned int BitsInUnignedInt = (unsigned int)(sizeof(unsigned int) * 8);
    unsigned int ThreeQuarters    = (unsigned int)((BitsInUnignedInt  * 3) / 4);
    unsigned int OneEighth        = (unsigned int)(BitsInUnignedInt / 8);
    unsigned int HighBits         = (unsigned int)(0xFFFFFFFF) << (BitsInUnignedInt - OneEighth);
    unsigned int hash             = 0;
    unsigned int test             = 0;
 
    while (*str)
    {
        hash = (hash << OneEighth) + (*str++);
        if ((test = hash & HighBits) != 0)
        {
            hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }
 
    return (hash & 0x7FFFFFFF);
}
 
// ELF Hash Function
unsigned int ELFHash(char *str)
{
    unsigned int hash = 0;
    unsigned int x    = 0;
 
    while (*str)
    {
        hash = (hash << 4) + (*str++);
        if ((x = hash & 0xF0000000L) != 0)
        {
            hash ^= (x >> 24);
            hash &= ~x;
        }
    }
 
    return (hash & 0x7FFFFFFF);
}
 
// BKDR Hash Function
unsigned int BKDRHash(char *str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;
 
    while (*str)
    {
        hash = hash * seed + (*str++);
    }
 
    return (hash & 0x7FFFFFFF);
}
 
// DJB Hash Function
unsigned int DJBHash(char *str)
{
    unsigned int hash = 5381;
 
    while (*str)
    {
        hash += (hash << 5) + (*str++);
    }
 
    return (hash & 0x7FFFFFFF);
}
 
// AP Hash Function
unsigned int APHash(char *str)
{
    unsigned int hash = 0;
    int i;
 
    for (i=0; *str; i++)
    {
        if ((i & 1) == 0)
        {
            hash ^= ((hash << 7) ^ (*str++) ^ (hash >> 3));
        }
        else
        {
            hash ^= (~((hash << 11) ^ (*str++) ^ (hash >> 5)));
        }
    }
 
    return (hash & 0x7FFFFFFF);
}

CONNECTPOOL::ConnectPool* CONNECTPOOL::ConnectPool::_instance = NULL ;
CONNECTPOOL::ConnectPool* CONNECTPOOL::ConnectPool::Instance() 
{
    if( _instance == NULL )
    {
        _instance = new CONNECTPOOL::ConnectPool() ; 
    }
    return _instance ; 
}

void CONNECTPOOL::ConnectPool::Release() 
{
    if(_instance )
    {
        delete _instance ; 
    }
}


CONNECTPOOL::ConnectPool::ConnectPool():m_p(NULL),\
_size(0)
{
    
}

CONNECTPOOL::ConnectPool::~ConnectPool()
{
    
}

void CONNECTPOOL::ConnectPool::AddNode(config* master ,  int groupid  ,  config* slave ) 
{
    p__node_ _master,_slave ; 
    if(master  )
    _master =  new __node__( master->ip ,master->port ) ; 
    if(slave )
    _slave = new __node__( slave->ip ,slave->port ) ;
    
    p_node_group_ _group = new __node_group__(_master   , _slave  , groupid==0?_size:groupid ) ; 
    p__list_node__ _list_node_ = new __list_node__( _group )  ;  
	if( !_size)
	{
		m_p=_list_node_ ;
	}
	else
	{
		p__list_node__ p = m_p ; 
        for( ; p->next ; p=p->next  ) ; 
        p->next = _list_node_ ; 
	}
	_size++; 
}
int CONNECTPOOL::ConnectPool::size() const  
{
   return  _size ; 
}

int CONNECTPOOL::ConnectPool::WakeUp(int msgid  ) 
{
    return 0 ; 
}

int CONNECTPOOL::ConnectPool::ExcuteCommand( char * data , char ** response , int(* HASH)(char * ) ) 
{
	if( HASH == NULL  )
	{
		HASH = PJWHash
	}
    return  0 ; 
}
END_NAMESPACE