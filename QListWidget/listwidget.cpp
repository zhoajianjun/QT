#include "listwidget.h"
#include <QHBoxLayout>

ListWidget::ListWidget()
{
        label = new QLabel;
        label->setFixedWidth(70);
        list = new QListWidget;
        list->addItem(new QListWidgetItem(QIcon(":/images/line.PNG"), tr("Line")));
        list->addItem(new QListWidgetItem(QIcon(":/images/rect.PNG"), tr("Rectangle")));
        list->addItem(new QListWidgetItem(QIcon(":/images/oval.PNG"), tr("Oval")));
        list->addItem(new QListWidgetItem(QIcon(":/images/tri.PNG"), tr("Triangle")));
        QHBoxLayout *layout = new QHBoxLayout;
        layout->addWidget(label);
        layout->addWidget(list);

        setLayout(layout);

        connect(list, SIGNAL(currentTextChanged(QString)), label, SLOT(setText(QString)));
}
