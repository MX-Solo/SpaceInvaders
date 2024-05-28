#include "gamescene.h"
#include "game.h"
#include <QKeyEvent>
#include <QDir>
#include <QPainter>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QRandomGenerator>
#include <QString>
#include <QDebug>


GameScene::GameScene(QObject *parent)
    : QGraphicsScene{parent}, m_spaceship(),
      m_leftArrowPressed(false), m_rightArrowPressed(false), m_spacebarPressed(false), m_loopTime(0.0f),
      m_deltaTime(0.0f), m_loopSpeed(int(1000.0f/Game::FPS)), m_level(this)
{
    setBackgroundBrush(Qt::black);
    m_enemyDeadSFX.setSource(Game::InvaderKilledSFX);
    srand(time(0));
    setSceneRect(0,0, 640, 480);

    m_bgItem = new QGraphicsPixmapItem(QPixmap(Game::PATH_TO_BG_PIXMAP));
    m_bgItem->setZValue(-1);
    addItem(m_bgItem);



    int randomValue = QRandomGenerator::global()->bounded(1, 7);

    qDebug() << randomValue;
    QString path = QString(":/res/level/level%0.lvl").arg(randomValue);

    m_level.loadLevel(path);


    addItem(&m_spaceship);
    m_spaceship.setPos(640/2-m_spaceship.pixmap().width()/2,400);


    //nm
    connect(&m_timer, &QTimer::timeout, this, &GameScene::loop);
    m_timer.start(int(1000.0f/Game::FPS));

    m_elapsedTimer.start();
}

void GameScene::playEnemyDeadSFX()
{
    m_enemyDeadSFX.play();
}

void GameScene::loop()
{
    m_deltaTime = m_elapsedTimer.elapsed();
    m_elapsedTimer.restart();

    m_loopTime += m_deltaTime;
    while( m_loopTime > m_loopSpeed &&!Game::SPACESHIP_DEAD)
    {

        m_loopTime -= m_loopSpeed;
        if(m_leftArrowPressed)
        {
            m_spaceship.moveLeft();
        }
        else if(m_rightArrowPressed)
        {
            m_spaceship.moveRight();
        }
        if(m_spacebarPressed)
        {
            m_spaceship.shootUp();
        }

        //deleted
        m_spaceship.decrementShoutCounter();


        Enemy::tryShoot();


        checkNextLevelActivated();

    }
    if(Game::SPACESHIP_DEAD)
    {
        m_level.drawGameOverText();
    }
}

void GameScene::checkNextLevelActivated()
{
    if(Enemy::s_enemyManager.isEmpty())
    {
        m_level.incrementCurrentLevel();
        m_level.loadLevel(Game::PATH_TO_LEVELS[m_level.currentLevel()]);
        Game::SPACESHIP_DEAD = false;
    }
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    if(event->key())
    {
        switch (event->key())
        {
        case Qt::Key_Left:
        {
            m_leftArrowPressed = true;
        }
            break;
        case Qt::Key_Right:
        {
            m_rightArrowPressed = true;
        }
            break;
        case Qt::Key_Space:
        {
            m_spacebarPressed = true;
        }
            break;
        }
    }

        if(event->key() == Qt::Key_R && Game::SPACESHIP_DEAD)
        {
           qDebug() << "restart";
            Game::SPACESHIP_DEAD = false;
           clear();
           m_bgItem = new QGraphicsPixmapItem(QPixmap(Game::PATH_TO_BG_PIXMAP));
           m_bgItem->setZValue(-1);
           addItem(m_bgItem);

           m_level.incrementCurrentLevel();
           m_level.loadLevel(Game::PATH_TO_LEVELS[m_level.currentLevel()]);

           addItem(&m_spaceship);
           m_spaceship.setPos(640/2-m_spaceship.pixmap().width()/2,400);
        }


    QGraphicsScene::keyPressEvent(event);
}

void GameScene::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key())
    {
        switch (event->key())
        {
        case Qt::Key_Left:
        {
            m_leftArrowPressed = false;
        }
            break;
        case Qt::Key_Right:
        {
            m_rightArrowPressed = false;
        }
            break;
        case Qt::Key_Space:
        {
            m_spacebarPressed = false;
        }
            break;
        }
    }
    QGraphicsScene::keyReleaseEvent(event);
}
