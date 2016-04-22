#ifndef MULTICOMBOBOX_H
#define MULTICOMBOBOX_H

#include <QWidget>
#include <QComboBox>
#include <QListWidget>
#include <QLineEdit>

class MultiComboBox : public QWidget
{
    Q_OBJECT

public:
    MultiComboBox(QWidget *parent = 0);
    ~MultiComboBox();
    void init();
protected slots:
    void stateChanged(int state);
    void textChanged(const QString &text);
private:
    QComboBox *m_com;
    QListWidget *m_list;
    QLineEdit *m_line;
    bool bSelected;
    QString strSelectedText;
};

#endif // MULTICOMBOBOX_H
