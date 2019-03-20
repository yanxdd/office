#include "ExportReport.h"

#include <QDebug>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidgetItem>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMenu>
#include <QtWidgets/QAction>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QDomDocument> //Ҳ����include <QDomDocument>
#include <QDateTime>
#include <QMessageBox>

#include "CSetBookMarkTmplDlg.h"
#include "CModelBase.h"
#include "CModelFactory.h"

Q_DECLARE_METATYPE(CModelBase*)

ExportReport::ExportReport(QWidget *parent)
	: QMainWindow(parent)
{
	//ui.setupUi(this);

	//mainwindow����Ҫ�и�centralWidget  ��QDialog�Ͳ�����
	QWidget *wndCenter = new QWidget();
	this->setCentralWidget(wndCenter);
	
	//��ʼ���˵���
	QMenuBar* mBar = this->menuBar();//QMainWindow�Դ�һ���˵���

	//����ģ��
	QMenu* menuTmpl = new QMenu("����ģ��");//�½��˵�
	QAction* actOpen = new QAction("��", menuTmpl);
	QAction* actNew = new QAction("�½�", menuTmpl);//�½��˵���
	QAction* actSave = new QAction("����", menuTmpl);
	QAction* actExit = new QAction("�˳�", menuTmpl);
	menuTmpl->addAction(actOpen);//��˵�����Ӳ˵���
	menuTmpl->addAction(actNew);
	menuTmpl->addAction(actSave);
	menuTmpl->addSeparator();
	menuTmpl->addAction(actExit);

	//����ģ��
	QMenu* menuTmpl2 = new QMenu("ͼ��ģ��");
	QMenu* menuGraph = new QMenu("ͼ", menuTmpl2);
	QMenu* menuTable = new QMenu("��", menuTmpl2);
	QAction* actGraph1 = new QAction("ͼ1", menuGraph);
	QAction* actGraph2 = new QAction("ͼ2", menuGraph);
	QAction* actTable2 = new QAction("��2", menuTable);
	menuGraph->addAction(actGraph1);
	QAction* actTable1 = new QAction("��1", menuTable);
	menuGraph->addAction(actGraph2);
	menuTable->addAction(actTable1);
	menuTable->addAction(actTable2);
	menuTmpl2->addMenu(menuGraph);//��˵�������Ӳ˵�
	menuTmpl2->addMenu(menuTable);//��˵�������Ӳ˵�

	mBar->addMenu(menuTmpl);
	mBar->addMenu(menuTmpl2);

	//��ʼ��������
//	QToolBar* tBar = new QToolBar();
//	this->addToolBar(tBar);//���һ��������
// 	tBar->addAction(act1);
// 	tBar->addSeparator();
// 	tBar->addAction(act4);

	// ��������
	QLabel* labelTmplList = new QLabel("��ǩ�б�");
	labelTmplList->setAlignment(Qt::AlignHCenter);
	_tabTmpl = new QTableWidget();
	_tabTmpl->setColumnCount(3);
	//����ÿһ�еı���
	QStringList header;
	header << tr("��ǩ��") << tr("����") << tr("����Դ");
	_tabTmpl->setHorizontalHeaderLabels(header);

	//QTableWidgetItem* hItem1 = new QTableWidgetItem("ID");//QIcon("./Icon/1.png"),"�б���1");
	//_tabTmpl->setHorizontalHeaderItem(0,hItem1); //��ͷ��1��
	//���ñ�ͷ����Ӵ�
	QFont font = _tabTmpl->horizontalHeader()->font();
	font.setBold(true);
	_tabTmpl->horizontalHeader()->setFont(font);  
	_tabTmpl->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //���ñ�ͷ����ɫ

	_tabTmpl->setSelectionBehavior(QAbstractItemView::SelectRows);  //����ѡ����Ϊʱÿ��ѡ��һ��
	_tabTmpl->setEditTriggers(QAbstractItemView::NoEditTriggers); //���ò��ɱ༭

	_tabTmpl->insertRow(0);
	_tabTmpl->setItem(0, 0, new QTableWidgetItem("��ǩ1"));
	_tabTmpl->setItem(0, 1, new QTableWidgetItem("��ɫ����ͼ"));
	_tabTmpl->setItem(0, 2, new QTableWidgetItem("��"));
	_tabTmpl->insertRow(1);
	_tabTmpl->setItem(1, 0, new QTableWidgetItem("��ǩ2"));
	_tabTmpl->setItem(1, 1, new QTableWidgetItem("��1"));
	_tabTmpl->setItem(1, 2, new QTableWidgetItem("��"));

	QVBoxLayout* vLayout1 = new QVBoxLayout();
	vLayout1->addWidget(labelTmplList);
	vLayout1->addWidget(_tabTmpl);

	// ��������
	QVBoxLayout* vLayout2 = new QVBoxLayout();

	QHBoxLayout *hLayout21 = new QHBoxLayout();
	QLabel* labelTmplPath = new QLabel("ģ���ļ�:");
	_lineTmplPath = new QLineEdit;
	_lineTmplPath->setReadOnly(true);
	//QPushButton* btnBrowse = new QPushButton("���");
	hLayout21->addWidget(labelTmplPath);
	hLayout21->addWidget(_lineTmplPath);
	//hLayout21->addWidget(btnBrowse);

	QHBoxLayout *hLayout22 = new QHBoxLayout();
	QLabel* labelStartTime = new QLabel("��ʼʱ��:");
	_tmStart = new QDateTimeEdit();
	//QTimeEdit *tmStart = new QTimeEdit();
	hLayout22->addWidget(labelStartTime);
	hLayout22->addWidget(_tmStart);
	hLayout22->addStretch();

	QHBoxLayout *hLayout23 = new QHBoxLayout();
	QLabel* labelEndTime = new QLabel("����ʱ��:");
	_tmEnd = new QDateTimeEdit();
	hLayout23->addWidget(labelEndTime);
	hLayout23->addWidget(_tmEnd);
	hLayout23->addStretch();

	QHBoxLayout *hLayout29 = new QHBoxLayout();
	QPushButton* btnShow = new QPushButton("��ʾ����");
	QPushButton* btnSaveTmpl = new QPushButton("����ģ��");
	QPushButton* btnExpt = new QPushButton("��������");
	hLayout29->addWidget(btnShow);
	hLayout29->addWidget(btnSaveTmpl);
	hLayout29->addWidget(btnExpt);

	vLayout2->addStretch();
	vLayout2->addLayout(hLayout21);
	vLayout2->addLayout(hLayout22);
	vLayout2->addLayout(hLayout23);
	vLayout2->addStretch();
	vLayout2->addLayout(hLayout29);
	vLayout2->addStretch();

	// �ϰ�����
	QHBoxLayout *hLayout1 = new QHBoxLayout();
	hLayout1->addLayout(vLayout1);
	hLayout1->addLayout(vLayout2);
	
	// �°�����
	QHBoxLayout *hLayout2 = new QHBoxLayout();
	_widgetShow = new QTextEdit();
	((QTextEdit *)_widgetShow)->setReadOnly(true);
	//wVariation->setMinimumHeight(100);
	hLayout2->addWidget(_widgetShow);

	QVBoxLayout* vLayout = new QVBoxLayout(wndCenter);
	vLayout->addLayout(hLayout1);
	vLayout->addLayout(hLayout2);


	//this->setCentralWidget(wndCenter);//������������Ҫ��ʾ��Widget
	//this->resize(550,350);

	//��ʼ��״̬��
	QStatusBar* sBar = this->statusBar();//QMainwindow�Դ�һ��״̬��

	QLabel* sLabel = new QLabel("�����������̿Ƽ����޹�˾");
	sBar->addWidget(sLabel,1);

	connect(actOpen, SIGNAL(triggered()), this, SLOT(OpenTmplSlot()));
	connect(actNew,  SIGNAL(triggered()), this, SLOT(NewTmplSlot()));
	connect(actSave, SIGNAL(triggered()), this, SLOT(SaveTmplSlot()));
	connect(actExit, SIGNAL(triggered()), this, SLOT(ExitAppSlot()));
	connect(btnExpt, SIGNAL(clicked()), this, SLOT(ExportWordSlot()));
	connect(btnShow, SIGNAL(clicked()), this, SLOT(ShowSlot()));
	connect(btnSaveTmpl, SIGNAL(clicked()), this, SLOT(SaveTmplSlot()));
	connect(_tabTmpl, SIGNAL(itemDoubleClicked(QTableWidgetItem *)), this, SLOT(SetBookMarkSlot(QTableWidgetItem *)));
	
	_db = new CDataBase(tr("mysql"), tr("localhost"), tr("test"), tr("root"), tr("123456"));
}

ExportReport::~ExportReport()
{
	if(_db)
		delete _db;
}

void ExportReport::OpenTmplSlot()
{
	QString sFile = "����ģ��.dotx";
	//�½�һ��wordӦ�ó���

	QAxObject *m_pWord = new QAxObject();
	bool bFlag = m_pWord->setControl( "word.Application" );
	if(!bFlag)
	{
		return;
	}
	m_pWord->setProperty("Visible", true);
	//��ȡ���еĹ����ĵ�
	QAxObject *document = m_pWord->querySubObject("Documents");
	if(!document)
	{
		return;
	}
	//���ļ�template.dotΪģ���½�һ���ĵ�
	document->dynamicCall("Add(QString)", sFile);
	//��ȡ��ǰ������ĵ�
	QAxObject *m_pWorkDocument = m_pWord->querySubObject("ActiveDocument");
	bool m_bIsOpen;
	if(m_pWorkDocument)
		m_bIsOpen = true;
	else
		m_bIsOpen = false;

	return;
}

void ExportReport::NewTmplSlot()
{
	int i = 0;
	//�����ļ��Ի�����
	QFileDialog *fileDialog = new QFileDialog(this);
	//�����ļ��Ի������
	fileDialog->setWindowTitle(tr("��WORDģ��"));
	//����Ĭ���ļ�·��
	fileDialog->setDirectory(".");
	//�����ļ�������
	fileDialog->setNameFilter(tr("Word(*.dotx *.dot)"));
	//���ÿ���ѡ�����ļ�,Ĭ��Ϊֻ��ѡ��һ���ļ�QFileDialog::ExistingFile
	fileDialog->setFileMode(QFileDialog::ExistingFile);
	//������ͼģʽ
	fileDialog->setViewMode(QFileDialog::Detail);
	//��ӡ����ѡ����ļ���·��
	QStringList fileNames;
	if(fileDialog->exec())
	{
		fileNames = fileDialog->selectedFiles();
	}
	if( 1 != fileNames.size()) 
		return;
	
	//��ȡģ�������б�ǩ
	WordEngine word;
	QStringList listBookMarks;
	word.Open(fileNames[0]);
	int iCount = word.GetBookmarks(listBookMarks);
	word.Close();
	if( 0 == iCount)
	{
		return;
	}

	this->ClearAll();
	_lineTmplPath->setText(fileNames[0]);

	foreach (QString strBookMark, listBookMarks)
	{
		//i = _tabTmpl->rowCount();
		_tabTmpl->insertRow(i);
		//QString strId = QString::number(i+1);//QString�ľ�̬������������ת�����ַ���
		//QTableWidgetItem* item1 = new QTableWidgetItem(strId);
		//_tabTmpl->setItem(i, 0, item1);
		_tabTmpl->setItem(i, 0, new QTableWidgetItem(strBookMark));
		_tabTmpl->setItem(i, 1, new QTableWidgetItem(""));
		_tabTmpl->setItem(i++, 2, new QTableWidgetItem("��"));
	}
}

void ExportReport::SaveTmplSlot()
{
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("���汨������"),
		"",
		tr("Config Files (*.xml)"));

	if (fileName.isNull())
		return;

	//ÿ�й�������Ϊwidget��,���ΪNULL,˵��û���޸Ļ������,�����ֵ,ȡ�����ֵ,���浽xml�ļ�
	QDomDocument doc;
	//д��xmlͷ��
	QDomProcessingInstruction instruction; //��Ӵ�������
	instruction=doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
	doc.appendChild(instruction);
	//��Ӹ��ڵ�
 	QDomElement root=doc.createElement("TemplateConfig");
 	doc.appendChild(root);

	//��ӽڵ�   wordģ��·��
	QDomElement elmtPath = doc.createElement("TemplateFile");
	QDomText txtPath = doc.createTextNode(_lineTmplPath->text());
	elmtPath.appendChild(txtPath);
	root.appendChild(elmtPath);
		
	// ������ǩ������XML�ڵ�
	int iCount = _tabTmpl->rowCount();
	CModelBase *model;
	bool bAllSuccess = true;
	QString strLog = "���±�ǩ����ʧ�ܣ�������鿴��־�ļ���\n";
	for (int i=0; i < iCount; ++i)
	{
		model = _tabTmpl->item(i, 0)->data(Qt::UserRole).value<CModelBase*>();
		if(!model)
		{
			//��¼����ʧ��
			bAllSuccess = false;
			qWarning() << _tabTmpl->item(i, 0)->text() + "XML�ڵ㱣��ʧ��";
			strLog += _tabTmpl->item(i, 0)->text() + "\n";
			continue;
		}

		QDomElement node = doc.createElement("label");		//������Ԫ��
		model->GenXmlModelNode(doc, node);
		root.appendChild(node);
	}
	
	//�򿪻򴴽��ļ�
	QFile fXml(fileName);								//���·��������·������Դ·��������
	if(!fXml.open(QFile::WriteOnly | QFile::Truncate)) //������QIODevice
		return;

	//������ļ�
	QTextStream out_stream(&fXml);
	doc.save(out_stream, 4); //����4��
	fXml.close();

	if (!bAllSuccess)
		QMessageBox::warning(this, tr("��ʾ"), strLog);

	return;
}

void ExportReport::ExitAppSlot()
{

}

void ExportReport::ShowSlot()
{
	if( !Db()->Init() )
	{
		QMessageBox::critical(this, "�޷������ݿ�", "�޷��������ݿ����ӣ�", QMessageBox::Cancel);
		return;
	}

	//����Ϊ���Դ���
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
	((QTextEdit *)_widgetShow)->setText(current_date);
}

void ExportReport::ExportWordSlot()
{
	QString sFile = "����ģ��.dotx";
	//�½�һ��wordӦ�ó���

	QAxObject *m_pWord = new QAxObject();
	bool bFlag = m_pWord->setControl( "word.Application" );
	if(!bFlag)
	{
		return;
	}
	m_pWord->setProperty("Visible", true);
	//��ȡ���еĹ����ĵ�
	QAxObject *document = m_pWord->querySubObject("Documents");
	if(!document)
	{
		return;
	}
	//���ļ�template.dotΪģ���½�һ���ĵ�
	document->dynamicCall("Add(QString)", sFile);
	//��ȡ��ǰ������ĵ�
	QAxObject *m_pWorkDocument = m_pWord->querySubObject("ActiveDocument");
	bool m_bIsOpen;
	if(m_pWorkDocument)
		m_bIsOpen = true;
	else
		m_bIsOpen = false;

	return;
}

void ExportReport::SetBookMarkSlot(QTableWidgetItem *item)
{

	// ��ʾ��ǩ�������öԻ���

	// ������һ�е����ͣ�ʹ���๤��������Ӧ��widget�࣬����ʾ, ��widget����һ�й�����
	QString strName = _tabTmpl->item(item->row(), 0)->text();
	QString strType = _tabTmpl->item(item->row(), 1)->text();

	CModelBase *model = _tabTmpl->item(item->row(), 0)->data(Qt::UserRole).value<CModelBase*>();

	CSetBookMarkTmplDlg dlg(model, strType, Db(),this);
	dlg.setWindowTitle(strName);

	if( QDialog::Rejected == dlg.exec() )
		return;

	// �����������д������
	
	dlg.WidgetCenter()->SaveData();

	_tabTmpl->item(item->row(), 1)->setText(dlg.Model()->Type());

	// ��model����item���еĵ�1�й���
	_tabTmpl->item(item->row(), 0)->setData(Qt::UserRole, QVariant::fromValue(dlg.Model()));

	return;
}

void ExportReport::ClearAll()
{
	int iCount = _tabTmpl->rowCount();
	for (; iCount > 0; --iCount)
	{
		CModelBase *model = _tabTmpl->item(iCount-1, 0)->data(Qt::UserRole).value<CModelBase*>();
		if (model)
			delete model;
		_tabTmpl->removeRow(iCount-1);
	}
}
