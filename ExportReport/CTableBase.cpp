#include "CTableBase.h"
#include "ui_ctablebase.h"

CTableBase::CTableBase(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::CTableBase();
	ui->setupUi(this);
}

CTableBase::~CTableBase()
{
	delete ui;
}

