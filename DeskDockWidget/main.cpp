#include "deskdockwidget.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	DeskDockWidget *w = new DeskDockWidget(DeskDockWidget::TOP);

	w->show();

	return a.exec();
}
