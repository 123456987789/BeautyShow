#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMutex>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QRect getCorrectRect(qreal w, qreal h, qreal qRatio);

private slots:
    void openImageFile();

private:
    Ui::Widget *ui;
    QImage image;
    qreal ratio;
    QPainter painter;
    QString oldDir;

    // QWidget interface
protected:
    virtual void wheelEvent(QWheelEvent *event) override;
};
#endif // WIDGET_H
