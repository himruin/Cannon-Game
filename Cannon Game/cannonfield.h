#ifndef CANNONFIELD_H
#define CANNONFIELD_H

#include <QWidget>

class QTimer;

class CannonField : public QWidget
{
    Q_OBJECT

public:
    CannonField(QWidget *parent = 0);

    int angle() const { return currentAngle; }
    int force() const { return currentForce; }
    double drag() const { return currentDrag; }
    int mass() const { return currentMass; }
    int wind() const { return currentWind; }
    int windAngle() const { return currentWindAngle; }

    bool gameOver() const { return gameEnded; }
    bool isShooting() const;

public slots:
    void setAngle(int angle);
    void setForce(int force);
    void setDrag(double drag);
    void setMass(int mass);
    void setWind(int wind);
    void setWindAngle(int windAngle);

    void shoot();
    void newTarget();
    void setGameOver();
    void restartGame();

private slots:
    void moveShot();

signals:
    void angleChanged(int newAngle);
    void forceChanged(int newForce);
    void dragChanged(double newDrag);
    void massChanged(int newMass);
    void windChanged(int newWind);
    void windAngleChanged(int newWindAngle);

    void hit();
    void missed();
    void canShoot(bool can);

protected:
    void paintEvent(QPaintEvent *event);

private:
    void paintShot(QPainter &painter);
    void paintTarget(QPainter &painter);
    void paintCannon(QPainter &painter);
    QRect cannonRect() const;
    QRect shotRect() const;
    QRect targetRect() const;

    int currentAngle;
    int currentForce;
    double currentDrag;
    int currentMass;
    int currentWind;
    int currentWindAngle;

    int timerCount;
    QTimer *autoShootTimer;

    float shootAngle;
    float shootForce;
    float shootDrag;
    float shootMass;
    float shootWind;
    float shootWindAngle;

    QPoint target;

    bool gameEnded;
};

#endif
