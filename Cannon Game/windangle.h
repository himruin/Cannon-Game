#ifndef WINDANGLE_H
#define WINDANGLE_H

#include <QWidget>

class QDial;

class windAngle : public QWidget
{
    Q_OBJECT

public:
    windAngle(QWidget *parent = 0);

    int value() const;

public slots:
    void setValue(int value);
    void setRange(int minValue, int maxValue);

signals:
    void valueChanged(int newValue);

private:
    QDial *dial;
};

#endif // WINDANGLE_H
