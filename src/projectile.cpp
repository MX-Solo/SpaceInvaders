#include "projectile.h"
#include <QGraphicsScene>
#include "spaceship.h"
#include "enemy.h"
#include "QDebug"

Projectile::Projectile(Game::Projectile type)
{
    m_type = type;
    if(m_type == Game::Projectile::SPACESHIP)
    {
        setPixmap(QPixmap(Game::PATH_TO_PROJECTILE_PIXMAP));
    }
    else
    {
        setPixmap(QPixmap(Game::PATH_TO_ENEMY_PROJECTILE_PIXMAP));
    }

    connect(&m_timer, &QTimer::timeout, this, &Projectile::updatePos);
    m_timer.start(int(1000.0f/Game::FPS));
}


void Projectile::updatePos()
{
    if(m_type == Game::Projectile::SPACESHIP)
    {
        moveBy(0, -Game::SPACESHIP_PROJECTILE_SPEED);
        if(y() + pixmap().height() < 0)
        {
            if(scene())
            {
                scene()->removeItem(this);
                delete this;
            }
        }
        checkCollideWithEnemy();
    }
    else if(m_type == Game::Projectile::ENEMY)
    {
        moveBy(0, +Game::SPACESHIP_PROJECTILE_SPEED);
        if(y() > 480)
        {
            if(scene())
            {
                scene()->removeItem(this);
                delete this;
            }
        }
        checkCollideWithSpaceship();
    }

}

void Projectile::checkCollideWithSpaceship()
{
    QList<QGraphicsItem*> collidedList = collidingItems();
    for(int idx = collidedList.size() - 1; idx >= 0; --idx)
    {
        Spaceship* spaceship = dynamic_cast<Spaceship*>(collidedList[idx]);
        if(spaceship)
        {
            spaceship->hit();
            if(scene())
            {
                scene()->removeItem(this);
                delete this;
                return;
            }
        }
    }
}

void Projectile::checkCollideWithEnemy()
{
    QList<QGraphicsItem*> collidedList = collidingItems();
    for(int idx = collidedList.size() - 1; idx >= 0; --idx)
    {
        Enemy* enemy = dynamic_cast<Enemy*>(collidedList[idx]);
        if(enemy)
        {
            enemy->hit();
            if(scene())
            {
                qDebug() << "dead";
                scene()->removeItem(this);
                delete this;
                return;
            }
        }
    }
}


