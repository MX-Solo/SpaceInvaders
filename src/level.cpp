#include "level.h"
#include <QFile>
#include <QTextStream>
#include <QFontDatabase>
#include "gamescene.h"
#include "enemy.h"
#include <QDebug>

Level::Level(QGraphicsScene *scene)
    : m_currentLevel(0)
{
    m_scene = scene;
    int id = QFontDatabase::addApplicationFont(Game::PATH_TO_FONT);
    m_fontFamily = QFontDatabase::applicationFontFamilies(id).at(0);

}

void Level::loadLevel(QString pathToFile)
{
    QFile file(pathToFile);
    QTextStream in(&file);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "File " << pathToFile << " not exist";
    }
    m_currentPathLevel = pathToFile;
    while(!in.atEnd()) {
        QString line = in.readLine();
        if(line.startsWith("//"))
        {
            continue;
        }
        QStringList data = line.split(";");
        for(int i = 0; i < data.size(); ++i)
        {
            QStringList propertiesOfElement = data.at(i).split(",");
            if(propertiesOfElement.isEmpty())
            {
                continue;
            }
            if(propertiesOfElement.size() != 3)
            {
                qFatal("Invalid file format: Enemy{e0,...e4},x,y;");
            }

            Enemy* enemy = nullptr;
            if(propertiesOfElement.at(0) == "e0")
            {
                enemy = new Enemy(0);
                enemy->setPosition(propertiesOfElement.at(1).toInt(), propertiesOfElement.at(2).toInt());
                m_scene->addItem(enemy);
            }
            else if(propertiesOfElement.at(0) == "e1")
            {
                enemy = new Enemy(1);
                enemy->setPosition(propertiesOfElement.at(1).toInt(), propertiesOfElement.at(2).toInt());
                m_scene->addItem(enemy);
            }

            GameScene *scene = qobject_cast<GameScene*>(m_scene);
            if(enemy)
            {
               connect(enemy, &Enemy::deadIsActivated, scene, &GameScene::playEnemyDeadSFX);
            }

        }
    }
    initTextItem();
    file.close();
}

void Level::reset()
{
    loadLevel(m_currentPathLevel);
}

void Level::drawGameOverText()
{
    if(!m_gameOverText->scene())
    {
        m_scene->addItem(m_gameOverText);
    }

    if(!m_restartTextItem->scene())
    {
        m_scene->addItem(m_restartTextItem);
    }

}

void Level::incrementCurrentLevel()
{
    m_currentLevel++;
    m_currentLevel %= Game::PATH_TO_LEVELS.size();
}

int Level::currentLevel() const
{
    return m_currentLevel;
}

void Level::initTextItem()
{
    m_gameOverText = new QGraphicsSimpleTextItem("GAME OVER‌💔");
    m_gameOverText->setFont(QFont(m_fontFamily, 50, 100));
    m_gameOverText->setBrush(Game::FONT_COLOR);
    m_gameOverText->setPen(Game::FONT_COLOR);
    m_gameOverText->setPos(640/2-m_gameOverText->boundingRect().width()/2, 100);

    m_restartTextItem = new QGraphicsSimpleTextItem("R - Restart‌‌ ↻");
    m_restartTextItem->setFont(QFont(m_fontFamily, 40, 100));
    m_restartTextItem->setBrush(Game::FONT_COLOR);
    m_restartTextItem->setPen(Game::FONT_COLOR);
    m_restartTextItem->setPos(640/2-m_gameOverText->boundingRect().width()/2, 200);

}
