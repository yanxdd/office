#ifndef CSETBOOKMARKTMPLDLG_H
#define CSETBOOKMARKTMPLDLG_H

#include <QDialog>
#include <QComboBox>

#include "CModelFactory.h"
#include "CModelBase.h"
#include "CDataBase.h"

namespace Ui {class CSetBookMarkTmplDlg;};
class ExportReport;

class CSetBookMarkTmplDlg : public QDialog
{
	Q_OBJECT

signals:
	void SignalShow();

public slots:
// 	void OKSlot();
 	void ShowSlot();

 	void UpdataCenterWidgetSlot(const QString& text);

public:
	CSetBookMarkTmplDlg(CModelBase *model, QString &strType, CDataBase *db, ExportReport *parent = 0);
	~CSetBookMarkTmplDlg();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	提供给外部接口，用来设置中心显示的内容. </summary>
	///
	/// <remarks>	user, 2019/3/9. </remarks>
	///
	/// <param name="widget">	[in,out] If non-null, the widget. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void SetCenterWidget(QWidget *widget);

	CModelBase * Model() const { return _model; }
	void Model(CModelBase * val) { _model = val; }
	CModelBaseWidget * WidgetCenter() const { return _widgetCenter; }
	void WidgetCenter(CModelBaseWidget * val) { _widgetCenter = val; }

private:
	Ui::CSetBookMarkTmplDlg *ui;

	QComboBox *_comboxType;

	CModelBase *_model;

	CModelBaseWidget *_widgetCenter;
	/// <summary> 标签类型 </summary>
	//QString _strType;
	// 
	CDataBase *_db;

	ExportReport *_parent;
};

#endif // CSETBOOKMARKTMPLDLG_H
