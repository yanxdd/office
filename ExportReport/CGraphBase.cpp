#include "CGraphBase.h"
#include "ui_cgraphbase.h"

CGraphBase::CGraphBase(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::CGraphBase();
	ui->setupUi(this);
}

CGraphBase::~CGraphBase()
{
	delete ui;
}

