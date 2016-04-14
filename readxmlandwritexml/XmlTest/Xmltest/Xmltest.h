#ifndef XMLTEST_H
#define XMLTEST_H

#include <QtWidgets>
#include <QtCore>
#include <QtXml>

class Xmltest : public QWidget
{
    Q_OBJECT
public:
    Xmltest(QWidget *parent = 0);
    ~Xmltest();

    void checkFolderPath(QString parentPath,QDomElement &parentElt,QDomDocument &doc);
    QDomDocument createFolderPathXml(QString path);
};

#endif // XMLTEST_H
