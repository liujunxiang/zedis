/*
 * Global.h
 *
 *  Created on: Aug 8, 2017
 *      Author: root
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_
#include "Reactor.h"
#include "Sigton.h"
#include "NameSpace.h"
#include "Macro.h"
BEGIN_NAMESPACE

class Reactor;

class Global : public Singleton<Global>
{
public:
    Global(void);
    ~Global(void);
    Reactor* manager;
};
#define REACTOR_MANAGER_POINTER Global::instance()
#define REACTOR_MANAGER_INSTANCE ( *(REACTOR_MANAGER_POINTER->manager ))
END_NAMESPACE
#endif /* GLOBAL_H_ */
