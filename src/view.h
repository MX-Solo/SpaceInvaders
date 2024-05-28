#include <QGraphicsView>
#include "gamescene.h"

class View : public QGraphicsView
{
    Q_OBJECT
public:
    explicit View();

private:
    GameScene *m_gameScene;

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};

