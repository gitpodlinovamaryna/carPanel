#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QObject>
#include <QLabel>

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

private slots:
    void on_speedometerSlider_valueChanged(int value);
    void on_ButtonTurnLeft_toggled(bool checked);
    void on_ButtonAlarm_toggled(bool checked);
    void on_ButtonTurnRight_toggled(bool checked);
    void on_TurnLeftTimer();
    void on_TurnRightTimer();
    void on_AlarmTimer();
};
#endif // WIDGET_H
