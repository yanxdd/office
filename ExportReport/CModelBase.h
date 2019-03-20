#ifndef CMODELBASE_H
#define CMODELBASE_H

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QDomElement>
#include <QDateTimeEdit>
#include <QLineEdit>
#include "common.h"
//#include "CModelFactory.h"

//namespace Ui {class CModelBase;};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	�ֳ��������࣬CModelBaseWidget��CModelBase. �ѽ��������������з���.
/// 			���ر����ò����ĶԻ���ʱ���ͷ�CModelBaseWidget����Լ�ڴ�. </summary>
///
/// <remarks>	user, 2019/3/10. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class CModelBase;

class CModelBaseWidget : public QWidget
{
	Q_OBJECT

public slots:

public:
	CModelBaseWidget(CModelBase *model, QWidget *parent = 0);
	~CModelBaseWidget();

	
	QDateTimeEdit *_tmStart;
	QDateTimeEdit *_tmEnd;

	QVBoxLayout *get_vLayoutCenter() { return _vLayoutCenter; }

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	������������õ���������. </summary>
	///
	/// <remarks>	user, 2019/3/11. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void SaveData();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	����������������. </summary>
	///
	/// <remarks>	user, 2019/3/11. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void SetData();
	
private:
	//Ui::CModelBase *ui;

	/// <summary> ģ��ָ�� </summary>
	CModelBase *_model;
	/// <summary> �м�������ֵĲ���, ����ͨ���޸�������������ò�ͬ��ʾ���� </summary>
	QVBoxLayout *_vLayoutCenter;

	QLineEdit  *_lineComment;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	WORD�е�ÿ1����ǩ��Ӧ1����ʾģ��.  </summary>
///
/// <remarks>	user, 2019/3/9. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class CModelBase
{
public:
	CModelBase();
	~CModelBase();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	ģ����. </summary>
	///
	/// <remarks>	user, 2019/3/10. </remarks>
	///
	/// <returns>	The name. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	//virtual QString GetName() { return QString("ģ�ͻ���"); }

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	���ɲ������õ���ʾ����. ����ʾ��Ӧ������ </summary>
	///
	/// <remarks>	user, 2019/3/10. </remarks>
	///
	/// <returns>	null if it fails, else the parameter set widget. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual CModelBaseWidget* GenParamSetWidget(QWidget *parent=0);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	����XML��ʽ��ģ�ͽڵ㣬 �����Լ���������Ϣ. QDomElement�Ĵ��ں��ͷ��Ƿ������⣿��</summary>
	///
	/// <remarks>	user, 2019/3/9. </remarks>
	///
	/// <returns>	The xml node. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void GenXmlModelNode(QDomDocument &doc, QDomElement &node);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	����һ����ʾ������ͼ�����Ǳ�. </summary>
	///
	/// <remarks>	user, 2019/3/9. </remarks>
	///
	/// <returns>	The display widget. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual QWidget* GenDisplayWidget();

public:
	QString Name() const { return _Name; }
	void Name(QString val) { _Name = val; }

	QString Type() const { return _Type; }
	void Type(QString val) { _Type = val; }

	QString StrComment() const { return _strComment; }
	void StrComment(QString val) { _strComment = val; }

private:
	/// <summary> ģ�Ͷ�Ӧ�ı�ǩ���� </summary>
	QString _Name;
	/// <summary> ģ�����ͣ�����ģ������ </summary>
	QString _Type;
	/// <summary> ��ע </summary>
	QString _strComment;
};

CLASS_PTR_DECLARE(CModelBase);

//REGISTER(CModelBase); ���࣬�����õ�������Ҫע��

#endif // CMODELBASE_H
