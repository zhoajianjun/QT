#include "paintarea.h"
#include <QPainter>
#include <QPrintDialog>
#include <QPrinter>

PaintArea::PaintArea()
{
    image = QImage(400,300,QImage::Format_RGB32);  //画布的初始化大小设为400*300，使用32位颜色
    backColor = qRgb(255,255,255);    //画布初始化背景色使用白色
    image.fill(backColor);
    modified = false;

    scale = 1;
    angle = 0;
    shear = 0;

    penColor = Qt::black;
    brushColor = Qt::black;
    penWidth = 1;
    penStyle = Qt::SolidLine;
    curShape = None;

}

void PaintArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.scale(scale,scale);
    if(angle)
    {
        QPointF center(image.width()/2.0,image.height()/2.0);
        painter.translate(center);
        painter.rotate(angle);
        painter.translate(-center);
    }
    if(shear)
    {
        painter.shear(shear,shear);
    }
    painter.drawImage(0,0,image);
}

void PaintArea::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)  //当鼠标左键按下
    {
        lastPoint = event->pos();   //获得鼠标指针的当前坐标作为起始坐标
    }
}
void PaintArea::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton)   //如果鼠标左键按着的同时移动鼠标
    {
        endPoint = event->pos();  //获得鼠标指针的当前坐标作为终止坐标
        paint(image);   //绘制图形
    }
}
void PaintArea::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)   //如果鼠标左键释放
    {
        endPoint = event->pos();
        paint(image);
    }
}

void PaintArea::paint(QImage &theImage)
{
    QPainter pp(&theImage);   //在theImage上绘图
    QPen pen = QPen();
    pen.setColor(penColor);
    pen.setStyle(penStyle);
    pen.setWidth(penWidth);
    QBrush brush = QBrush(brushColor);
    pp.setPen(pen);
    pp.setBrush(brush);

    int x,y,w,h;
    x = lastPoint.x();
    y = lastPoint.y();
    w = endPoint.x() - x;
    h = endPoint.y() - y;

    switch(curShape)
    {
    case None:
        {
            pp.drawLine(lastPoint,endPoint);   //由起始坐标和终止坐标绘制直线
            lastPoint = endPoint;  //让终止坐标变为起始坐标
            break;
        }
    case Line:
        {
            pp.drawLine(lastPoint,endPoint);
            break;
        }
    case Rectangle:
        {
            pp.drawRect(x,y,w,h);
            break;
        }
    case Ellipse:
        {
            pp.drawEllipse(x,y,w,h);
            break;
        }
    }
    update();   //进行更新界面显示，可引起窗口重绘事件，重绘窗口
    modified = true;
}

void PaintArea::setImageSize(int width, int height)
{
    QImage newImage(width,height,QImage::Format_RGB32);
    image = newImage;
    update();
}

void PaintArea::setImageColor(QColor color)
{
    backColor = color.rgb();  //因为image的背景色要用QRgb类型的颜色，所以这里进行了一下转换
    image.fill(backColor);
    update();
}

bool PaintArea::saveImage(const QString &fileName, const char *fileFormat)
{
    QImage visibleImage = image;

    if (visibleImage.save(fileName, fileFormat))   //实现了文件存储
    {
        modified = false;
        return true;
    }
    else
    {
        return false;
    }
}
bool PaintArea::openImage(const QString &fileName)
{
    QImage loadedImage;
    if (!loadedImage.load(fileName))
        return false;

    QSize newSize = loadedImage.size();
    setImageSize(newSize.width(),newSize.height());
    image = loadedImage;

    modified = false;
    update();
    return true;
}

QSize PaintArea::getImageSize()
{
    return image.size();
}

void PaintArea::doPrint()
 {
     QPrinter printer(QPrinter::HighResolution);

     QPrintDialog *printDialog = new QPrintDialog(&printer, this);
     if (printDialog->exec() == QDialog::Accepted)
     {
         QPainter painter(&printer);
         QRect rect = painter.viewport();
         QSize size = image.size();
         size.scale(rect.size(), Qt::KeepAspectRatio);
         painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
         painter.setWindow(image.rect());
         painter.drawImage(0, 0, image);
     }
 }

void PaintArea::zoomIn()
{
    scale*=1.2;
    update();
}

void PaintArea::zoomOut()
{
    scale/=1.2;
    update();
}

void PaintArea::zoom_1()
{
    scale = 1;
    update();
}

void PaintArea::doRotate()
{
    angle +=90;
    update();
}

void PaintArea::doShear()
{
    shear = 0.2;
    update();
}

void PaintArea::doClear()
{
    image.fill(backColor);    //用现在的画布背景色进行填充
    update();
}


void PaintArea::setPenStyle(Qt::PenStyle style)
{
   penStyle = style;
}
void PaintArea::setPenWidth(int width)
{
    penWidth = width;
}
void PaintArea::setPenColor(QColor color)
{
    penColor = color;
}

void PaintArea::setBrushColor(QColor color)
{
    brushColor = color;
}

void PaintArea::setShape(ShapeType shape)
{
    curShape = shape;
}

