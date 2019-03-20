#ifndef CDATABASE_H
#define CDATABASE_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>

class CDataBase
{
public:
	CDataBase(void);
	CDataBase(QString &type, QString &host, QString &db_name, QString &user, QString &pass);
	~CDataBase(void);
	
	bool Init();

	QSqlDatabase * Db() const { return _db; }
	void Db(QSqlDatabase * val) { _db = val; }

private:
	QSqlDatabase *_db;

	QString _strDbName;
	QString _strType;
	QString _strHost;
	QString _strUser;
	QString _strPass;


	QString _strConnName;
};

#endif