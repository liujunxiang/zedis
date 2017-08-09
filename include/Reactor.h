/*
 * Reactor.h
 *
 *  Created on: Aug 7, 2017
 *      Author: root
 */

#ifndef REACTOR_H_
#define REACTOR_H_
#include "NameSpace.h"
#include "Macro.h"
BEGIN_NAMESPACE
class ReactorImp ;
class AbstractEventHandle ;
class EXPORT Reactor{
public:
	Reactor(ReactorImp *p ) ;
	~Reactor() ;
public:
	int RegistEvent(AbstractEventHandle * p  , Event e  ) ;
	int RemoveEvent(AbstractEventHandle * p ) ;
	int HandleEvent() ;
private:
	Reactor& operator =( const Reactor & ) ;
private:
	ReactorImp* m_p_imp;
} ;

END_NAMESPACE

#endif /* REACTOR_H_ */
