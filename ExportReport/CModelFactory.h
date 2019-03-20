#ifndef CMODELFACTORY_H
#define CMODELFACTORY_H

#include <QString>
#include <QWidget>
#include <iostream>
#include <map>
#include "CModelBase.h"
#include "common.h"

typedef void* (*PTRCreateObject)(void);  


//工厂模式
class CModelFactory
{

public:
	CModelFactory(void);
	~CModelFactory(void); 


	/// <summary>	通过类名称字符串获取类的实例. </summary>
	void* GetClassByName(QString className);  

	/// <summary>	注册，将给定的类名称字符串和对应的创建类对象的函数保存到map中  </summary>
	void RegistClass(QString name, PTRCreateObject method);  


	static CModelFactory& Instance();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	创建一个模型对象. </summary>
	///
	/// <param name="Name">	模型类型. </param>
	///
	/// <returns>	. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	CModelBase* CreateModel(const QString &Name, QWidget *parent=0);

private:  
	std::map<QString, PTRCreateObject> m_classMap ; 

};

CLASS_PTR_DECLARE(CModelFactory);

//注册动作类
class RegisterAction{
public:
	RegisterAction(QString className, PTRCreateObject ptrCreateFn){
		CModelFactory::Instance().RegistClass(className, ptrCreateFn);
	}
};

#endif