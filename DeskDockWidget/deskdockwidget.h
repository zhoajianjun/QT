#ifndef DESKDOCKWIDGET_H
#define DESKDOCKWIDGET_H

#include "qtinclude.h"

#define  _DEFAULT_TIMER_INTERNAL_ 100

class DeskDockWidget : public QWidget
{
	Q_OBJECT

public:
	enum DockDirection { TOP , LEFT, RIGHT } ;

    explicit DeskDockWidget(DockDirection D,QWidget* parent=0, Qt::WindowFlags flags = 0);

	int timeInternal() const {return m_timeInternal;};

	void setTimerInternal(int time) {m_timeInternal = time;};

protected:
	virtual void paintEvent(QPaintEvent *);

	virtual void mousePressEvent(QMouseEvent *);

	virtual void mouseMoveEvent(QMouseEvent *);

	QSize sizeHint() const
	{
		return QSize(128,142);
	}

private slots:

	void setDirection(DockDirection D);

	void changeDock();
	
private:

	QPoint m_dragPosition;
	QTimer *m_timer;
	bool m_mouseIn;
	DockDirection m_D;
	bool m_tracingTop;
	bool m_tracingLeft;
	bool m_tracingRight;
	QRect m_screenRect;
	int m_timeInternal;

private:
	void initVariables();

	void initSettings();

	void initTimers();

};

#endif // DESKDOCKWIDGET_H
