#include "enemy.h"
#include <QGraphicsScene>
#include <QRandomGenerator>
#include "animation.h"
#include "projectile.h"
#include "spaceship.h"
#include "game.h"
#include <QSize>
#include <QDebug>



QList<Enemy*> Enemy::s_enemyManager;
int Enemy::s_shootCounter;

Enemy::Enemy(int type)
    : QGraphicsPixmapItem(QPixmap(Game::PATH_TO_ENEMIES_PIXMAP)), m_currentFrame(0)
{
    enemyType = type;
    m_pixmap = pixmap().copy(type * Game::ENEMY_SIZE * Game::COUNT_OF_ENEMY_ANIM_FRAMES, 0, Game::COUNT_OF_ENEMY_ANIM_FRAMES*Game::ENEMY_SIZE, Game::ENEMY_SIZE);
    setPixmap(m_pixmap.copy(0,0, Game::ENEMY_SIZE, Game::ENEMY_SIZE));

    connect(&m_timer, &QTimer::timeout, this, &Enemy::updatePixmap);
    m_timer.start(Game::TIME_OF_ENEMY_FRAME);

    s_enemyManager.push_back(this);
}

Enemy::~Enemy()
{
    s_enemyManager.removeOne(this);
}

void Enemy::setPosition(int grid_x, int grid_y)
{
    int x = grid_x * 32;
    int y = grid_y * 32;
    setPos(x, y);
}

void Enemy::decrementShootCounter()
{
    s_shootCounter--;
    if(s_shootCounter < 0) s_shootCounter = 0;

}

void Enemy::tryShoot()
{

        decrementShootCounter();
        if(s_shootCounter == 0 && s_enemyManager.size())
        {

            s_shootCounter = QRandomGenerator::global()->bounded(Game::MIN_ENEMY_SHOOT_COUNTER, Game::MAX_ENEMY_SHOOT_COUNTER);
            for(int i = 0 ; i < s_enemyManager.size();i++){
                if(s_enemyManager.at(i)->enemyType == 1){
                    s_enemyManager.at(i)->makeShoot();
                }
            }

        }


}

void Enemy::makeShoot()
{

        Projectile* p = new Projectile(Game::Projectile::ENEMY);
        p->setPos(x()+Game::ENEMY_SIZE/2 - p->boundingRect().width()/2, y() + Game::ENEMY_SIZE - p->boundingRect().height()/2);
        scene()->addItem(p);
}

void Enemy::hit()
{

        if(scene())
        {
            Animation *explosionAnim = new Animation(QPixmap(Game::PATH_TO_EXPLOSION_PIXMAP), QSize(Game::ENEMY_SIZE, Game::ENEMY_SIZE), Game::COUNT_OF_EXPLOSION_ANIM_FRAMES, Game::TIME_OF_EXPLOSION_ANIM_FRAME);
            explosionAnim->setPos(pos());
            scene()->addItem(explosionAnim);
            scene()->removeItem(this);
            emit deadIsActivated();
            delete this;
        }

}

void Enemy::updatePixmap()
{
    m_currentFrame++;
    m_currentFrame %= Game::COUNT_OF_ENEMY_ANIM_FRAMES;
    setPixmap(m_pixmap.copy(m_currentFrame * Game::ENEMY_SIZE, 0, Game::ENEMY_SIZE, Game::ENEMY_SIZE));
}

