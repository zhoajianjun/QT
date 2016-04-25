#ifndef MYBUTTONGROUP_H
#define MYBUTTONGROUP_H

#include <QButtonGroup>
#include <QPushButton>
#include <QMessageBox>
#include <QButtonGroup>
//Derived Class from QButtonGroup
class MyButtonGroup: public QButtonGroup
{
  Q_OBJECT
  public:
    MyButtonGroup(QWidget* parent);
    ~ MyButtonGroup();

  public slots:
    //Slot that is called when one of buttons in QButtonGroup is clicked
    void buttonClick(QAbstractButton* button);

};
#endif
