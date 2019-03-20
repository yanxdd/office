#include "CDataBase.h"


CDataBase::CDataBase(void)
{
}


CDataBase::CDataBase(QString &type, QString &host, QString &db_name, QString &user, QString &pass)
	:_db(NULL),
	_strType(type),
	_strHost(host),
	_strDbName(db_name),
	_strUser(user),
	_strPass(pass)
{
	_strConnName = "CDataBase";
}

CDataBase::~CDataBase(void)
{
	if (_db)
	{
		_db->close();
		QSqlDatabase::removeDatabase(_strConnName);
		delete _db;
	}
}

bool CDataBase::Init()
{
	if (!_db)
		return true;

	_db = new QSqlDatabase();
	if ( !QString::compare(_strType, "mysql", Qt::CaseInsensitive) )
	{
		*_db = QSqlDatabase::addDatabase("QMYSQL", _strConnName);
	} 
	else if ( !QString::compare(_strType, "oracle", Qt::CaseInsensitive) )
	{
		*_db = QSqlDatabase::addDatabase("QOCI", _strConnName);
	} 

	_db->setHostName(_strHost);
	_db->setDatabaseName(_strDbName);
	_db->setUserName(_strUser);
	_db->setPassword(_strPass); 
	if (!_db->open()) 
	{
		//QMessageBox::critical(0, tr("无法打开数据库"), "无法创建数据库连接！ ", QMessageBox::Cancel);
		QSqlDatabase::removeDatabase(_strConnName);
		delete _db;
		return false;
	}
	return true;
}
