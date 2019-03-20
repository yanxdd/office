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
#include <QDomDocument> //也可以include <QDomDocument>
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

	//mainwindow必须要有个centralWidget  用QDialog就不用了
	QWidget *wndCenter = new QWidget();
	this->setCentralWidget(wndCenter);
	
	//初始化菜单栏
	QMenuBar* mBar = this->menuBar();//QMainWindow自带一个菜单栏

	//报表模块
	QMenu* menuTmpl = new QMenu("报表模板");//新建菜单
	QAction* actOpen = new QAction("打开", menuTmpl);
	QAction* actNew = new QAction("新建", menuTmpl);//新建菜单项
	QAction* actSave = new QAction("保存", menuTmpl);
	QAction* actExit = new QAction("退出", menuTmpl);
	menuTmpl->addAction(actOpen);//向菜单上添加菜单项
	menuTmpl->addAction(actNew);
	menuTmpl->addAction(actSave);
	menuTmpl->addSeparator();
	menuTmpl->addAction(actExit);

	//内容模块
	QMenu* menuTmpl2 = new QMenu("图表模板");
	QMenu* menuGraph = new QMenu("图", menuTmpl2);
	QMenu* menuTable = new QMenu("表", menuTmpl2);
	QAction* actGraph1 = new QAction("图1", menuGraph);
	QAction* actGraph2 = new QAction("图2", menuGraph);
	QAction* actTable2 = new QAction("表2", menuTable);
	menuGraph->addAction(actGraph1);
	QAction* actTable1 = new QAction("表1", menuTable);
	menuGraph->addAction(actGraph2);
	menuTable->addAction(actTable1);
	menuTable->addAction(actTable2);
	menuTmpl2->addMenu(menuGraph);//向菜单上添加子菜单
	menuTmpl2->addMenu(menuTable);//向菜单上添加子菜单

	mBar->addMenu(menuTmpl);
	mBar->addMenu(menuTmpl2);

	//初始化工具栏
//	QToolBar* tBar = new QToolBar();
//	this->addToolBar(tBar);//添加一个工具栏
// 	tBar->addAction(act1);
// 	tBar->addSeparator();
// 	tBar->addAction(act4);

	// 左上区域
	QLabel* labelTmplList = new QLabel("标签列表");
	labelTmplList->setAlignment(Qt::AlignHCenter);
	_tabTmpl = new QTableWidget();
	_tabTmpl->setColumnCount(3);
	//设置每一列的标题
	QStringList header;
	header << tr("标签名") << tr("类型") << tr("数据源");
	_tabTmpl->setHorizontalHeaderLabels(header);

	//QTableWidgetItem* hItem1 = new QTableWidgetItem("ID");//QIcon("./Icon/1.png"),"列表项1");
	//_tabTmpl->setHorizontalHeaderItem(0,hItem1); //表头第1列
	//设置表头字体加粗
	QFont font = _tabTmpl->horizontalHeader()->font();
	font.setBold(true);
	_tabTmpl->horizontalHeader()->setFont(font);  
	_tabTmpl->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色

	_tabTmpl->setSelectionBehavior(QAbstractItemView::SelectRows);  //设置选择行为时每次选择一行
	_tabTmpl->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑

	_tabTmpl->insertRow(0);
	_tabTmpl->setItem(0, 0, new QTableWidgetItem("标签1"));
	_tabTmpl->setItem(0, 1, new QTableWidgetItem("单色折线图"));
	_tabTmpl->setItem(0, 2, new QTableWidgetItem("否"));
	_tabTmpl->insertRow(1);
	_tabTmpl->setItem(1, 0, new QTableWidgetItem("标签2"));
	_tabTmpl->setItem(1, 1, new QTableWidgetItem("表1"));
	_tabTmpl->setItem(1, 2, new QTableWidgetItem("否"));

	QVBoxLayout* vLayout1 = new QVBoxLayout();
	vLayout1->addWidget(labelTmplList);
	vLayout1->addWidget(_tabTmpl);

	// 右上区域
	QVBoxLayout* vLayout2 = new QVBoxLayout();

	QHBoxLayout *hLayout21 = new QHBoxLayout();
	QLabel* labelTmplPath = new QLabel("模板文件:");
	_lineTmplPath = new QLineEdit;
	_lineTmplPath->setReadOnly(true);
	//QPushButton* btnBrowse = new QPushButton("浏览");
	hLayout21->addWidget(labelTmplPath);
	hLayout21->addWidget(_lineTmplPath);
	//hLayout21->addWidget(btnBrowse);

	QHBoxLayout *hLayout22 = new QHBoxLayout();
	QLabel* labelStartTime = new QLabel("开始时间:");
	_tmStart = new QDateTimeEdit();
	//QTimeEdit *tmStart = new QTimeEdit();
	hLayout22->addWidget(labelStartTime);
	hLayout22->addWidget(_tmStart);
	hLayout22->addStretch();

	QHBoxLayout *hLayout23 = new QHBoxLayout();
	QLabel* labelEndTime = new QLabel("结束时间:");
	_tmEnd = new QDateTimeEdit();
	hLayout23->addWidget(labelEndTime);
	hLayout23->addWidget(_tmEnd);
	hLayout23->addStretch();

	QHBoxLayout *hLayout29 = new QHBoxLayout();
	QPushButton* btnShow = new QPushButton("显示内容");
	QPushButton* btnSaveTmpl = new QPushButton("保存模板");
	QPushButton* btnExpt = new QPushButton("导出报表");
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

	// 上半区域
	QHBoxLayout *hLayout1 = new QHBoxLayout();
	hLayout1->addLayout(vLayout1);
	hLayout1->addLayout(vLayout2);
	
	// 下半区域
	QHBoxLayout *hLayout2 = new QHBoxLayout();
	_widgetShow = new QTextEdit();
	((QTextEdit *)_widgetShow)->setReadOnly(true);
	//wVariation->setMinimumHeight(100);
	hLayout2->addWidget(_widgetShow);

	QVBoxLayout* vLayout = new QVBoxLayout(wndCenter);
	vLayout->addLayout(hLayout1);
	vLayout->addLayout(hLayout2);


	//this->setCentralWidget(wndCenter);//设置中央区域要显示的Widget
	//this->resize(550,350);

	//初始化状态栏
	QStatusBar* sBar = this->statusBar();//QMainwindow自带一个状态栏

	QLabel* sLabel = new QLabel("北京昆宇蓝程科技有限公司");
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
	QString sFile = "报表模板.dotx";
	//新建一个word应用程序

	QAxObject *m_pWord = new QAxObject();
	bool bFlag = m_pWord->setControl( "word.Application" );
	if(!bFlag)
	{
		return;
	}
	m_pWord->setProperty("Visible", true);
	//获取所有的工作文档
	QAxObject *document = m_pWord->querySubObject("Documents");
	if(!document)
	{
		return;
	}
	//以文件template.dot为模版新建一个文档
	document->dynamicCall("Add(QString)", sFile);
	//获取当前激活的文档
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
	//定义文件对话框类
	QFileDialog *fileDialog = new QFileDialog(this);
	//定义文件对话框标题
	fileDialog->setWindowTitle(tr("打开WORD模板"));
	//设置默认文件路径
	fileDialog->setDirectory(".");
	//设置文件过滤器
	fileDialog->setNameFilter(tr("Word(*.dotx *.dot)"));
	//设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFile
	fileDialog->setFileMode(QFileDialog::ExistingFile);
	//设置视图模式
	fileDialog->setViewMode(QFileDialog::Detail);
	//打印所有选择的文件的路径
	QStringList fileNames;
	if(fileDialog->exec())
	{
		fileNames = fileDialog->selectedFiles();
	}
	if( 1 != fileNames.size()) 
		return;
	
	//读取模板中所有标签
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
		//QString strId = QString::number(i+1);//QString的静态方法，将数字转换成字符串
		//QTableWidgetItem* item1 = new QTableWidgetItem(strId);
		//_tabTmpl->setItem(i, 0, item1);
		_tabTmpl->setItem(i, 0, new QTableWidgetItem(strBookMark));
		_tabTmpl->setItem(i, 1, new QTableWidgetItem(""));
		_tabTmpl->setItem(i++, 2, new QTableWidgetItem("否"));
	}
}

void ExportReport::SaveTmplSlot()
{
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("保存报表配置"),
		"",
		tr("Config Files (*.xml)"));

	if (fileName.isNull())
		return;

	//每行关联数据为widget类,如果为NULL,说明没有修改或者添加,如果有值,取里面的值,保存到xml文件
	QDomDocument doc;
	//写入xml头部
	QDomProcessingInstruction instruction; //添加处理命令
	instruction=doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
	doc.appendChild(instruction);
	//添加根节点
 	QDomElement root=doc.createElement("TemplateConfig");
 	doc.appendChild(root);

	//添加节点   word模板路径
	QDomElement elmtPath = doc.createElement("TemplateFile");
	QDomText txtPath = doc.createTextNode(_lineTmplPath->text());
	elmtPath.appendChild(txtPath);
	root.appendChild(elmtPath);
		
	// 遍历标签，生成XML节点
	int iCount = _tabTmpl->rowCount();
	CModelBase *model;
	bool bAllSuccess = true;
	QString strLog = "以下标签保存失败，详情请查看日志文件。\n";
	for (int i=0; i < iCount; ++i)
	{
		model = _tabTmpl->item(i, 0)->data(Qt::UserRole).value<CModelBase*>();
		if(!model)
		{
			//记录导出失败
			bAllSuccess = false;
			qWarning() << _tabTmpl->item(i, 0)->text() + "XML节点保存失败";
			strLog += _tabTmpl->item(i, 0)->text() + "\n";
			continue;
		}

		QDomElement node = doc.createElement("label");		//创建子元素
		model->GenXmlModelNode(doc, node);
		root.appendChild(node);
	}
	
	//打开或创建文件
	QFile fXml(fileName);								//相对路径、绝对路径、资源路径都可以
	if(!fXml.open(QFile::WriteOnly | QFile::Truncate)) //可以用QIODevice
		return;

	//输出到文件
	QTextStream out_stream(&fXml);
	doc.save(out_stream, 4); //缩进4格
	fXml.close();

	if (!bAllSuccess)
		QMessageBox::warning(this, tr("提示"), strLog);

	return;
}

void ExportReport::ExitAppSlot()
{

}

void ExportReport::ShowSlot()
{
	if( !Db()->Init() )
	{
		QMessageBox::critical(this, "无法打开数据库", "无法创建数据库连接！", QMessageBox::Cancel);
		return;
	}

	//以下为测试代码
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
	((QTextEdit *)_widgetShow)->setText(current_date);
}

void ExportReport::ExportWordSlot()
{
	QString sFile = "报表模板.dotx";
	//新建一个word应用程序

	QAxObject *m_pWord = new QAxObject();
	bool bFlag = m_pWord->setControl( "word.Application" );
	if(!bFlag)
	{
		return;
	}
	m_pWord->setProperty("Visible", true);
	//获取所有的工作文档
	QAxObject *document = m_pWord->querySubObject("Documents");
	if(!document)
	{
		return;
	}
	//以文件template.dot为模版新建一个文档
	document->dynamicCall("Add(QString)", sFile);
	//获取当前激活的文档
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

	// 显示书签参数设置对话框

	// 根据这一列的类型，使用类工厂生成相应的widget类，并显示, 把widget与这一列关联。
	QString strName = _tabTmpl->item(item->row(), 0)->text();
	QString strType = _tabTmpl->item(item->row(), 1)->text();

	CModelBase *model = _tabTmpl->item(item->row(), 0)->data(Qt::UserRole).value<CModelBase*>();

	CSetBookMarkTmplDlg dlg(model, strType, Db(),this);
	dlg.setWindowTitle(strName);

	if( QDialog::Rejected == dlg.exec() )
		return;

	// 保存界面上填写的数据
	
	dlg.WidgetCenter()->SaveData();

	_tabTmpl->item(item->row(), 1)->setText(dlg.Model()->Type());

	// 把model类与item这行的第1列关联
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
