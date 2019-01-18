//Drag controls

#include <QDoubleSpinBox>
#include <QVBoxLayout>

#include "drag.h"

Drag::Drag(QWidget *parent)
    : QWidget(parent)
{
    lcd = new QDoubleSpinBox;
    lcd->setFixedHeight(23);

    lcd->setRange(0, 1000);
    lcd->setValue(0);

    connect(lcd, SIGNAL(valueChanged(double)),
            this, SIGNAL(valueChanged(double)));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(lcd);
    setLayout(layout);

    setFocusProxy(lcd);
}

double Drag::value() const
{
    return lcd->value();
}

void Drag::setValue(double value)
{
    lcd->setValue(value);
}

void Drag::setRange(double minValue, double maxValue)
{
    lcd->setRange(minValue, maxValue);
}

