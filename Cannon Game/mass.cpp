//Mass controls

#include <QSpinBox>
#include <QVBoxLayout>

#include "mass.h"

Mass::Mass(QWidget *parent)
    : QWidget(parent)
{
    lcd = new QSpinBox;
    lcd->setFixedHeight(23);

    lcd->setRange(0, 100);
    lcd->setValue(0);

    connect(lcd, SIGNAL(valueChanged(int)),
            this, SIGNAL(valueChanged(int)));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(lcd);
    setLayout(layout);

    setFocusProxy(lcd);
}

int Mass::value() const
{
    return lcd->value();
}

void Mass::setValue(int value)
{
    lcd->setValue(value);
}

void Mass::setRange(int minValue, int maxValue)
{
    if (minValue < 0 || maxValue > 100 || minValue > maxValue) {
        qWarning("LCDRange::setRange(%d, %d)\n"
                 "\tRange must be 0..99\n"
                 "\tand minValue must not be greater than maxValue",
                 minValue, maxValue);
        return;
    }
    lcd->setRange(minValue, maxValue);
}

