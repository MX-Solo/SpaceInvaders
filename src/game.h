#ifndef GAME_H
#define GAME_H
#include <QSize>
#include <QString>
#include <QPoint>
#include <QColor>
#include <QUrl>

class Game
{
public:
    Game();

    //Utilities
    constexpr static const QSize RESOLUTION = QSize(640, 480);
    constexpr static const int FPS = 60;

    constexpr static const int GRID_WIDTH = RESOLUTION.width()/32+50;
    constexpr static const int GRID_HEIGHT = RESOLUTION.height()/32;
    static int convertPixelToGridPoint(int pixelVal);
    static const QStringList PATH_TO_LEVELS;

    //Sprite
    static const QString PATH_TO_SPACESHIP_PIXMAP;
    static const QString PATH_TO_PROJECTILE_PIXMAP;
    static const QString PATH_TO_ENEMY_PROJECTILE_PIXMAP;
    static const QString PATH_TO_BG_PIXMAP;
    static const QString PATH_TO_ENEMIES_PIXMAP;
    static const QString PATH_TO_EXPLOSION_PIXMAP;
    static const QString PATH_TO_UFO_PIXMAP;
    static const QString PATH_TO_POWERUP_PIXMAP;
    static const QString PATH_TO_SPACESHIP_SPRITE_PIXMAP;

    //Font
    static const QString PATH_TO_FONT;
    static const QColor FONT_COLOR;

    //SFX
    static const QUrl ExplosionSFX;
    static const QUrl InvaderKilledSFX;
    static const QUrl ShootSFX;


    //Spaceship
    constexpr static const float SPACESHIP_SPEED = 4.f;
    constexpr static const float SPACESHIP_PROJECTILE_SPEED = 4.f;
    //nm
    constexpr static const int   SPACESHIP_SHOOT_COUNTER = 10;
    constexpr static const int SPACESHIP_SIZE = 64;
    static bool SPACESHIP_DEAD;

    //Projectile
    enum class Projectile{
        SPACESHIP, ENEMY
    };

    //Enemy
    constexpr static const int ENEMY_SIZE = 32;
    constexpr static const int COUNT_OF_ENEMY_ANIM_FRAMES = 2;
    constexpr static const int TIME_OF_ENEMY_FRAME = 250;

    //nm
    static int   MIN_ENEMY_SHOOT_COUNTER;
    //nm
    static int   MAX_ENEMY_SHOOT_COUNTER;

    //ExplosionAnim
    constexpr static const int COUNT_OF_EXPLOSION_ANIM_FRAMES = 11;
    constexpr static const int TIME_OF_EXPLOSION_ANIM_FRAME = 50;

};

#endif // GAME_H
