#include "mybuttongroup.h"
#include <QDebug>

MyButtonGroup::MyButtonGroup(QWidget *parent)
{
	this->setParent(parent);

	//connect buttonClicked signal to our custom slot 'buttonClick'
	connect(this , SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(buttonClick(QAbstractButton*)));
}

MyButtonGroup::~MyButtonGroup(){}

void MyButtonGroup::buttonClick(QAbstractButton *button)
{
    QMessageBox* box = new QMessageBox();
    box->setWindowTitle("Hello");
    box->setText("You clicked " + button->text());
    if(button->text()=="Button 1")
    {
        //TODO
        qDebug()<<"B1"<<endl;
    }
    else if(button->text()=="Button 2")
    {
        //TODO
        qDebug()<<"B2"<<endl;
    }
    else if(button->text()=="Button 3")
    {
        //TODO
        qDebug()<<"B3"<<endl;
    }
    else
    {
        //TODO
        qDebug()<<"B4"<<endl;
    }
    box->show();
}
