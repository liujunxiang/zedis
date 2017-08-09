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
BEGIN_NAMESPACE
namespace CONNECTPOOL{
typedef struct __node__
{
	char ip[16] ;
	unsigned int port ;
	unsigned char status ;
	redisContext* c;
}__attribute__((packed)) _node_ ,*p__node_;
typedef struct __node_group__
{
	struct __node__* master ;
	struct __node__* slave ;
}_node_group_ ,*p_node_group_;
typedef struct __list_node__
{
	p_node_group_ g ;
	__list_node__* next ;
	__list_node__():g(NULL),next(NULL){ }
} ;
class DLLEXPORT ConnectPool{
public:
	ConnectPool();
	~ConnectPool() ;
public:
};
}

END_NAMESPACE


#endif /* REDISCONNECTPOOL_H_ */
