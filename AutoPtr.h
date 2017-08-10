/*
 * AutoPtr.h
 *
 *  Created on: Aug 7, 2017
 *      Author: root
 */

#ifndef AUTOPTR_H_
#define AUTOPTR_H_

template<typename T>
class AutoPtr
{
public:
	typedef T TYPE ;
	typedef T* POINTER ;
public:
	explicit AutoPtr( POINTER p ):_p(p)
	{

	}
	~AutoPtr()
	{
		if( _p)
		{
			delete  _p ;
		}
	}
private:
	POINTER _p ;
} ;

template<typename T>
class AutoPtrContainer
{
public:
	typedef T TYPE ;
	typedef T* POINTER ;
	typedef AutoPtr<T> OBJECT ;
	typedef OBJECT* P_OBJECT ;
private:
	#include <vector>
	std::vector<P_OBJECT> m_vec ;
public:
	void Add(POINTER p)
	{
		AutoPtr<T>* _p = new AutoPtr<T>( p ) ;
		m_vec.push_back ( _p ) ;
	}

public:
	AutoPtrContainer()
	{
			
	}

	~AutoPtrContainer()
	{
		std::vector<P_OBJECT> it;
		for( it == m_vec.begin() ;it!=m_vec.end() ;it++)
		{
			delete( *it ) ;
		}
	}
} ;

#endif /* AUTOPTR_H_ */
