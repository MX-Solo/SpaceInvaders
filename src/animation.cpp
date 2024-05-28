#include "animation.h"
#include <QGraphicsScene>
#include <QDebug>

Animation::Animation(const QPixmap &pixmap, QSize tileSize, int countOfFrames, int timeOfFrame)
    : m_currentFrame(0)
{
    m_pixmap = pixmap;
    m_tileSize = tileSize;
    m_countOfFrames = countOfFrames;
    m_timeOfFrame = timeOfFrame;

    setPixmap(m_pixmap.copy(0,0,tileSize.width(), tileSize.height()));
    connect(&m_timer, &QTimer::timeout, this, &Animation::updatePixmap);
    m_timer.start(timeOfFrame);
}

Animation::~Animation()
{
    qDebug() << "~Animation()";
}

void Animation::updatePixmap()
{

    m_currentFrame++;
    setPixmap(m_pixmap.copy(m_currentFrame*m_tileSize.width(), 0, m_tileSize.width(), m_tileSize.height()));

    if(m_currentFrame == m_countOfFrames)
    {
        if(scene())
        {
            scene()->removeItem(this);
            delete this;
            return;
        }
    }
}
