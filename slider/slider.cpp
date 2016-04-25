//#include "constants.h"
#include "slider.h"

const char SLIDERSTYLESHEET[] = "QSlider::groove:horizontal{border: 0.5px solid #165708;background: #8f8f8f;"
                                "height: 2px;border-radius: 1px;padding-left:-1px;padding-right:-1px;}            "
                                "QSlider::handle:horizontal{border:1px solid #454343;background:#2af5b9;width:2px;"
                                "margin-top: -2px;margin-bottom: -2px;border-radius: 2px;} QSlider::sub-page:horizontal {background:#2af5b9;border: 1px solid #4A708B;height: 2px;border-radius: 2px;}"
                                "QSlider::add-page:horizontal {background: #615f5f;border: 0px solid #2af5b9;height: 1px;border-radius: 2px;}";

Slider::Slider(QWidget *parent)
    : QSlider(parent)
    , m_inBtnClicked(false)
    , m_outBtnClicked(false)
    , m_inPointX(0)
    , m_outPointX(0)
{
    setCursor(Qt::PointingHandCursor);
    setFixedHeight(5);
    setStyleSheet(SLIDERSTYLESHEET);
}

void Slider::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (orientation() == Qt::Vertical)
            setValue(minimum() + ((maximum()-minimum()) * (height()-event->y())) / height());
        else
            setValue(minimum() + ((maximum()-minimum()) * event->x()) / width());

        m_point.setX(event->x());

        event->accept();
    }

    QSlider::mousePressEvent(event);

}

void Slider::paintEvent(QPaintEvent *event)
{
    QStyleOptionSlider opt;
    initStyleOption(&opt);

    opt.subControls = QStyle::SC_SliderGroove | QStyle::SC_SliderHandle;
    if (tickPosition() != NoTicks) {
        opt.subControls |= QStyle::SC_SliderTickmarks;
    }

    QRect groove_rect = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderGroove, this);
    //qDebug() << groove_rect;
    QSlider::paintEvent(event);

    if (m_inBtnClicked)
    {
        m_inPointX = m_point.x();
        m_inBtnClicked = false;
        //m_outPointX = 0;
    }
    if (m_outBtnClicked)
    {
        m_outPointX = m_point.x();
        m_outBtnClicked = false;
    }

    //qDebug() << "m_inPointX " << m_inPointX << "m_outPointX" << m_outPointX;
    int width;
    width = m_outPointX == 0 ? groove_rect.width() : m_outPointX - m_inPointX;
    if (!m_inPointX)
        return;

    QRect rect(m_inPointX, groove_rect.top(), width, groove_rect.height());
    QPainter painter(this);
    painter.fillRect(rect, QBrush(Qt::red));
}






