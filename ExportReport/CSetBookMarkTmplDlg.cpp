#include "CSetBookMarkTmplDlg.h"
#include "ui_CSetBookMarkTmplDlg.h"
#include "common.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QMessageBox>
#include "ExportReport.h"

CSetBookMarkTmplDlg::CSetBookMarkTmplDlg(CModelBase *model, QString &type, CDataBase *db, ExportReport *parent)
	: QDialog(parent),
	_parent(parent),
	_model(model),
	_db(db),
	_widgetCenter(NULL)
{
	ui = new Ui::CSetBookMarkTmplDlg();
	ui->setupUi(this);

	QHBoxLayout *hLayout = new QHBoxLayout(this);//widget);
	QLabel* labelType = new QLabel(" ����:  ", this);
	_comboxType = new QComboBox(this);
	//_comboxType->addItem(_strType);
	_comboxType->addItem("��ɫ����ͼ");
	_comboxType->addItem("��1");
	_comboxType->addItem("����2");
	_comboxType->addItem("Ĭ��");
	_comboxType->setCurrentText(type);
	hLayout->addWidget(labelType);
	hLayout->addWidget(_comboxType);
	hLayout->addStretch();
	QGroupBox *groupBox = new QGroupBox(this);
	groupBox->setLayout(hLayout);
	ui->vLayoutCenter->addWidget(groupBox);

	connect(_comboxType, SIGNAL(currentIndexChanged(const QString&)), this, 
		SLOT(UpdataCenterWidgetSlot(const QString&)));
	connect(ui->btnOK, SIGNAL(clicked()), this, SLOT(accept())); //QDialog::Accepted
	connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(reject())); //QDialog::Rejected
	connect(ui->btnShow, SIGNAL(clicked()), this, SLOT(ShowSlot())); 

	connect(this, SIGNAL(SignalShow()), parent, SLOT(ShowSlot())); 

	UpdataCenterWidgetSlot(type);
}

CSetBookMarkTmplDlg::~CSetBookMarkTmplDlg()
{
	delete ui;
}

void CSetBookMarkTmplDlg::SetCenterWidget(QWidget *widget)
{
	ui->vLayoutCenter->addWidget(widget);
}

void CSetBookMarkTmplDlg::ShowSlot()
{
	QWidget *widget = _model->GenDisplayWidget();

	_parent->WidgetShow(widget);

	//�����Ի�������ʾ
	//emit SignalShow();
}

//void CSetBookMarkTmplDlg::OKSlot()
//{
//	accept();
//}
//
//void CSetBookMarkTmplDlg::CancelSlot()
//{
//	reject();
//}
// 

void CSetBookMarkTmplDlg::UpdataCenterWidgetSlot(const QString& text)
{
	if (_model)
	{
		delete _model;
	}
	_model = CModelFactory::Instance().CreateModel(text);
	if(!_model)
	{
		QMessageBox::warning(this, tr("��ʾ"), "û���ҵ���Ӧ��ģ��");
		return;
	}

	_model->Name(this->windowTitle());
	_model->Type(text);

	if (_widgetCenter)
		delete _widgetCenter;
	_widgetCenter = _model->GenParamSetWidget(this);
	this->SetCenterWidget(_widgetCenter);
}