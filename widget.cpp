#include "widget.h"
#include "./ui_widget.h"
#include <QPaintEvent>
#include <QPainterPath>
#include <QPainter>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QThread>
#include <QAction>
#include <QPalette>
#include <QWheelEvent>

void Widget::paintEvent(QPaintEvent *event)
{
    qDebug() << image.width() << ", " <<image.height();
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

//    painter.setPen(QPen(Qt::black));
//    for(int i =30;i-30<this->width();i+=30)
//    {
//        painter.drawLine(i,0,i,(this->height()/30+1)*30);
//    }
//    for(int j =30;j-30<this->height();j+=30)
//    {
//        painter.drawLine(0,j,(this->width()/30+1)*30,j);
//    }

    int width = 60;
    int height = 60;
    QColor color(0,0,0);
    for(int i =0;(i-1)*width<this->width();i++)
    {
        for(int j =i%2;(j-1)*height<this->height();j+=2)
        {
            painter.fillRect(i*width,j*height,width,height,QBrush(color));
        }
    }

    if(!image.isNull())
    {
        if (image.width() > this->width() || image.height() > this->height())
        {
            painter.drawImage(getCorrectRect(this->width(),this->height(),ratio), image);
        }
        else
        {
            painter.drawImage(QRect((this->width()-image.width())/2,(this->height()-image.height())/2,image.width(),image.height()), image);
        }
    }
    painter.end();

    event->accept();
}

void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{
    this->isFullScreen() ? this->showNormal() : this->showFullScreen();
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("beauty show");
//    QPalette pal = this->palette();
//    pal.setBrush(QPalette::Window, QBrush(QPixmap(":/images/images/hw.png")));
    setPalette(QColor(Qt::white));
    setAutoFillBackground(true);
    QAction* m_ActionShow = new QAction("Open", this);
    addAction(m_ActionShow);
    setContextMenuPolicy(Qt::ActionsContextMenu);
    connect(m_ActionShow, SIGNAL(triggered()), this, SLOT(openImageFile()));
//    this->setMaximumSize(4096,2160);
//    this->showMaximized();
//    this->setWindowFlags(Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);

}

Widget::~Widget()
{
    delete ui;
}

QRect Widget::getCorrectRect(qreal qW, qreal qH, qreal qRatio)
{
    qreal rectWidth = 0.0;
    qreal rectHeight = 0.0;
    if(qW/qH>qRatio)
    {
        rectHeight=qH;
        rectWidth = rectHeight*qRatio;
    } else{
        rectWidth = qW;
        rectHeight=rectWidth/qRatio;
    }
    return QRect((qW-rectWidth)/2,(qH-rectHeight)/2,rectWidth, rectHeight);
}

void Widget::openImageFile()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "open an image file",
        oldDir,
        "images(*.png *jpg *jpeg *bmp)");
    if (!fileName.isEmpty()) {
        image.load(fileName);
        ratio = qreal(image.width())/qreal(image.height());
        if (!this->isFullScreen() && !this->isMaximized())
        {
//            if(image.width() > screen()->geometry().width() || image.height() > screen()->geometry().height())
//            {
//                resize(getCorrectRect(
//                           screen()->geometry().width()/2,
//                           screen()->geometry().height()/2,
//                           ratio
//                           ).size());

//            }
//            else
//            {
            this->resize(image.width(),image.height());
//            }
        }
        oldDir = fileName.left(fileName.lastIndexOf('\\'));
    }
}



void Widget::wheelEvent(QWheelEvent *event)
{
//    if(event->angleDelta().y()>0)
//    {
//        scaleRatio *= 1.1;
//    }
//    else
//    {
//        scaleRatio *= 0.9;
//    }
//    qDebug() << QString("event->angleDelta().y() = %1").arg(event->angleDelta().y());
//    update();
}
