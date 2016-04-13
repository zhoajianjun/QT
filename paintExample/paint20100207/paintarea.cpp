#include "paintarea.h"
#include <QPainter>
#include <QPrintDialog>
#include <QPrinter>

PaintArea::PaintArea()
{
    image = QImage(400,300,QImage::Format_RGB32);  //�����ĳ�ʼ����С��Ϊ400*300��ʹ��32λ��ɫ
    backColor = qRgb(255,255,255);    //������ʼ������ɫʹ�ð�ɫ
    image.fill(backColor);
    modified = false;
}

void PaintArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(0,0,image);
}

void PaintArea::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)  //������������
    {
        lastPoint = event->pos();   //������ָ��ĵ�ǰ������Ϊ��ʼ����
    }
}
void PaintArea::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton)   //������������ŵ�ͬʱ�ƶ����
    {
        endPoint = event->pos();  //������ָ��ĵ�ǰ������Ϊ��ֹ����
        paint(image);   //����ͼ��
    }
}
void PaintArea::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)   //����������ͷ�
    {
        endPoint = event->pos();
        paint(image);
    }
}

void PaintArea::paint(QImage &theImage)
{
    QPainter pp(&theImage);   //��theImage�ϻ�ͼ
    pp.drawLine(lastPoint,endPoint);   //����ʼ�������ֹ�������ֱ��
    lastPoint = endPoint;  //����ֹ�����Ϊ��ʼ����
    update();   //���и��½�����ʾ�������𴰿��ػ��¼����ػ洰��
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
    backColor = color.rgb();  //��Ϊimage�ı���ɫҪ��QRgb���͵���ɫ���������������һ��ת��
    image.fill(backColor);
    update();
}

bool PaintArea::saveImage(const QString &fileName, const char *fileFormat)
{
    QImage visibleImage = image;

    if (visibleImage.save(fileName, fileFormat))   //ʵ�����ļ��洢
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

