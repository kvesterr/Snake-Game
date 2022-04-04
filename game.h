#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QKeyEvent>
#include <QPainter>
#include <QTime>
#include <QMessageBox>

class Game : public QWidget
{
public:
    Game();

protected:
    void timerEvent(QTimerEvent*) override;
    void keyPressEvent(QKeyEvent*) override;
    void paintEvent(QPaintEvent*) override;

private:
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;
    static const int FIELD_WIDTH = 20;
    static const int FIELD_HEIGHT = 20;
    static const int DELAY = 150;

    void doDrawing();
    void localApple();
    void move();
    void checkField();
    void gameOver();
    void checkApple();

    int m_timer_id;

    QPoint m_apple;

    enum directions
    {
        left, right, up, down
    };

    directions m_dir;

    bool m_in_game;
    QVector<QPoint> m_dots;

    void initGame();
};

#endif // GAME_H
