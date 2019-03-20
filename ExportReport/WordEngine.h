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

	/// <summary>	��ȡ���е���ǩ. </summary>
	int GetBookmarks(QStringList &listBookMark);

	// ���ñ�ǩ����
	bool SetMarks(const QString& strMark, const QString& strContent);
	//������� 3
	bool SetTitle(const QString& strMark, const QString& strContent);
	// �������ñ�ǩ
	bool SetBatchMarks(QStringList &itemList, QStringList sometexts);
	// �������
	void InsertTable(int nStart, int nEnd, int row, int column);
	QAxObject *InsertTable(QString sLabel,int row, int column);
	//�ϲ���Ԫ��
	void MergeCells(QAxObject *table, int nStartRow,int nStartCol,int nEndRow,int nEndCol);
	//����ͼƬ
	void InsertPic(QString sLabel,const QString& picPath);
	//�����п�
	void SetColumnWidth(QAxObject *table, int column, int width);
	// ���ñ������
	void SetCellString(QAxObject *table, int row, int column, const QString& text);
	// Ϊ��������
	void AddTableRow(QAxObject *table, int nRow, int rowCount);
	// �������ݴ���  isBold�����Ƿ����
	void SetCellFontBold(QAxObject *table, int row, int column, bool isBold);
	// �������ִ�С
	void SetCellFontSize(QAxObject *table, int row, int column, int size);
	// �ڱ���в���ͼƬ
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