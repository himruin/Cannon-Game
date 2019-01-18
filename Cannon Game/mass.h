#ifndef MASS_H
#define MASS_H

#include <QWidget>

class QSpinBox;

class Mass : public QWidget
{
    Q_OBJECT

public:
    Mass(QWidget *parent = 0);

    int value() const;

public slots:
    void setValue(int value);
    void setRange(int minValue, int maxValue);

signals:
    void valueChanged(int newValue);

private:
    QSpinBox *lcd;
};

#endif // MASS_H
