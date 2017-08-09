/*
 * Global.cpp
 *
 *  Created on: Aug 8, 2017
 *      Author: root
 */

#include "Global.h"
DECLARE_SINGLETON_MEMBER(Global);

Global::Global(void)
{
	manager = new Reactor( NULL );
}

Global::~Global(void)
{
	Safe_del( manager ) ;
}
