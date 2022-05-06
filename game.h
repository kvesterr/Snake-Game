#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QKeyEvent>
#include <QPainter>
#include <QTime>

class Game : public QWidget
{

public:

    Game();

    short getDirection() { return m_dir; }
    void setDirection(short dir) { m_dir = dir; }
    int getDelay() { return DELAY; }
    void setDelay(int del) { DELAY = del; }
    int getScore() { return score; }

    bool isInGame() { return m_in_game; }

    void initGame();


    static const int DOT_WIDTH = 30;  //  Ширина и высота точки (части змейки).
    static const int DOT_HEIGHT = 30;
    static const int FIELD_WIDTH = 20;  //  Ширина и высота игрового поля.
    static const int FIELD_HEIGHT = 18;
    int DELAY = 148;  //  Задержка обновления игрового процесса. default: 148 (4 * 37)

protected:
    void timerEvent(QTimerEvent*) override;
    void paintEvent(QPaintEvent*) override;

private:

    void doDrawing();
    void localApple();
    void move();
    void checkField();
    void checkApple();



    short m_dir;  //  Поле направления. (0 - Up, 1 - Right, 2 - Down, 3 - Left);

    int m_timer_id;

    QPoint m_apple;

    bool m_in_game;
    QVector<QPoint> m_dots;  //  Вектор содержащий информацию о положении змейки.

    int score;

};

#endif // GAME_H
