#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPointF>
#include <QTimer>
#include "game.h"
#include <QList>
#include <QSoundEffect>

class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Enemy(int type = 0);
    ~Enemy();
    int enemyType = 0;

    void setPosition(int grid_x, int grid_y);
    static QList<Enemy*> s_enemyManager;
    static void decrementShootCounter();
    static void tryShoot();
    void makeShoot();
    void hit();
signals:
    void deadIsActivated();
private slots:
    void updatePixmap();
private:
    void checkCollisionWithSpaceship();

    QPoint m_srcPoint;
    QTimer m_timer;
    int m_currentFrame;
    QPixmap m_pixmap;

    static int s_shootCounter;
};

#endif // ENEMY_H
