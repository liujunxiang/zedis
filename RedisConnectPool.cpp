#include "RedisConnectPool.h"
namespace STANDAND_RESID_PROTOL{
static inline int __get_num(   char ** data )
{
    #if 1
    int len = 0 ; 
    while( *(*data) !='\r' )
    {
        len = (len*10)+(**data - '0');  
        ++(*data) ; 
    }
    return len ;    
    #endif 
}

static inline int __get_str(char ** data  ,  char *out)
{
    char *head = *data ; 
    char *pwalk = head ; 
    for( ; *pwalk != '\r' ; ++(*data) ,pwalk++ ) ; 
    if( out )
    {
        strncpy(out ,head ,   pwalk-head ) ; 
    }
    return  0 ; 
}
}


namespace HASH_ALGOTITHM
{
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
}
BEGIN_NAMESPACE


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

int CONNECTPOOL::ConnectPool::set(  char * key ,  char *command ,char *out) 
{
    int index = HASH_ALGOTITHM::PJWHash( key )%this->_size  ; 

    int walk ; 
    p__list_node__ p ; 
    for(   walk= 0 ,  p = this->m_p  ; walk<index ; walk++ , p=p->next ) ; 
    #if DEBUG
        printf("key[%s] will locate at the [%d] redis-group\n" ,key ,p->g->id  ) ;
    #endif 
    //
    if( p->g->master->set( command   ) || p->g->slave->set( command   )  )
    {
        sprintf( out ,  "-ERR:"DEBUG_FORMAT"command[%s] execute failed\r\n" ,DEBUG_VALIST,  command ) ;
    }
    else
    {
         sprintf( out ,  "+OK\r\n") ;
    }
    return  0 ; 
}


int CONNECTPOOL::ConnectPool::get(  char * key ,  char *command ,char *out) 
{
    int index = HASH_ALGOTITHM::PJWHash( key )%this->_size  ; 
    #if DEBUG
        printf("key[%s] will locate at the [%d] redis-group\n" ,key ,index  ) ;
    #endif 
    int walk ; 
    p__list_node__ p ; 
    for(   walk= 0 ,  p = this->m_p  ; walk<index ; walk++ , p=p->next ) ; 
    
    p->g->active_node()->get( command , out  ) ; 
    return  0 ; 
}
void CONNECTPOOL::ConnectPool::info( char *out ) 
{
    p__list_node__ p = this->m_p  ; 
    char ch[16384]={0} ; 
    for( ; p->next ; p=p->next )
    {
        printf("gid=%d\n" ,p->g->id ) ; 
        char buf[ 4096] = {0 } ; 
        char *_walk= buf ; 
        char *head=_walk  ;
        sprintf(buf , "==============grouid[%d]===============\r\n" ,p->g->id )  ;
        _walk =head+ strlen( buf) ; 
        
        sprintf( _walk , "****master server[%s,%d]******\r\n" , p->g->master->ip ,p->g->master->port  ) ; 
        _walk = head + strlen( buf) ; 
        p->g->master->info( _walk ) ; 
        _walk = head + strlen( buf) ; 
        
        sprintf( _walk , "****slave server[%s,%d]******\r\n" , p->g->slave->ip ,p->g->slave->port  ) ; 
        _walk = head + strlen( buf) ; 
        p->g->slave->info( _walk ) ; 

        strcat( ch ,buf ) ; 
    }
    printf("ch=%s\n" , ch ) ; 
}
int CONNECTPOOL::ConnectPool::size() const  
{
   return  _size ; 
}

int CONNECTPOOL::ConnectPool::WakeUp(int msgid  ) 
{
    return 0 ; 
}
int CONNECTPOOL::ConnectPool::ExcuteCommand( char * data , char * response , unsigned int(* HASH)(char * ) ) 
{
    #if DEBUG
    printf(DEBUG_FORMAT"\n" , DEBUG_VALIST ) ;
    #endif 
	if( HASH == NULL  )
	{
		HASH = HASH_ALGOTITHM::PJWHash ;
	}
	char *pwalk = data ; 
    typedef int( *FUN )( char **) ; 
    typedef int( *FUN_STR )( char ** , char* ) ; 
    FUN convert = STANDAND_RESID_PROTOL::__get_num ; 
    FUN_STR conv = STANDAND_RESID_PROTOL::__get_str ;
	pwalk++ ;
	int componments= (*convert)( &pwalk ) ; 
    //printf("componments=[%d],data=[%s],pwalk=[%s]\n" , componments , data ,pwalk  ) ; 
    #if 1
    switch(componments )
    {
        case 1:
        {
            /**parse command stream**/
            pwalk +=3;//point to the begin of command-length-str
            int size = (*convert)( &pwalk ) ;//command length 
            char *out =(char*) malloc( size+1 ) ; 
            memset( out , 0 ,size+1  ) ; 
            pwalk +=2;//point to the begin of command-str
            (*conv)( &pwalk ,out ) ; 
            if( !strcmp( out ,"COMMAND") )
            {
                sprintf( response ,  "+OK\r\n" ) ;
                return  0 ; 
            }
            
            
            if( !strcmp( out ,"INFOCLUSTER") )
            {
                this->info( NULL ) ; 
                sprintf( response ,  "+OK\r\n" ) ;
                return  0 ; 
            }
            
             sprintf( response ,  "-ERR:no support command[%s]\r\n" ,out  ) ;
            return -1; 
        }
        break;
        case 2:
        {
            /**parse command stream**/
            pwalk +=3;//point to the begin of command-length-str
            int size = (*convert)( &pwalk ) ;//command length 
            char *out =(char*) malloc( size+1 ) ; 
            memset( out , 0 ,size+1  ) ; 
            pwalk +=2;//point to the begin of command-str
            (*conv)( &pwalk ,out ) ; 
            if( strcmp( out , "get") &&  strcmp( out , "GET") )
            {
                sprintf( response ,  "-ERR:"DEBUG_FORMAT"unspport  command[%s]\r\n" ,DEBUG_VALIST,  out ) ; //error starts-with -
                #if DEBUG
                printf("response=%s\n" , response ) ; 
                #endif 
                free( out ) ; 
                return -1; 
            }
            
            /**parse key stream**/
            pwalk +=3;//point to the begin of key-length-str
            size = (*convert)( &pwalk ) ;
            char *out_key =(char*) malloc( size+1 ) ;
            memset( out_key , 0 ,size+1  ) ; 
            pwalk +=2;//point to the begin of key-str
            (*conv)( &pwalk ,out_key ) ; 
            #if DEBUG
            printf( DEBUG_FORMAT"command=[%s],key=[%s]\n" , DEBUG_VALIST , out , out_key) ; 
            #endif 
            
            char command[256]={0} ; 
            sprintf( command , "%s %s" ,out ,out_key   ) ; 
            this->get(out_key , command  , response ) ; 
            #if DEBUG
                printf("response=%s\n" ,response  ) ; 
            #endif 
            free( out ) ; 
            free( out_key ) ; 
        }
        break ;
        case 3:
        {
            /**parse command stream**/
            pwalk +=3;//point to the begin of command-length-str
            int size = (*convert)( &pwalk ) ;//command length 
            char *out =(char*) malloc( size+1 ) ; 
            memset( out , 0 ,size+1  ) ; 
            pwalk +=2;//point to the begin of command-str
            (*conv)( &pwalk ,out ) ; 
            if( strcmp( out , "set") &&  strcmp( out , "SET") )
            {
                sprintf( response ,  "-ERR:"DEBUG_FORMAT"unspport  command[%s]\r\n" ,DEBUG_VALIST,  out ) ; //error starts-with -
                #if DEBUG
                printf("response=%s\n" , response ) ; 
                #endif
                free( out ) ; 
                return -1; 
            }
            
       
            /**parse key stream**/
            pwalk +=3;//point to the begin of key-length-str
            size = (*convert)( &pwalk ) ;
            char *out_key =(char*) malloc( size+1 ) ;
            memset( out_key , 0 ,size+1  ) ; 
            pwalk +=2;//point to the begin of key-str
            (*conv)( &pwalk ,out_key ) ; 
            
            
            
            /**parse value stream**/
            pwalk +=3;//point to the begin of value-length-str
            size = (*convert)( &pwalk ) ;
            char *out_value =(char*) malloc( size+1 ) ;
            memset( out_value , 0 ,size+1  ) ; 
            pwalk +=2;//point to the begin of key-str
            (*conv)( &pwalk ,out_value ) ; 
            

            char command[256]={0} ; 
            sprintf( command , "%s %s %s" ,out ,out_key , out_value  ) ; 
            #if DEBUG
                printf(DEBUG_FORMAT"command=[%s]\n" , DEBUG_VALIST , command ) ; 
            #endif
            this->set(out_key , command  , response ) ; 
            free( out ) ; 
            free( out_key ) ; 
            free(out_value  ) ; 
        }
        break;
        default:
        return -1 ; 
    }
    #endif 
    return  0 ; 
}
END_NAMESPACE