#ifndef FORCE_H
#define FORCE_H

#include <QWidget>

class QSlider;

class Force : public QWidget
{
    Q_OBJECT

public:
    Force(QWidget *parent = 0);

    int value() const;

public slots:
    void setValue(int value);
    void setRange(int minValue, int maxValue);

signals:
    void valueChanged(int newValue);

private:
    QSlider *slider;
};

#endif // FORCE_H
