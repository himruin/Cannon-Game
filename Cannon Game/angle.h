#ifndef ANGLE_H
#define ANGLE_H

#include <QWidget>

class QDial;

class Angle : public QWidget
{
    Q_OBJECT

public:
    Angle(QWidget *parent = 0);

    int value() const;

public slots:
    void setValue(int value);
    void setRange(int minValue, int maxValue);

signals:
    void valueChanged(int newValue);

private:
    QDial *dial;
};

#endif
