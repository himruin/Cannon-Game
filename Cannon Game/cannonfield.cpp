//Cannon, bullet & the game

#include <QDateTime>
#include <QPaintEvent>
#include <QPainter>
#include <QTimer>

#include <math.h>
#include <stdlib.h>

#include "cannonfield.h"

QPen pen(Qt::NoPen);

CannonField::CannonField(QWidget *parent)
    : QWidget(parent)
{
    currentAngle = 45;
    currentForce = 0;
    currentWind = 0;
    currentWindAngle = 0;
    timerCount = 0;
    autoShootTimer = new QTimer(this);
    connect(autoShootTimer, SIGNAL(timeout()), this, SLOT(moveShot()));
    shootAngle = 0;
    shootForce = 0;
    shootWind = 0;
    shootWindAngle = 0;
    target = QPoint(0, 0);
    gameEnded = false;
    setPalette(QPalette(QColor(224, 224, 224)));
    setAutoFillBackground(true);

    newTarget();
}

void CannonField::setAngle(int angle)
{
    if (currentAngle == angle)
        return;
    currentAngle = angle;
    update(cannonRect());
    emit angleChanged(currentAngle);
}

void CannonField::setForce(int force)
{
    if (force < 0)
        force = 0;
    if (currentForce == force)
        return;
    currentForce = force;
    emit forceChanged(currentForce);
}

void CannonField::setDrag(double drag)
{
    if (drag < 0)
        drag = 0;
    if (currentDrag == drag)
        return;
    currentDrag = drag;
    emit dragChanged(currentDrag);
}

void CannonField::setMass(int mass)
{
    if (mass < 0)
        mass = 0;
    if (currentMass == mass)
        return;
    currentMass = mass;
    emit massChanged(currentMass);
}

void CannonField::setWind(int wind)
{
    if (wind < 0)
        wind = 0;
    if (currentWind == wind)
        return;
    currentWind = wind;
    emit windChanged(currentWind);
}

void CannonField::setWindAngle(int windAngle)
{
    if (windAngle < 0)
        windAngle = 0;
    if (currentWindAngle == windAngle)
        return;
    currentWindAngle = windAngle;
    emit windAngleChanged(currentWindAngle);
}

void CannonField::shoot()
{
    if (isShooting())
        return;
    timerCount = 0;
    shootAngle = currentAngle;
    shootForce = currentForce;
    shootDrag = currentDrag;
    shootMass = currentMass;
    shootWind = currentWind;
    shootWindAngle = currentWindAngle;
    autoShootTimer->start(5);
    emit canShoot(false);
}

void CannonField::newTarget()
{
    static bool firstTime = true;

    if(firstTime)
    {
        firstTime = false;
        QTime midnight (0, 0, 0);
        qsrand(midnight.secsTo(QTime::currentTime()));        
    }
    target = QPoint(200 + qrand() % 190, 10 + qrand() %225);
    update();
}

void CannonField::setGameOver()
{
    if (gameEnded)
        return;
    if (isShooting())
        autoShootTimer->stop();
    gameEnded = true;
    update();
}

void CannonField::restartGame()
{
     if (isShooting())
         autoShootTimer->stop();
     gameEnded = false;
     update();
     emit canShoot(true);
}

void CannonField::moveShot()
{
    QRegion region = shotRect();
    ++timerCount;

    QRect shotR = shotRect();

    if (shotR.intersects(targetRect())) {
        autoShootTimer->stop();
        emit hit();
        emit canShoot(true);
    } else if (shotR.x() > width() || shotR.y() > height()) {
        autoShootTimer->stop();
        emit missed();
        emit canShoot(true);
    } else {
        region = region.united(shotR);
    }
    update(region);
}

void CannonField::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    if(gameEnded) {
        painter.setPen(Qt::black);
        painter.setFont(QFont("Courier", 48, QFont::Bold));
        painter.drawText(rect(), Qt::AlignCenter, tr("Game Over"));
    }

    paintCannon(painter);
    if (isShooting())
        paintShot(painter);
    if (!gameEnded)
        paintTarget(painter);
}

void CannonField::paintShot(QPainter &painter)
{
    painter.setPen(pen);
    painter.setBrush(Qt::black);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.drawEllipse(shotRect());
}

void CannonField::paintTarget(QPainter &painter)
{
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.drawRect(targetRect());
}

const QRect barrelRect(30, -5, 20, 10);

void CannonField::paintCannon(QPainter &painter)
{
    painter.setPen(pen);
    painter.setBrush(Qt::red);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);

    painter.save();
    painter.translate(10, height()-10);
    painter.drawPie(QRect(-35, -35, 70, 70), 0, 360 * 16);
    painter.rotate(-currentAngle);
    painter.drawRect(barrelRect);
    painter.restore();
}

QRect CannonField::cannonRect() const
{
    QRect result(0, 0, 100, 100);
    result.moveBottomLeft(rect().bottomLeft());
    return result;
}

QRect CannonField::shotRect() const
{
    const double g = 9.81;

    double time = timerCount/20.0;
    double velocity = 2 * shootForce;
    double radians = shootAngle * 3.14159265 / 180;
    double density = shootDrag + 0.0000001;
    double flow = shootWind;
    double windradians = shootWindAngle * 3.14159265 / 180;

    double velox = velocity * cos(radians) + flow * cos(windradians);
    double veloy = velocity * sin(radians) + flow * sin(windradians);
    double x0 = 10+((barrelRect.right() + 5) * cos(radians));
    double y0 = 10+(barrelRect.right() + 5) * sin(radians);
    double tvel;


    tvel = sqrt((2*shootMass*g)/(0.8*(density+0.0000001)*0.4)); //terminal velocity

    //eq. of motion
    double x = x0 + velox * tvel / g * (1 - exp(-g*time/tvel));
    double y = y0 + tvel/g * (veloy+tvel) * (1 - exp(-g*time/tvel)) - tvel*time;

    QRect result(0, 0, 8, 8);
    result.moveCenter(QPoint(qRound(x), height() - 1 - qRound(y)));
    return result;
}

QRect CannonField::targetRect() const
{
    QRect result(0, 0, 20, 10);
    result.moveCenter(QPoint(target.x(), height() - 1 - target.y()));
    return result;
}

bool CannonField::isShooting() const
{
    return autoShootTimer->isActive();
}
