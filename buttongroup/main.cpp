
#include <QApplication>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QVector>
#include "mybuttongroup.h"
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QMainWindow *window = new QMainWindow();
	QVector<QPushButton*> btn;

	window->setWindowTitle(QString::fromUtf8("MainWindow"));
	window->resize(250, 250);

	QWidget *centralWidget = new QWidget(window);
	centralWidget->setFixedSize(400,300);

	//Create QPushButtons
	QPushButton* button1 = new QPushButton("Button 1" , centralWidget);
	QPushButton* button2 = new QPushButton("Button 2" , centralWidget);
	QPushButton* button3 = new QPushButton("Button 3" , centralWidget);
	QPushButton* button4 = new QPushButton("Button 4" , centralWidget);

	button1->setCheckable(true);
	button2->setCheckable(true);
	button3->setCheckable(true);
	button4->setCheckable(true);
	btn.append(button1);
	btn.append(button2);
	btn.append(button3);
	btn.append(button4);



	QHBoxLayout* layout = new QHBoxLayout(centralWidget);
	for(int i=0;i<btn.count();++i)
	{
		layout->addWidget(btn.at(i));
	}

	//Create QButonGroup and add Buttons here
	//Adding Buttons into QButtonGroup does not change anything visually
	//QButtonGroup is just a logical grouping
	QButtonGroup* group = new MyButtonGroup(centralWidget);
	for(int i=0;i<btn.count();++i)
	{
		group->addButton(btn.at(i));
	}
	group->setExclusive(true);

	window->setCentralWidget(centralWidget);
	window->show();

	return app.exec();

}
