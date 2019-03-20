#include "CModelFactory.h"

CModelFactory::CModelFactory(void)
{
}


CModelFactory::~CModelFactory(void)
{
}

CModelFactory& CModelFactory::Instance()
{
	static CModelFactory obj;
	return obj;
}

CModelBase* CModelFactory::CreateModel(const QString &strType, QWidget *parent)
{
	CModelBase *model = (CModelBase*)CModelFactory::Instance().GetClassByName(strType);
	if (!model)
	{
		model = new CModelBase();
	}
	//根据类型创建实体
// 	if (Name == "折线图")
// 	{
// 		//model = new CModelGraph1();//boost::make_shared<CModelGraph1>(parent);
// 		//model = (CModelBase*)CModelFactory::Instance().GetClassByName("CModelGraph1");
// 	} 
// 	else 
// 	{
// 		model = new CModelBase();//boost::make_shared<CModelBase>(parent);
// 	}

	return model;
}


void* CModelFactory::GetClassByName(QString className){  
	std::map<QString, PTRCreateObject>::const_iterator iter;  
	iter = m_classMap.find(className) ;  
	if ( iter == m_classMap.end() )  
		return NULL ;  
	else  
		return iter->second() ;  
}  


void CModelFactory::RegistClass(QString name, PTRCreateObject method){  
	m_classMap.insert(std::pair<QString, PTRCreateObject>(name, method)) ;  
}
