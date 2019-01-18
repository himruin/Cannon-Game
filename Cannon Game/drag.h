#ifndef DRAG_H
#define DRAG_H

#include <QWidget>

class QDoubleSpinBox;

class Drag : public QWidget
{
    Q_OBJECT
public:
    Drag(QWidget *parent = 0);

    double value() const;

public slots:
    void setValue(double value);
    void setRange(double minValue, double maxValue);

signals:
    void valueChanged(double newValue);

private:
    QDoubleSpinBox *lcd;
};

#endif // DRAG_H
