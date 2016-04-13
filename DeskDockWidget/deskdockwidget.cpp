#include "deskdockwidget.h"

DeskDockWidget::DeskDockWidget(DockDirection D, QWidget *parent, Qt::WindowFlags flags)
	: QWidget(parent, flags),m_D(D)
{
	initVariables();

	initSettings();

	initTimers();
}

void DeskDockWidget::initSettings()
{
	setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Tool | Qt::FramelessWindowHint);

	setAttribute(Qt::WA_TranslucentBackground, true);

	setMouseTracking(true);
}

void DeskDockWidget::initVariables()
{
	m_tracingTop = false;
	m_tracingLeft = false;
	m_tracingRight = false;

	QDesktopWidget *desk = QApplication::desktop();  
	m_screenRect = desk->screenGeometry();

	m_mouseIn = false;

	m_timeInternal = _DEFAULT_TIMER_INTERNAL_;
}

void DeskDockWidget::initTimers()
{
	m_timer = new QTimer(this);

	connect(m_timer, SIGNAL(timeout()), this, SLOT(changeDock()));
}

void DeskDockWidget::setDirection(DockDirection D)
{
	m_D = D;
}

void DeskDockWidget::paintEvent(QPaintEvent *e)
{
	QPainter p(this);

	QPixmap img(":/images/m.png");

	p.setBrush(QBrush(img));

	p.setPen(QColor("#b5b4c9"));

	p.drawRoundedRect(0,0,width() - 1,height() - 1, 8, 8);
}

void DeskDockWidget::changeDock()
{
	int curx = QCursor::pos().x();
	int cury = QCursor::pos().y();
	int curHeight = height();
	int curWidth = width();
	int i = 0;

	switch(m_D)
	{
	case TOP:
		if ( (curx >= x() && curx <= x() + width() && cury >= y() && cury <= y() + height()))
		{

			if(m_mouseIn == false)
			{
				for (i = -curHeight; i <= cury; ++i)
				{
					move(this->geometry().x(), i);
				}
				m_mouseIn = true;
			}
		} 
		else if((curx < x() || curx > x() + width() || cury < y() || cury > y() + height()))
		{
			if (m_mouseIn == true)
			{
				for (i = 0; i < curHeight - 8; ++i)
				{
					move(this->geometry().x(), -i);
				}
				m_mouseIn = false;
			}
		}
		break;
	case  LEFT:
		if ( (curx >= x() && curx <= x() + width() && cury >= y() && cury <= y() + height()))
		{

			if(m_mouseIn == false)
			{
				for (i = -curWidth; i <= curx; ++i)
				{
					move(i, this->geometry().y());
				}
				m_mouseIn = true;
			}
		} 
		else if((curx < x() || curx > x() + width() || cury < y() || cury > y() + height()))
		{
			if (m_mouseIn == true)
			{
				for (i = 0; i < curWidth - 8; ++i)
				{
					move(-i, this->geometry().y());
				}
				m_mouseIn = false;
			}
		}
		break;
	case RIGHT:
		if ( (curx >= x() && curx <= x() + width() && cury >= y() && cury <= y() + height()))
		{

			if(m_mouseIn == false)
			{
				for (i = 0; i <= curWidth - 8; ++i)
				{
					move(m_screenRect.right() - i, this->geometry().y());
				}
				m_mouseIn = true;
			}
		} 
		else if((curx < x() || curx > x() + width() || cury < y() || cury > y() + height()))
		{
			if (m_mouseIn == true)
			{
				for (i = 0; i <= curWidth - 8; ++i)
				{
					move(m_screenRect.right() - curWidth + i , this->geometry().y());
				}
				m_mouseIn = false;
			}
		}
		break;
	default:
		break;
	}
}

void DeskDockWidget::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
		m_dragPosition = e->globalPos() - frameGeometry().topLeft();
		e->accept();
	}
}

void DeskDockWidget::mouseMoveEvent(QMouseEvent *e)
{
	if (e->buttons() & Qt::LeftButton)
	{
		move(e->globalPos() - m_dragPosition);	

		switch (m_D)
		{
		case TOP:
			if (this->geometry().top() <= 8 )
			{
				m_timer->start(m_timeInternal);
				m_tracingTop = true;
			}else
			{
				m_tracingTop = false;
			}
			break;
		case LEFT:
			if (this->geometry().left() <= 8 )
			{
				m_timer->start(m_timeInternal);
				m_tracingLeft = true;
			}else
			{
				m_tracingLeft = false;
			}
			break;
		case RIGHT:
			if (this->geometry().right() >= m_screenRect.right() - 8 )
			{
				m_timer->start(m_timeInternal);
				m_tracingRight = true;
			}else
			{
				m_tracingRight = false;
			}
			break;
		default:
			if (m_timer->isActive())
			{
				m_timer->stop();
			}	
			break;
		}

		if( (m_tracingTop == false)
			&& (m_tracingLeft == false)
			&& (m_tracingRight == false) )
		{
			if (m_timer->isActive())
			{
				m_timer->stop();
			}			
		}
		e->accept();
	}
}
