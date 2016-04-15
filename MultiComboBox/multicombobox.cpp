#include "multicombobox.h"
#include <QCheckBox>

MultiComboBox::MultiComboBox(QWidget *parent)
    : QWidget(parent)
{
    m_com = new QComboBox(this);
}

MultiComboBox::~MultiComboBox()
{

}

void MultiComboBox::init()
{
    m_list = new QListWidget(this);
    m_line = new QLineEdit(this);
    for (int i=0;i<5;++i) {
        QListWidgetItem *pItem = new QListWidgetItem(m_list);
        m_list->addItem(pItem);
        pItem->setData(Qt::UserRole,i);
        QCheckBox *pCheckBox = new QCheckBox(this);
        pCheckBox->setText(QStringLiteral("Qter%1").arg(i));
        m_list->addItem(pItem);
        m_list->setItemWidget(pItem,pCheckBox);
        connect(pCheckBox,SIGNAL(stateChanged(int)),this,SLOT(stateChanged(int)));

    }
    m_com->setModel(m_list->model());
    m_com->setView(m_list);
    m_com->setLineEdit(m_line);
    m_line->setReadOnly(true);                                                                                                                    //ui.comboBox->setEditable(true);
    connect(m_line, SIGNAL(textChanged(const QString &)), this, SLOT(textChanged(const QString &)));
}

void MultiComboBox::stateChanged(int state)
{

}

void MultiComboBox::textChanged(const QString &text)
{

}
