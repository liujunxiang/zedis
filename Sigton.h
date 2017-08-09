/*
 * Sigton.h
 *
 *  Created on: Aug 8, 2017
 *      Author: root
 */

#ifndef SIGTON_H_
#define SIGTON_H_

#include "NameSpace.h"
#include "Macro.h"
BEGIN_NAMESPACE
template <class T>
class Singleton
{
public:
    static inline T* instance();
    void release();
protected:
    Singleton(void){}
    ~Singleton(void){}
    static T* _instance;
};

template <class T>
inline T* Singleton<T>::instance()
{
    if(!_instance)
        _instance = new T;
    return _instance;
}

template <class T>
void Singleton<T>::release()
{
    if (!_instance)
        return;
    delete _instance;
    _instance = 0;
}

#define DECLARE_SINGLETON_MEMBER(_Ty)   \
    template <> _Ty* Singleton<_Ty>::_instance = NULL;
END_NAMESPACE
#endif /* SIGTON_H_ */
