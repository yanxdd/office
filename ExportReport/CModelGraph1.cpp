#include <QColorDialog>
#include <QColor>
#include "CModelGraph1.h"
#include "ui_CModelGraph1.h"
#include "CModelFactory.h"

REGISTER(CModelGraph1, "单色折线图"); //注册


CModelGraph1Widget::CModelGraph1Widget(CModelBase *model, QWidget *parent)
	: CModelBaseWidget(model, parent)
{
	ui = new Ui::CModelGraph1Widget();
	ui->setupUi(this);

	_model = static_cast<CModelGraph1*>(model);
	SetData();

	this->get_vLayoutCenter()->addWidget(ui->layoutWidget);

	//向下面的垂直布局中添加东西
	QTextEdit *txtTest = new QTextEdit(this);
	txtTest->setText("单色折线图");
	this->get_vLayoutCenter()->addWidget(txtTest);
	
	connect(ui->btnColor, SIGNAL(clicked()), this, SLOT(SelectColorSlot()));

	//
// 	QHBoxLayout *hLayout9 = new QHBoxLayout(this);
// 	QLabel* labelComment = new QLabel("备注:");
// 	_lineComment = new QLineEdit(this);
// 	hLayout9->addWidget(labelComment);
// 	hLayout9->addWidget(_lineComment);
}

CModelGraph1Widget::~CModelGraph1Widget()
{
	delete ui;
}


void CModelGraph1Widget::SaveData()
{
	CModelBaseWidget::SaveData();

	_model->StrXComment(ui->lineEditX->text());
	_model->StrYComment(ui->lineEditY->text());
	_model->UiRGB(ui->lineRGB->text().toUInt(NULL, 16));
	_model->StrDataSource(ui->txtDataSrc->toPlainText());
}

void CModelGraph1Widget::SetData()
{
	CModelBaseWidget::SetData();

	ui->lineEditX->setText(_model->StrXComment());
	ui->lineEditY->setText(_model->StrYComment());
	ui->lineRGB->setText( QString::number(_model->UiRGB(), 16) );
	ui->txtDataSrc->setText(_model->StrDataSource());
}

void CModelGraph1Widget::SelectColorSlot()
{
	unsigned int uiRgb = _model->UiRGB();
	QColor c( (uiRgb >> 16) & 0xFF, (uiRgb >> 8) & 0xFF, uiRgb & 0xFF );
	QColorDialog dlg;//调出颜色选择器对话框
	c = dlg.getColor(c);//getRgba();
	if(c.isValid())
		ui->lineRGB->setText( QString::number(c.red() << 16 | c.green() << 8 | c.blue(), 16) );
}


//==========================================================================================================



CModelGraph1::CModelGraph1()//(QWidget *parent)
	//: CModelBase(parent)
	:_uiRGB(0xFF0000) //默认红色 Qt::red
{
	//ui = new Ui::CModelGraph1();
	//ui->setupUi(this);
}

CModelGraph1::~CModelGraph1()
{
	//delete ui;
}

void CModelGraph1::GenXmlModelNode(QDomDocument &doc, QDomElement &node)
{
	CModelBase::GenXmlModelNode(doc, node);


	// 1. 设置横坐标
	QDomElement title = doc.createElement("横坐标");	//创建子元素
	QDomText text; //设置括号标签中间的值
	text = doc.createTextNode(this->StrXComment());
	title.appendChild(text);
	node.appendChild(title);
	// 2. 设置纵坐标
	title = doc.createElement("纵坐标");	//创建子元素
	text= doc.createTextNode(this->StrYComment());
	title.appendChild(text);
	node.appendChild(title);
	// 3. 设置颜色
	title = doc.createElement("颜色");	//创建子元素
	text= doc.createTextNode( QString::number(this->UiRGB(), 16) );
	title.appendChild(text);
	node.appendChild(title);

}

QWidget* CModelGraph1::GenDisplayWidget()
{
	return new QWidget();
}

CModelBaseWidget* CModelGraph1::GenParamSetWidget(QWidget *parent)
{
	CModelBaseWidget *widget = new CModelGraph1Widget(this, parent);

	return widget;
}

