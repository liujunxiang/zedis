/*
 * Type.h
 *
 *  Created on: Aug 7, 2017
 *      Author: root
 */

#ifndef TYPE_H_
#define TYPE_H_
typedef int SOCKET_T ;
typedef unsigned int Event;
enum EventMask {
    e_READEVENT  = 0x01,
    e_WRITEEVENT = 0x02,
    e_ERROREVENT = 0x03,
};
#endif /* TYPE_H_ */
