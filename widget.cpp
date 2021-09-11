#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
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
        m_timer = new QTimer();
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


void Widget::on_ButtonTurnLeft_toggled(bool checked)
{
    if(checked)
        {
            QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(on_TurnLeftTimer()));
            m_timer->start(500);
        }
        else
        {
            m_timer->stop();
            QObject::disconnect(m_timer, SIGNAL(timeout()), this, SLOT(on_TurnLeftTimer()));
            ui->labelTurnLeft->setVisible(true);
        }
}


void Widget::on_ButtonAlarm_toggled(bool checked)
{
    if(checked)
        {
            QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(on_AlarmTimer()));
            m_timer->start(500);
        }
        else
        {
            m_timer->stop();
            QObject::disconnect(m_timer, SIGNAL(timeout()), this, SLOT(on_AlarmTimer()));
            ui->labelTurnRight->setVisible(true);
            ui->labelTurnLeft->setVisible(true);
        }
}


void Widget::on_ButtonTurnRight_toggled(bool checked)
{
    if(checked == true)
       {
           QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(on_TurnRightTimer()));
           m_timer->start( 500);
       }
       else
       {
           m_timer->stop();
           QObject::disconnect(m_timer, SIGNAL(timeout()), this, SLOT(on_TurnRightTimer()));
           ui->labelTurnRight->setVisible(true);
       }
}

void Widget::on_TurnLeftTimer()
{
    ui->labelTurnLeft->isVisible() ? ui->labelTurnLeft->setVisible(false) : ui->labelTurnLeft->setVisible(true);
}

void Widget::on_TurnRightTimer()
{
    ui->labelTurnRight->isVisible() ? ui->labelTurnRight->setVisible(false) : ui->labelTurnRight->setVisible(true);
}

void Widget::on_AlarmTimer()
{
    if(ui->labelTurnLeft->isVisible() && ui->labelTurnRight->isVisible())
    {
        ui->labelTurnLeft->setVisible(false);
        ui->labelTurnRight->setVisible(false);

    }
    else
    {
        ui->labelTurnRight->setVisible(true);
        ui->labelTurnLeft->setVisible(true);
    }
}


