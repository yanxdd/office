#ifndef WORDENGINE_H
#define WORDENGINE_H
#include <QWidget>
#include <QAxObject>
#include <QAxWidget>
//#include <QThread>

class WordEngine : public QWidget
{
	Q_OBJECT
public:
	explicit WordEngine(QWidget *parent = 0);
	WordEngine(const QString& strFile, QWidget *parent = 0);
	~WordEngine();

	bool Open(bool bVisable = false);
	bool Open(const QString& strFile, bool bVisable = false);

	bool Create(bool bVisable = false);
	bool Create(const QString& strFile, bool bVisable = false);

	bool Close();

	bool IsOpen();

	void Save();
	bool SaveAs(const QString& strSaveFile);

	/// <summary>	获取所有的书签. </summary>
	int GetBookmarks(QStringList &listBookMark);

	// 设置标签内容
	bool SetMarks(const QString& strMark, const QString& strContent);
	//插入标题 3
	bool SetTitle(const QString& strMark, const QString& strContent);
	// 批量设置标签
	bool SetBatchMarks(QStringList &itemList, QStringList sometexts);
	// 创建表格
	void InsertTable(int nStart, int nEnd, int row, int column);
	QAxObject *InsertTable(QString sLabel,int row, int column);
	//合并单元格
	void MergeCells(QAxObject *table, int nStartRow,int nStartCol,int nEndRow,int nEndCol);
	//插入图片
	void InsertPic(QString sLabel,const QString& picPath);
	//设置列宽
	void SetColumnWidth(QAxObject *table, int column, int width);
	// 设置表格内容
	void SetCellString(QAxObject *table, int row, int column, const QString& text);
	// 为表格添加行
	void AddTableRow(QAxObject *table, int nRow, int rowCount);
	// 设置内容粗体  isBold控制是否粗体
	void SetCellFontBold(QAxObject *table, int row, int column, bool isBold);
	// 设置文字大小
	void SetCellFontSize(QAxObject *table, int row, int column, int size);
	// 在表格中插入图片
	void InsertCellPic(QAxObject *table, int row,int column,const QString& picPath);

private:
	bool m_bOpened;
	QString m_strFilePath;
	QAxObject *m_wordDocuments;
	QAxObject *m_wordWidget;
	//    QThread *m_thread;


signals:

public slots:

};
#endif // WORDENGINE_H