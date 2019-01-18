#include <QApplication>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLCDNumber>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QCheckBox>

#include "cannonfield.h"
#include "angle.h"
#include "force.h"
#include "drag.h"
#include "mass.h"
#include "wind.h"
#include "windangle.h"
#include "gameboard.h"

GameBoard::GameBoard(QWidget *parent)
    : QWidget(parent)
{
    //force and angle controls decl.
    Force *force = new Force;
    force->setRange(0, 100);

    Angle *angle = new Angle;
    angle->setRange(0, 90);

    Drag *drag = new Drag;
    drag->setRange(0, 1000);

    Mass *mass = new Mass;
    mass->setRange(0, 100);

    Wind *wind = new Wind;
    wind->setRange(0, 100);

    windAngle *windangle = new windAngle;
    windangle->setRange(0, 180);

    cannonField = new CannonField;

    //IMPORTANT!!!
    //sending values from controls to the cannon
    connect(angle, SIGNAL(valueChanged(int)),
            cannonField, SLOT(setAngle(int)));
    connect(cannonField, SIGNAL(angleChanged(int)),
            angle, SLOT(setValue(int)));

    connect(force, SIGNAL(valueChanged(int)),
            cannonField, SLOT(setForce(int)));
    connect(cannonField, SIGNAL(forceChanged(int)),
            force, SLOT(setValue(int)));

    connect(drag, SIGNAL(valueChanged(double)),
            cannonField, SLOT(setDrag(double)));
    connect(cannonField, SIGNAL(dragChanged(double)),
            drag, SLOT(setValue(double)));

    connect(mass, SIGNAL(valueChanged(int)),
            cannonField, SLOT(setMass(int)));
    connect(cannonField, SIGNAL(massChanged(int)),
            mass, SLOT(setValue(int)));

    connect(wind, SIGNAL(valueChanged(int)),
            cannonField, SLOT(setWind(int)));
    connect(cannonField, SIGNAL(windChanged(int)),
            wind, SLOT(setValue(int)));

    connect(windangle, SIGNAL(valueChanged(int)),
            cannonField, SLOT(setWindAngle(int)));
    connect(cannonField, SIGNAL(windAngleChanged(int)),
            windangle, SLOT(setValue(int)));

    connect(cannonField, SIGNAL(hit()),
            this, SLOT(hit()));
    connect(cannonField, SIGNAL(missed()),
            this, SLOT(missed()));

    //buttons and labels
    QPushButton *shoot = new QPushButton(tr("&Shoot!"));

    connect(shoot, SIGNAL(clicked()),
            this, SLOT(fire()));
    connect(cannonField, SIGNAL(canShoot(bool)),
            shoot, SLOT(setEnabled(bool)));

    QPushButton *restart = new QPushButton(tr("&New Game"));

    connect(restart, SIGNAL(clicked()),
            this, SLOT(newGame()));

    hits = new QLCDNumber(2);
    hits->setSegmentStyle(QLCDNumber::Filled);

    shotsLeft = new QLCDNumber(2);
    shotsLeft->setSegmentStyle(QLCDNumber::Filled);


    QLabel *hitslabel = new QLabel(tr("Hits"));
    QLabel *shotsleftlabel = new QLabel(tr("Shots left"));
    QLabel *forcelabel = new QLabel(tr("Speed"));
    QLabel *anglelabel = new QLabel(tr("Angle"));
    QLabel *draglabel = new QLabel(tr("Density"));
    QLabel *masslabel = new QLabel(tr("Mass"));
    QLabel *windlabel = new QLabel(tr("Wind"));


    //setting layouts
    {
    //scoreboard
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(shoot);
    topLayout->addWidget(hits);
    topLayout->addWidget(hitslabel);
    topLayout->addWidget(shotsLeft);
    topLayout->addWidget(shotsleftlabel);
    topLayout->addStretch(1);
    topLayout->addWidget(restart);

    //force
    QHBoxLayout *forceLayout = new QHBoxLayout;
    forceLayout->addWidget(forcelabel);
    forceLayout->addWidget(force);

    //angle
    QHBoxLayout *angleLayout = new QHBoxLayout;
    angleLayout->addWidget(anglelabel);
    angleLayout->addWidget(angle);

    //drag
    QHBoxLayout *dragLayout = new QHBoxLayout;
    dragLayout->addWidget(draglabel);
    dragLayout->addWidget(drag);

    //mass
    QHBoxLayout *massLayout = new QHBoxLayout;
    massLayout->addWidget(masslabel);
    massLayout->addWidget(mass);

    //wind
    QVBoxLayout *windLayout = new QVBoxLayout;
    windLayout->addWidget(wind);
    windLayout->addWidget(windangle);

    QHBoxLayout *IIwindLayout = new QHBoxLayout;
    IIwindLayout->addWidget(windlabel);
    IIwindLayout->addLayout(windLayout);

    //whole left panel
    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addLayout(dragLayout);
    leftLayout->addLayout(massLayout);
    leftLayout->addLayout(IIwindLayout);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addLayout(forceLayout);
    rightLayout->addLayout(angleLayout);

    QHBoxLayout *panel = new QHBoxLayout;
    panel->addLayout(leftLayout);
    panel->addLayout(rightLayout);

    //whole window layout
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addLayout(topLayout, 0, 1);
    gridLayout->addLayout(panel, 0, 0, 2, 1);
    gridLayout->addWidget(cannonField, 1, 1);
    gridLayout->setColumnStretch(1, 10);
    setLayout(gridLayout);
    }

    //setting initial values
    angle->setValue(45);
    force->setValue(25);
    drag->setValue(1.2);
    wind->setValue(0);
    windangle->setValue(0);
    mass->setValue(10);

    newGame();
}

void GameBoard::fire()
{
    if (cannonField->gameOver() || cannonField->isShooting())
        return;
    shotsLeft->display(shotsLeft->intValue() - 1);
    cannonField->shoot();
}

void GameBoard::hit()
{
    hits->display(hits->intValue() + 1);
    if (shotsLeft->intValue() == 0)
        cannonField->setGameOver();
    else
        cannonField->newTarget();
}

void GameBoard::missed()
{
    if (shotsLeft->intValue() == 0)
        cannonField->setGameOver();
}

void GameBoard::newGame()
{
    shotsLeft->display(15);
    hits->display(0);
    cannonField->restartGame();
    cannonField->newTarget();
}
