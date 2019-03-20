#ifndef CMODELFACTORY_H
#define CMODELFACTORY_H

#include <QString>
#include <QWidget>
#include <iostream>
#include <map>
#include "CModelBase.h"
#include "common.h"

typedef void* (*PTRCreateObject)(void);  


//����ģʽ
class CModelFactory
{

public:
	CModelFactory(void);
	~CModelFactory(void); 


	/// <summary>	ͨ���������ַ�����ȡ���ʵ��. </summary>
	void* GetClassByName(QString className);  

	/// <summary>	ע�ᣬ���������������ַ����Ͷ�Ӧ�Ĵ��������ĺ������浽map��  </summary>
	void RegistClass(QString name, PTRCreateObject method);  


	static CModelFactory& Instance();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	����һ��ģ�Ͷ���. </summary>
	///
	/// <param name="Name">	ģ������. </param>
	///
	/// <returns>	. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	CModelBase* CreateModel(const QString &Name, QWidget *parent=0);

private:  
	std::map<QString, PTRCreateObject> m_classMap ; 

};

CLASS_PTR_DECLARE(CModelFactory);

//ע�ᶯ����
class RegisterAction{
public:
	RegisterAction(QString className, PTRCreateObject ptrCreateFn){
		CModelFactory::Instance().RegistClass(className, ptrCreateFn);
	}
};

#endif