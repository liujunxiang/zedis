/*
 * Reactor.cpp
 *
 *  Created on: Aug 7, 2017
 *      Author: root
 */
#include "Reactor.h"
#include "ReactorImp.h"

BEGIN_NAMESPACE
Reactor::Reactor(ReactorImp *p ):m_p_imp( new ReactorImp() )
{
}

Reactor::~Reactor()
{
	Safe_del( m_p_imp )
}

int Reactor::RegistEvent(AbstractEventHandle * p  , Event e )
{
	return  m_p_imp->RegistEvent( p ,e )  ;
}


int Reactor::RemoveEvent(AbstractEventHandle * p )
{
	return m_p_imp->RemoveEvent( p )   ;
}

int Reactor::HandleEvent( )
{

	m_p_imp->HandleEvent() ;
	return   0 ;
}

END_NAMESPACE
