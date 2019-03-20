#ifndef CTABLEBASE_H
#define CTABLEBASE_H

#include <QWidget>
namespace Ui {class CTableBase;};

class CTableBase : public QWidget
{
	Q_OBJECT

public:
	CTableBase(QWidget *parent = 0);
	~CTableBase();

private:
	Ui::CTableBase *ui;
};

#endif // CTABLEBASE_H
