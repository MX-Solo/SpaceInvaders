#ifndef LEVEL_H
#define LEVEL_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QFont>

class Level : public QObject
{
    Q_OBJECT
public:
    explicit Level(QGraphicsScene* scene);
    void loadLevel(QString pathToFile);
    void reset();
    void drawGameOverText();
    void incrementCurrentLevel();
    int currentLevel() const;
signals:

private:
    void initTextItem();
    int m_currentLevel;

    QString m_currentPathLevel, m_fontFamily;
    QGraphicsScene* m_scene;
    QGraphicsSimpleTextItem *m_gameOverText, *m_restartTextItem;
    QFont m_mainTextFont, m_subTextFont;
};

#endif // LEVEL_H
