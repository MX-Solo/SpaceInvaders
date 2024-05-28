#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Animation : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Animation(const QPixmap& pixmap, QSize tileSize, int countOfFrames, int timeOfFrame);
    ~Animation();
signals:
private slots:
    void updatePixmap();

private:
    QPixmap m_pixmap;
    QSize m_tileSize;
    int m_countOfFrames;
    int m_timeOfFrame;
    int m_currentFrame;
    QTimer m_timer;
};
