#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QTime>
#include <QtMath>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QTimer *m_timer;
    int m_speedometerValue;
    QPixmap *m_pixmapArrow;

public slots:
    void on_speedometerSlider_valueChanged(int value);
};
#endif // WIDGET_H
