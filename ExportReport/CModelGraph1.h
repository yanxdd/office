#ifndef CMODELGRAPH1_H
#define CMODELGRAPH1_H

#include <CModelBase.h>
#include <QTextEdit>
#include <QColorDialog>

#include "common.h"

namespace Ui {class CModelGraph1Widget;};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	单色折线图. 颜色 横坐标 纵坐标 数据源
/// 			分成了两个类，把界面类和数据类进行分离.
/// 			当关闭设置参数的对话框时，释放界面类，节约内存. </summary>
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
	/// <summary>	保存界面上设置的所有数据. </summary>
	///
	/// <remarks>	user, 2019/3/11. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void SaveData();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	给界面上设置数字. </summary>
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
	/// <summary>	模型名. </summary>
	///
	/// <remarks>	user, 2019/3/10. </remarks>
	///
	/// <returns>	The name. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	QString GetName() { return QString("单色折线图"); }

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	生成参数设置的显示布局. 并显示对应的数据 </summary>
	///
	/// <remarks>	user, 2019/3/10. </remarks>
	///
	/// <returns>	null if it fails, else the parameter set widget. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual CModelBaseWidget* GenParamSetWidget(QWidget *parent=0);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	生成XML格式的模型节点， 保存自己的配置信息. QDomElement的存期和释放是否有问题？？</summary>
	///
	/// <remarks>	user, 2019/3/9. </remarks>
	///
	/// <returns>	The xml node. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void GenXmlModelNode(QDomDocument &doc, QDomElement &node);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	生成一个显示部件，图或者是表. </summary>
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
	/// <summary> RGB颜色 </summary>
	unsigned int _uiRGB;
	/// <summary> 数据来源，一般填写sql语句 </summary>
	QString _strDataSource;
};

CLASS_PTR_DECLARE(CModelGraph1);

#endif // CMODELGRAPH1_H
