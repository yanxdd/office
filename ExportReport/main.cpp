#include "ExportReport.h"
#include <QApplication>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QtCore/QTextCodec>
#include "qt_windows.h"


void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	static QMutex mutex;
	mutex.lock();

	QString text;
	switch(type)
	{
	case QtDebugMsg:
		text = QString("Debug:");
		break;

	case QtWarningMsg:
		text = QString("Warning:");
		break;

	case QtCriticalMsg:
		text = QString("Critical:");
		break;

	case QtFatalMsg:
		text = QString("Fatal:");
	}

	QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
	QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
	QString current_date = QString("[%1]").arg(current_date_time);
	QString message = QString("%1 %2 %3 %4").arg(current_date).arg(text).arg(context_info).arg(msg);
	
	static QFile *file = NULL;
	if (!file)
	{
		file = new QFile("ExportReport.log");
		file->open(QIODevice::WriteOnly | QIODevice::Append);
	}

	QTextStream text_stream(file);
	text_stream << message << "\r\n";
	file->flush();
	//file.close();

	mutex.unlock();
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//QTextCodec::setCodecForCStrings(QTextCodec::codecForName("system"));//����C�ַ�����
	//QTextCodec::setCodecForLocale(QTextCodec::codecForName("system"));//����Qt�������ַ�����
	//QTextCodec::setCodecForTr(QTextCodec::codecForName("system"));//����ǹ�tr�ģ�tr��QObject::tr��ΪQt��һ���������

	qInstallMessageHandler( myMessageOutput );


	HRESULT result = OleInitialize(0);

	if (result != S_OK && result != S_FALSE)
	{
		qDebug()<<QString("Could not initialize OLE (error %x)").arg((unsigned int)result);
	}

	ExportReport w;
	w.show();
	return a.exec();
}
