#include <QHBoxLayout>
#include <QLabel>
#include <QDateTimeEdit>

#include "CModelBase.h"

//#include "ui_CModelBase.h"


CModelBaseWidget::CModelBaseWidget(CModelBase *model, QWidget *parent)
	: QWidget(parent),
	_model(model)
{
	//ui = new Ui::CModelBase();
	//ui->setupUi(this);
	
	//������һ����ֱ����
	QVBoxLayout* vLayout = new QVBoxLayout(this);

	QHBoxLayout *hLayout1 = new QHBoxLayout(this);
	QLabel* labelStartTime = new QLabel("��ʼʱ��:", this);
	_tmStart = new QDateTimeEdit(this);
	//QTimeEdit *tmStart = new QTimeEdit();
	hLayout1->addWidget(labelStartTime);
	hLayout1->addWidget(_tmStart);
	hLayout1->addStretch();

	QHBoxLayout *hLayout2 = new QHBoxLayout(this);
	QLabel* labelEndTime = new QLabel("����ʱ��:", this);
	_tmEnd = new QDateTimeEdit(this);
	hLayout2->addWidget(labelEndTime);
	hLayout2->addWidget(_tmEnd);
	hLayout2->addStretch();

	_vLayoutCenter = new QVBoxLayout(this);

	QHBoxLayout *hLayout9 = new QHBoxLayout(this);
	QLabel* labelComment = new QLabel("��ע:");
	_lineComment = new QLineEdit(this);
	hLayout9->addWidget(labelComment);
	hLayout9->addWidget(_lineComment);

	vLayout->addLayout(hLayout1);
	vLayout->addLayout(hLayout2);
	vLayout->addLayout(_vLayoutCenter);
	vLayout->addLayout(hLayout9);

}

CModelBaseWidget::~CModelBaseWidget()
{
	//delete ui;
}

void CModelBaseWidget::SaveData()
{
	_model->StrComment(_lineComment->text());
}

void CModelBaseWidget::SetData()
{
	_lineComment->setText(_model->StrComment());
}



//===================================================================


CModelBase::CModelBase()
{
	_strComment = "";
}

CModelBase::~CModelBase()
{
}

void CModelBase::GenXmlModelNode(QDomDocument &doc, QDomElement &node)
{
	// 1. ��������
	//node.setAttribute("id",1);
	node.setAttribute("name", "��ǩ1");					//��������
	node.setAttribute("type", "����");					//��������

	// 2. ���ñ�ע
	QDomElement title = doc.createElement("��ע");	//������Ԫ��
	QDomText text; //�������ű�ǩ�м��ֵ
	text= doc.createTextNode(this->StrComment());
	title.appendChild(text);
	node.appendChild(title);

	return;
}

QWidget* CModelBase::GenDisplayWidget()
{
	return new QWidget();
}

CModelBaseWidget* CModelBase::GenParamSetWidget(QWidget *parent)
{
	CModelBaseWidget *widget = new CModelBaseWidget(this, parent);

	return widget;
}
