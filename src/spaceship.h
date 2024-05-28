#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPixmap>
#include "game.h"
#include <QSoundEffect>

class Spaceship : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Spaceship();
    void moveLeft();
    void moveRight();
    void shootUp();
    void decrementShoutCounter();
    void hit();
signals:
private slots:
    void updatePixmap();

private:
    void clampX();
    int m_shoutCounter;
    int m_health;
    QTimer m_timer;
    QPixmap m_pixmap;
    QSoundEffect m_explosionSFX;
    QSoundEffect m_shootSFX;
};
