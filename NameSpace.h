/*
 * NameSpace.h
 *
 *  Created on: Aug 7, 2017
 *      Author: root
 */

#ifndef NAMESPACE_H_
#define NAMESPACE_H_
#include "Version.h"
#define NAMESPACE_MAKER(a,b,c) NAMESPACE_##a##_##b_##c
#define NAMESPACE_CONCAT(A,B,C) NAMESPACE_MAKER(A,B,C)
#define NAMESPACENAME NAMESPACE_CONCAT( T_MAJOR_VERSION , T_MINOR_VERSION ,  T_BETA_VERSION )
#define BEGIN_NAMESPACE namespace NAMESPACENAME{
#define END_NAMESPACE };\
	using namespace NAMESPACENAME ;

#endif /* NAMESPACE_H_ */
