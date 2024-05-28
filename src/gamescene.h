#include <QGraphicsScene>
#include <QTimer>
#include <QElapsedTimer>
#include <QSoundEffect>

#include "level.h"
#include "spaceship.h"
#include "enemy.h"

class QGraphicsPixmapItem;
class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(QObject *parent = nullptr);

signals:

public slots:
    void playEnemyDeadSFX();
private slots:
    void loop();

private:
    void checkNextLevelActivated();
    Spaceship m_spaceship;
    bool m_leftArrowPressed, m_rightArrowPressed, m_spacebarPressed;
    // QGraphicsScene interface
    float m_loopTime, m_deltaTime;
    const float m_loopSpeed;
    QTimer m_timer;
    QElapsedTimer m_elapsedTimer;
    QGraphicsPixmapItem *m_bgItem;
    Level m_level;
    QSoundEffect m_enemyDeadSFX;
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
};

