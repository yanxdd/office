#ifndef CMODELGRAPH1_H
#define CMODELGRAPH1_H

#include <CModelBase.h>
#include <QTextEdit>
#include <QColorDialog>

#include "common.h"

namespace Ui {class CModelGraph1Widget;};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	��ɫ����ͼ. ��ɫ ������ ������ ����Դ
/// 			�ֳ��������࣬�ѽ��������������з���.
/// 			���ر����ò����ĶԻ���ʱ���ͷŽ����࣬��Լ�ڴ�. </summary>
///
/// <remarks>	user, 2019/3/10. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class CModelGraph1;

class CModelGraph1Widget : public CModelBaseWidget
{
	Q_OBJECT

public slots:
	void SelectColorSlot();

public:
	CModelGraph1Widget(CModelBase *model, QWidget *parent = 0);
	~CModelGraph1Widget();

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
	CModelGraph1 *_model;

	Ui::CModelGraph1Widget *ui;
};

class CModelGraph1ShowWidget : public QWidget
{
Q_OBJECT


public:
	CModelGraph1ShowWidget(QWidget *parent = 0);
	~CModelGraph1ShowWidget();

private:
	CModelGraph1 *_model;

	//Ui::CModelGraph1ShowWidget *ui;
};


class CModelGraph1 : public CModelBase
{
	//Q_OBJECT

public:
	CModelGraph1();//QWidget *parent = 0);
	~CModelGraph1();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	ģ����. </summary>
	///
	/// <remarks>	user, 2019/3/10. </remarks>
	///
	/// <returns>	The name. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	QString GetName() { return QString("��ɫ����ͼ"); }

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

	QString StrXComment() const { return _strXComment; }
	void StrXComment(QString val) { _strXComment = val; }

	QString StrYComment() const { return _strYComment; }
	void StrYComment(QString val) { _strYComment = val; }

	unsigned int UiRGB() const { return _uiRGB; }
	void UiRGB(unsigned int val) { _uiRGB = val; }

	QString StrDataSource() const { return _strDataSource; }
	void StrDataSource(QString val) { _strDataSource = val; }

private:
	//Ui::CModelGraph1 *ui;

	/// <summary> The string x coordinate comment </summary>
	QString _strXComment;
	/// <summary> The string y coordinate comment </summary>
	QString _strYComment;
	/// <summary> RGB��ɫ </summary>
	unsigned int _uiRGB;
	/// <summary> ������Դ��һ����дsql��� </summary>
	QString _strDataSource;
};

CLASS_PTR_DECLARE(CModelGraph1);

#endif // CMODELGRAPH1_H
