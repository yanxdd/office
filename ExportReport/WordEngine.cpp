#include "wordengine.h"
#include "qt_windows.h"
//#include <QDebug>
//#include <windows.h>
#include <QMessageBox>
// 
WordEngine::WordEngine(QWidget *parent) :
QWidget(parent),
	m_bOpened(false),
	m_wordDocuments(NULL),
	m_wordWidget(NULL)
{
}

WordEngine::WordEngine(const QString& strFilePath, QWidget *parent):
QWidget(parent),
	m_bOpened(false),
	m_strFilePath(strFilePath),
	m_wordDocuments(NULL),
	m_wordWidget(NULL)
{
}

WordEngine::~WordEngine()
{
	Close();
}

/******************************************************************************
* ������Create
* ���ܣ����ļ�
* ������bVisable �Ƿ���ʾ����
* ����ֵ�� bool
*****************************************************************************/
bool WordEngine::Create(bool bVisable)
{
	//�½�һ��wordӦ�ó���,������Ϊ�ɼ�
	m_wordWidget = new QAxObject();
	bool bFlag = m_wordWidget->setControl( "word.Application" );
	if(!bFlag)
	{
		// ��wps��
		bFlag = m_wordWidget->setControl( "kwps.Application" );
		if(!bFlag)
		{
			return false;
		}
	}
	m_wordWidget->setProperty("Visible", bVisable);
	//��ȡ���еĹ����ĵ�
	QAxObject *document = m_wordWidget->querySubObject("Documents");
	if(!document)
	{
		return false;
	}
	//���ļ�template.dotΪģ���½�һ���ĵ�
	document->dynamicCall("Add(QString)", m_strFilePath);
	//��ȡ��ǰ������ĵ�
	m_wordDocuments = m_wordWidget->querySubObject("ActiveDocument");
	m_bOpened = true;
	return m_bOpened;
}

/******************************************************************************
* ������open
* ���ܣ����ļ�
* ������strFilePath �ļ�·����bVisable �Ƿ���ʾ����
* ����ֵ��bool
*****************************************************************************/
bool WordEngine::Create(const QString& strFilePath, bool bVisable)
{
	m_strFilePath = strFilePath;
	this->Close();
	return Create(bVisable);
}

/******************************************************************************
* ������open
* ���ܣ����ļ�
* ������bVisable �Ƿ���ʾ����
* ����ֵ�� bool
*****************************************************************************/
bool WordEngine::Open(bool bVisable)
{
	//�½�һ��wordӦ�ó���,������Ϊ�ɼ�
	m_wordWidget = new QAxObject();
	bool bFlag = m_wordWidget->setControl( "word.Application" );
	if(!bFlag)
	{
		// ��wps��
// 		bFlag = m_wordWidget->setControl( "kwps.Application" );
// 		if(!bFlag)
// 		{
// 			return false;
// 		}
	}
	m_wordWidget->setProperty("Visible", bVisable);
	//��ȡ���еĹ����ĵ�
	QAxObject *document = m_wordWidget->querySubObject("Documents");
	if(!document)
	{  
		// ��wps��
		//bFlag = m_wordWidget->setControl( "kwps.Application" );
		QMessageBox::warning(this, "����", "û�з�WORDӦ��");
		return false;
	}
	//���ļ�template.dotΪģ���½�һ���ĵ�
	document->dynamicCall("Open(QString)", m_strFilePath);
	//��ȡ��ǰ������ĵ�
	m_wordDocuments = m_wordWidget->querySubObject("ActiveDocument");
	m_bOpened = true;
	return m_bOpened;
}

/******************************************************************************
* ������open
* ���ܣ����ļ�
* ������strFilePath �ļ�·����bVisable �Ƿ���ʾ����
* ����ֵ��bool
*****************************************************************************/
bool WordEngine::Open(const QString& strFilePath, bool bVisable)
{
	m_strFilePath = strFilePath;
	Close();
	return Open(bVisable);
}

/******************************************************************************
* ������close
* ���ܣ��ر��ļ�
* ��������
* ����ֵ��bool
*****************************************************************************/
bool WordEngine::Close()
{
	//    qDebug()<<m_bOpened;
	if (m_bOpened)
	{
		if(m_wordDocuments)
			m_wordDocuments->dynamicCall("Close (bool)", false);//�ر��ı�����  ������
		if(m_wordWidget)
			m_wordWidget->dynamicCall("Quit()");//�˳�word
		if(m_wordDocuments)
			delete m_wordDocuments;
		if(m_wordWidget)
			delete m_wordWidget;
		m_bOpened = false;
	}

	return m_bOpened;
}

/******************************************************************************
* ������isOpen
* ���ܣ���õ�ǰ�Ĵ�״̬
* ��������
* ����ֵ��bool
*****************************************************************************/
bool WordEngine::IsOpen()
{
	return m_bOpened;
}

/******************************************************************************
* ������save
* ���ܣ������ļ�
* ��������
* ����ֵ��void
*****************************************************************************/
void WordEngine::Save()
{
	m_wordDocuments->dynamicCall("Save()");
}

/******************************************************************************
* ������saveAs
* ���ܣ�����ļ�
* ������strSaveFile �ļ�·��
* ����ֵ��void
*****************************************************************************/
bool WordEngine::SaveAs(const QString& strSaveFile)
{
	return m_wordDocuments->dynamicCall("SaveAs (const QString&)",
		strSaveFile).toBool();
}

int WordEngine::GetBookmarks(QStringList &listBookMark)
{
	QAxObject* allBookmarks = NULL;
	int iCount = 0;

	allBookmarks = m_wordDocuments->querySubObject("Bookmarks");
	//ѡ�б�ǩ�����ַ�textg���뵽��ǩλ��
	if(allBookmarks)
	{
		iCount = allBookmarks->property("Count").toInt();
		/*��дģ���е���ǩ*/
		for(int i = iCount; i > 0; --i){
			QAxObject *bookmark = allBookmarks->querySubObject("Item(QVariant)", i);
			listBookMark.append( bookmark->property("Name").toString() );
		}
	}
	return iCount;
}

/******************************************************************************
* ������setMarks
* ���ܣ����ñ�ǩ����
* ������strMark ��ǩ����strContent �ı�
* ����ֵ��bool
*****************************************************************************/
bool WordEngine::SetMarks(const QString& strMark, const QString& strContent)
{
	QAxObject* bookmarkCode = NULL;
	bookmarkCode = m_wordDocuments->querySubObject("Bookmarks(QVariant)", strMark);
	//ѡ�б�ǩ�����ַ�textg���뵽��ǩλ��
	if(bookmarkCode)
	{
		bookmarkCode->dynamicCall("Select(void)");
		bookmarkCode->querySubObject("Range")->setProperty("Text", strContent);
		return true;
	}

	return false;
}

/******************************************************************************
* ������setTitle
* ���ܣ�������� 3
* ������strMark ��ǩ����strContent �ı�
* ����ֵ��bool
*****************************************************************************/
bool WordEngine::SetTitle(const QString& strMark, const QString& strContent)
{
	QAxObject* bookmarkCode = NULL;
	bookmarkCode = m_wordDocuments->querySubObject("Bookmarks(QVariant)", strMark);
	//ѡ�б�ǩ�����ַ�textg���뵽��ǩλ��
	if(bookmarkCode)
	{
		bookmarkCode->dynamicCall("Select(void)");
		bookmarkCode->querySubObject("Range")->setProperty("Text", strContent+"\n");
		bookmarkCode->querySubObject("Range")->dynamicCall("SetStyle(QVariant)", QString::fromLocal8Bit("���� 3"));
		return true;
	}

	return false;
}
/******************************************************************************
* ������setBatchMarks
* ���ܣ��������ñ�ǩ����
* ������itemList ��ǩ���б�sometexts �����б�
* ����ֵ��bool
*****************************************************************************/
bool WordEngine::SetBatchMarks(QStringList &itemList,QStringList sometexts)
{
	QAxObject* allBookmarks = NULL;
	allBookmarks = m_wordDocuments->querySubObject("Bookmarks");
	//ѡ�б�ǩ�����ַ�textg���뵽��ǩλ��
	if(allBookmarks)
	{
		int count = allBookmarks->property("Count").toInt();
		/*��дģ���е���ǩ*/
		for(int i=count;i>0;--i){
			QAxObject *bookmark = allBookmarks->querySubObject("Item(QVariant)", i);
			QString name= bookmark->property("Name").toString();
			int j=0;
			foreach(QString itemName , itemList){
				if (name == itemName) {
					QAxObject *curBM = m_wordDocuments->querySubObject("Bookmarks(QString)", name);
					curBM->querySubObject("Range")->setProperty("Text", sometexts.at(j));
					break;
				}
				j++;
			}
			return true;
		}

		return false;
	}
	return false;
}

/******************************************************************************
* ������insertTable
* ���ܣ��������
* ������nStart ��ʼλ��; nEnd ����λ��; row ��; column ��
* ����ֵ�� void
*****************************************************************************/
void WordEngine::InsertTable(int nStart, int nEnd, int row, int column)
{
	QAxObject* ptst = m_wordDocuments->querySubObject( "Range( Long, Long )", nStart, nEnd );
	QAxObject* pTable = m_wordDocuments->querySubObject( "Tables" );
	QVariantList params;
	params.append(ptst->asVariant());
	params.append(row);
	params.append(column);
	if( pTable )
	{
		pTable->dynamicCall( "Add(QAxObject*, Long ,Long )",params);

	}
}

QAxObject *WordEngine::InsertTable(QString sLabel,int row, int column){
	QAxObject *bookmark = m_wordDocuments->querySubObject("Bookmarks(QVariant)", sLabel);
	if(bookmark)
	{
		bookmark->dynamicCall("Select(void)");
		QAxObject *selection = m_wordWidget->querySubObject("Selection");

		selection->dynamicCall("InsertAfter(QString&)", "\n");
		//selection->dynamicCall("MoveLeft(int)", 1);
		selection->querySubObject("ParagraphFormat")->dynamicCall("Alignment", "wdAlignParagraphCenter");
		//selection->dynamicCall("TypeText(QString&)", "Table Test");//���ñ���

		QAxObject *range = selection->querySubObject("Range");
		QAxObject *tables = m_wordDocuments->querySubObject("Tables");
		QAxObject *table = tables->querySubObject("Add(QVariant,int,int)",range->asVariant(),row,column);

		for(int i=1;i<=6;i++)
		{
			QString str = QString("Borders(-%1)").arg(i);
			QAxObject *borders = table->querySubObject(str.toLocal8Bit().constData());
			borders->dynamicCall("SetLineStyle(int)",1);
		}
		return table;
	}
	return NULL;
}

/******************************************************************************
* ������insertPic
* ���ܣ�����ͼƬ
* ������sLable ��ǩ����picPath ͼƬ·��
* ����ֵ��void
*****************************************************************************/
void WordEngine::InsertPic(QString sLabel,const QString& picPath)
{
	QAxObject *bookmark=m_wordDocuments->querySubObject("Bookmarks(QVariant)",sLabel);
	// ѡ�б�ǩ����ͼƬ���뵽��ǩλ��
	if(bookmark){
		bookmark->dynamicCall("Select(void)");
		QAxObject *selection = m_wordWidget->querySubObject("Selection");
		selection->querySubObject("ParagraphFormat")->dynamicCall("Alignment", "wdAlignParagraphCenter");
		QAxObject *range = bookmark->querySubObject("Range");
		QVariant tmp = range->asVariant();
		QList<QVariant>qList;
		qList<<QVariant(picPath);
		qList<<QVariant(false);
		qList<<QVariant(true);
		qList<<tmp;
		QAxObject *Inlineshapes = m_wordDocuments->querySubObject("InlineShapes");
		Inlineshapes->dynamicCall("AddPicture(const QString&, QVariant, QVariant ,QVariant)",qList);
	}

}

/******************************************************************************
* ������MergeCells
* ���ܣ��ϲ���Ԫ��
* ������table ���; nStartRow ��ʼ��Ԫ������; nStartCol ; nEndRow ; nEndCol
* ����ֵ��void
*****************************************************************************/
void WordEngine::MergeCells(QAxObject *table, int nStartRow,int nStartCol,int nEndRow,int nEndCol)
{
	QAxObject* StartCell =table->querySubObject("Cell(int, int)",nStartRow,nStartCol);
	QAxObject* EndCell = table->querySubObject("Cell(int, int)",nEndRow,nEndCol);
	StartCell->dynamicCall("Merge(LPDISPATCH)",EndCell->asVariant());
}

/******************************************************************************
* ������setColumnWidth
* ���ܣ����ñ���п�
* ������table ���; column ����; width ���
* ����ֵ��void
*****************************************************************************/
void WordEngine::SetColumnWidth(QAxObject *table, int column, int width)
{
	table->querySubObject("Columns(int)", column)->setProperty("Width", width);
}

/******************************************************************************
* ������setCellString
* ���ܣ����ñ������
* ������table ���; row ����; column ����; text �����ı�
* ����ֵ��void
*****************************************************************************/
void WordEngine::SetCellString(QAxObject *table, int row, int column, const QString& text)
{
	if(table)
	{
		table->querySubObject("Cell(int, int)", row, column)
			->querySubObject("Range")
			->dynamicCall("SetText(QString)", text);
	}
}

/******************************************************************************
* ������addTableRow
* ���ܣ�Ϊ��������
* ������table ���; nRow ������; rowCount ���������
* ����ֵ��void
*****************************************************************************/
void WordEngine::AddTableRow(QAxObject *table, int nRow, int rowCount)
{
	QAxObject* rows = table->querySubObject("Rows");

	int Count = rows->dynamicCall("Count").toInt();
	if(0 <= nRow && nRow <=Count)
	{
		for(int i = 0; i < rowCount; ++i)
		{
			QString sPos = QString("Item(%1)").arg(nRow + i);
			QAxObject* row = rows->querySubObject(sPos.toStdString().c_str());
			QVariant param = row->asVariant();
			rows->dynamicCall("Add(Variant)", param);
		}
	}
}


/******************************************************************************
* ������setCellFontBold
* ���ܣ��������ݴ���  isBold�����Ƿ����
* ������table ���; row ������; column ����; isBold �Ƿ�Ӵ�
* ����ֵ��void
*****************************************************************************/
void WordEngine::SetCellFontBold(QAxObject *table, int row, int column, bool isBold)
{
	table->querySubObject("Cell(int, int)",row,column)->querySubObject("Range")
		->dynamicCall("SetBold(int)", isBold);
}

/******************************************************************************
* ������setCellFontSize
* ���ܣ��������ִ�С
* ������table ���; row ������; column ����; size �����С
* ����ֵ��void
*****************************************************************************/
void WordEngine::SetCellFontSize(QAxObject *table, int row, int column, int size)
{
	table->querySubObject("Cell(int, int)",row,column)->querySubObject("Range")
		->querySubObject("Font")->setProperty("Size", size);
}

/******************************************************************************
* ������insertCellPic
* ���ܣ��ڱ���в���ͼƬ
* ������table ���; row ������; column ����; picPath ͼƬ·��
* ����ֵ��void
*****************************************************************************/
void WordEngine::InsertCellPic(QAxObject *table, int row, int column,
	const QString& picPath)
{
	QAxObject* range = table->querySubObject("Cell(int, int)", row, column)
		->querySubObject("Range");
	range->querySubObject("InlineShapes")
		->dynamicCall("AddPicture(const QString&)", picPath);
}