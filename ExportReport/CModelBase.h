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
/// <summary>	分成了两个类，CModelBaseWidget和CModelBase. 把界面类和数据类进行分离.
/// 			当关闭设置参数的对话框时，释放CModelBaseWidget，节约内存. </summary>
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
	//Ui::CModelBase *ui;

	/// <summary> 模型指针 </summary>
	CModelBase *_model;
	/// <summary> 中间参数部分的布局, 子类通过修改这个布局来设置不同显示内容 </summary>
	QVBoxLayout *_vLayoutCenter;

	QLineEdit  *_lineComment;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	WORD中的每1个标签对应1个显示模型.  </summary>
///
/// <remarks>	user, 2019/3/9. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class CModelBase
{
public:
	CModelBase();
	~CModelBase();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	模型名. </summary>
	///
	/// <remarks>	user, 2019/3/10. </remarks>
	///
	/// <returns>	The name. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	//virtual QString GetName() { return QString("模型基类"); }

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

public:
	QString Name() const { return _Name; }
	void Name(QString val) { _Name = val; }

	QString Type() const { return _Type; }
	void Type(QString val) { _Type = val; }

	QString StrComment() const { return _strComment; }
	void StrComment(QString val) { _strComment = val; }

private:
	/// <summary> 模型对应的标签名称 </summary>
	QString _Name;
	/// <summary> 模型类型，就是模型名称 </summary>
	QString _Type;
	/// <summary> 备注 </summary>
	QString _strComment;
};

CLASS_PTR_DECLARE(CModelBase);

//REGISTER(CModelBase); 基类，不会用到，不需要注册

#endif // CMODELBASE_H
