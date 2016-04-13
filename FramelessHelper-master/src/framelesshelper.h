#ifndef FRAMELESSHELPER_H
#define FRAMELESSHELPER_H

#include <QObject>
#include <QMargins>


class QPushButton;
class QWidget;
class FramelessHelperPrivate;

class FramelessHelper : public QObject
{
    Q_OBJECT
public:
    explicit FramelessHelper(QWidget *parent);

    void setResizeMargins(int margin);
    void setResizeMargins(const QMargins &margins);

    void setCloseButton(QPushButton *button, bool edgeResize = true);
    void setMaximizedButton(QPushButton *button, bool edgeResize = true);
    void setMinimizedButton(QPushButton *button, bool edgeResize = true);
    void setRestoreButton(QPushButton *button, bool edgeResize = true);

    void addEdgeWidget(QWidget *widget);
    void addDragWidget(QWidget *widget);

private:
    FramelessHelperPrivate *d;
};

#endif // FRAMELESSHELPER_H
