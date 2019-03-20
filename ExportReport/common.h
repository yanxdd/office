#ifndef COMMON_H
#define COMMON_H

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#pragma execution_character_set("utf-8")

#define CLASS_PTR_DECLARE(a) typedef boost::shared_ptr<class a> a##Ptr;\
	typedef boost::weak_ptr<class a> a##WPtr


#define REGISTER(className, ChineseName)                                             \
	className* objectCreator##className(){                              \
		return new className;                                           \
	}                                                                   \
	RegisterAction g_creatorRegister##className(                        \
ChineseName,(PTRCreateObject)objectCreator##className)


#endif