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
    matrix.rotate(-37); // start position, the arrow is on zero

    QPixmap tempArrow = QPixmap(*ui->arrowLabel->pixmap());
    tempArrow = (tempArrow).transformed(matrix);
    ui->arrowLabel->setPixmap(tempArrow);

    m_pixmapArrow = new QPixmap(tempArrow);
    m_speedometerValue = 0;
    m_timer = new QTimer();
}

Widget::~Widget()
{
    delete m_pixmapArrow;
    delete m_timer;
    delete ui;
}

void Widget::on_speedometerSlider_valueChanged(int value)
{
    m_speedometerValue = ui->speedometerSlider->value();
    ui->valueLabel->setText(QString::number(m_speedometerValue) + " km/h");

    QMatrix matrix;
    matrix.rotate(m_speedometerValue * 1.06); // rotation 1.06 degree

    QPixmap tempArrow = QPixmap(*m_pixmapArrow);
    tempArrow = (*m_pixmapArrow).transformed(matrix);

    ui->arrowLabel->setPixmap(tempArrow);
}

void Widget::on_ButtonTurnLeft_toggled(bool checked)
{
    if(checked)
    {
        QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(on_TurnLeftTimer()));
        m_timer->start(500);
        ui->ButtonTurnRight->setCheckable(false);
        ui->ButtonAlarm->setCheckable(false);
    }
    else
    {
        m_timer->stop();
        QObject::disconnect(m_timer, SIGNAL(timeout()), this, SLOT(on_TurnLeftTimer()));
        ui->labelTurnLeft->setVisible(true);
        ui->ButtonTurnRight->setCheckable(true);
        ui->ButtonAlarm->setCheckable(true);
    }
}

void Widget::on_ButtonAlarm_toggled(bool checked)
{
    if(checked)
        {
            QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(on_AlarmTimer()));
            m_timer->start(500);
            ui->ButtonTurnRight->setCheckable(false);
            ui->ButtonTurnLeft->setCheckable(false);
        }
    else
        {
            m_timer->stop();
            QObject::disconnect(m_timer, SIGNAL(timeout()), this, SLOT(on_AlarmTimer()));
            ui->labelTurnRight->setVisible(true);
            ui->labelTurnLeft->setVisible(true);
            ui->ButtonTurnRight->setCheckable(true);
            ui->ButtonTurnLeft->setCheckable(true);
        }
}


void Widget::on_ButtonTurnRight_toggled(bool checked)
{
    if(checked)
    {
        QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(on_TurnRightTimer()));
        m_timer->start( 500);
        ui->ButtonTurnLeft->setCheckable(false);
        ui->ButtonAlarm->setCheckable(false);

    }
    else
    {
        m_timer->stop();
        QObject::disconnect(m_timer, SIGNAL(timeout()), this, SLOT(on_TurnRightTimer()));
        ui->labelTurnRight->setVisible(true);
        ui->ButtonTurnLeft->setCheckable(true);
        ui->ButtonAlarm->setCheckable(true);
    }
}

void Widget::on_TurnLeftTimer()
{
     ui->labelTurnLeft->setVisible(!ui->labelTurnLeft->isVisible());
}

void Widget::on_TurnRightTimer()
{
    ui->labelTurnRight->setVisible(!ui->labelTurnRight->isVisible());
}

void Widget::on_AlarmTimer()
{
    ui->labelTurnLeft->setVisible(!ui->labelTurnLeft->isVisible());
    ui->labelTurnRight->setVisible(!ui->labelTurnRight->isVisible());
}


