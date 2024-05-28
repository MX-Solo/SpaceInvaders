#include <QObject>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include "game.h"

class Projectile : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Projectile(Game::Projectile type);
private slots:
    void updatePos();

signals:
private:
    QTimer m_timer;
    Game::Projectile m_type;

    void checkCollideWithSpaceship();
    void checkCollideWithEnemy();
    void checkCollideWithUfo();
};

