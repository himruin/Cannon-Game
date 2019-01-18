//Wind angle controls

#include <QSpinBox>
#include <QDial>
#include <QVBoxLayout>

#include "windangle.h"

windAngle::windAngle(QWidget *parent)
    : QWidget(parent)
{
    QSpinBox *lcd = new QSpinBox;
    lcd->setFixedHeight(23);
    lcd->setRange(0, 180);

    dial = new QDial;
    dial->setRange(0, 180);
    dial->setValue(0);

    connect(dial, SIGNAL(valueChanged(int)),
            lcd, SLOT(setValue(int)));
    connect(lcd, SIGNAL(valueChanged(int)),
            dial, SLOT(setValue(int)));
    connect(dial, SIGNAL(valueChanged(int)),
            this, SIGNAL(valueChanged(int)));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(lcd);
    layout->addWidget(dial);
    setLayout(layout);

    setFocusProxy(dial);
}

int windAngle::value() const
{
    return dial->value();
}

void windAngle::setValue(int value)
{
    dial->setValue(value);
}

void windAngle::setRange(int minValue, int maxValue)
{
    if (minValue < 0 || maxValue > 180 || minValue > maxValue) {
        qWarning("LCDRange::setRange(%d, %d)\n"
                 "\tRange must be 0..99\n"
                 "\tand minValue must not be greater than maxValue",
                 minValue, maxValue);
        return;
    }
    dial->setRange(minValue, maxValue);
}
