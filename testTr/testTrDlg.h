#include "ui_testTrDlg.h"
#include <QDialog>
#include <QWidget>
#include <QTranslator>

class testTrDlg : public QDialog, Ui::Dialog
{
	Q_OBJECT
public:
	testTrDlg(QWidget * parent = 0);
	~testTrDlg();

public slots:
	void english();
	void chinese();
	void ILoveMyFamily();
	void testTr();

private:
	QTranslator  * translator;
};
