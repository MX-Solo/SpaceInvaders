#include "spaceship.h"
#include "game.h"
#include "animation.h"
#include <QGraphicsScene>
#include "projectile.h"
#include <QDebug>

Spaceship::Spaceship()
    : QGraphicsPixmapItem(QPixmap(Game::PATH_TO_SPACESHIP_SPRITE_PIXMAP)), m_shoutCounter(0)
{
    m_pixmap = pixmap();
    setPixmap(m_pixmap.copy(0, 0, Game::SPACESHIP_SIZE, Game::SPACESHIP_SIZE));
    m_health = 1;



    connect(&m_timer, &QTimer::timeout, this, &Spaceship::updatePixmap);
    m_timer.start(1000);

    m_explosionSFX.setSource(Game::ExplosionSFX);
    m_shootSFX.setSource(Game::ShootSFX);
}

void Spaceship::moveLeft()
{
    moveBy(-Game::SPACESHIP_SPEED, 0);
    clampX();
}

void Spaceship::moveRight()
{
    moveBy(Game::SPACESHIP_SPEED, 0);
    clampX();
}

void Spaceship::shootUp()
{
    if(m_shoutCounter == 0)
    {
        m_shoutCounter = Game::SPACESHIP_SHOOT_COUNTER;
        m_shootSFX.play();
        if(scene())
        {

        Projectile* p = new Projectile(Game::Projectile::SPACESHIP);
        p->setPos(x()+30, y());
        scene()->addItem(p);

        }
    }

}

void Spaceship::decrementShoutCounter()
{
    m_shoutCounter--;
    if(m_shoutCounter < 0)
    {
        m_shoutCounter = 0;
    }
}

void Spaceship::hit()
{
        Game::SPACESHIP_DEAD = true;
        qDebug() << "dead";
        if(scene())
        {
            Animation *explosionAnim = new Animation(QPixmap(Game::PATH_TO_EXPLOSION_PIXMAP), QSize(Game::ENEMY_SIZE, Game::ENEMY_SIZE), Game::COUNT_OF_EXPLOSION_ANIM_FRAMES, Game::TIME_OF_EXPLOSION_ANIM_FRAME);
            explosionAnim->setPos(pos());
            scene()->addItem(explosionAnim);
            scene()->removeItem(this);
            m_explosionSFX.play();
        }
}



void Spaceship::updatePixmap()
{

        setPixmap(m_pixmap.copy(0, 0, Game::SPACESHIP_SIZE, Game::SPACESHIP_SIZE));
}

void Spaceship::clampX()
{
    if(x() < 0)
    {
        setX(0);
    }
    else if(x() + pixmap().width() > 640)
    {
        setX(640 - pixmap().width());
    }
}
