#ifndef WIND_H
#define WIND_H

#include <QWidget>

class QSlider;

class Wind : public QWidget
{
    Q_OBJECT

public:
    Wind(QWidget *parent = 0);

    int value() const;

public slots:
    void setValue(int value);
    void setRange(int minValue, int maxValue);

signals:
    void valueChanged(int newValue);

private:
    QSlider *slider;
};

#endif // WIND_H
