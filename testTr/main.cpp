#include "testTrDlg.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char ** argv)
{
	QApplication app(argc, argv);

	testTrDlg * dlg = new testTrDlg;

	dlg->show();
	
	return app.exec();
}