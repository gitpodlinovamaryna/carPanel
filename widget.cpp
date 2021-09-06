#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QImageReader>
#include <QtGui>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->speedometerSlider->setRange(0, 200);

    QMatrix matrix;
    matrix.rotate(-37);

    QPixmap *tempArrow = new QPixmap(*ui->arrowLabel->pixmap());
    *tempArrow = (*tempArrow).transformed(matrix);
    ui->arrowLabel->setPixmap(*tempArrow);

    m_pixmapArrow = new QPixmap(*tempArrow);
    m_speedometerValue = 0;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_speedometerSlider_valueChanged(int value)
{
    m_speedometerValue = ui->speedometerSlider->value();
    ui->valueLabel->setText(QString::number(m_speedometerValue) + " km/h");

    QMatrix matrix;
    matrix.rotate(m_speedometerValue * 1.06);

    QPixmap *tempArrow = new QPixmap(*m_pixmapArrow);
    *tempArrow = (*m_pixmapArrow).transformed(matrix);

    ui->arrowLabel->setPixmap(*tempArrow);
}
