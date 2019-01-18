//Wind force controls

#include <QSpinBox>
#include <QSlider>
#include <QVBoxLayout>

#include "wind.h"

Wind::Wind(QWidget *parent)
    : QWidget(parent)
{
    QSpinBox *lcd = new QSpinBox;
    lcd->setFixedHeight(23);
    lcd->setRange(0, 100);

    slider = new QSlider(Qt::Horizontal);

    slider->setRange(0, 100);
    slider->setValue(0);

    connect(slider, SIGNAL(valueChanged(int)),
            lcd, SLOT(setValue(int)));
    connect(lcd, SIGNAL(valueChanged(int)),
            slider, SLOT(setValue(int)));
    connect(slider, SIGNAL(valueChanged(int)),
            this, SIGNAL(valueChanged(int)));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(lcd);
    layout->addWidget(slider);
    setLayout(layout);

    setFocusProxy(slider);
}

int Wind::value() const
{
    return slider->value();
}

void Wind::setValue(int value)
{
    slider->setValue(value);
}

void Wind::setRange(int minValue, int maxValue)
{
    if (minValue < 0 || maxValue > 100 || minValue > maxValue) {
        qWarning("LCDRange::setRange(%d, %d)\n"
                 "\tRange must be 0..99\n"
                 "\tand minValue must not be greater than maxValue",
                 minValue, maxValue);
        return;
    }
    slider->setRange(minValue, maxValue);
}

