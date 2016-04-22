#include "multicombobox.h"
#include <QCheckBox>

MultiComboBox::MultiComboBox(QWidget *parent)
    : QWidget(parent)
{
    m_com = new QComboBox(this);
    m_com->setGeometry(0,0,200,30);
    init();
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
    bSelected = true;
    QString strSelectedData("");
    QObject *object = QObject::sender();
    strSelectedText.clear();
    QCheckBox *pSenderCheckBox = static_cast<QCheckBox*>(object);
    int nCount = m_list->count();
    for (int i = 0;i < nCount;++i) {
        QListWidgetItem *pItem = m_list->item(i);
        QWidget *pwidget = m_list->itemWidget(pItem);
        QCheckBox *pCheckBox = (QCheckBox*)pwidget;
        if (pCheckBox->isChecked()) {
            QString strText = pCheckBox->text();
            strSelectedData.append(strText).append(";");
        }
        if (pSenderCheckBox == pCheckBox) {
            int nData = pItem->data(Qt::UserRole).toInt();
        }
        if (strSelectedData.endsWith(";")) {
            strSelectedData.remove(strSelectedData.count() - 1,1);
        }
        if (!strSelectedData.isEmpty()) {
            strSelectedText = strSelectedData;
            m_line->setText(strSelectedData);
            m_line->setToolTip(strSelectedData);

        } else {
            m_line->clear();
        }
    }
    bSelected = false;
}

void MultiComboBox::textChanged(const QString &text)
{
    if (!bSelected) {
        m_line->setText(strSelectedText);
    }
}
