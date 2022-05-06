#include "game.h"

#include <QDebug>

//  Конструктор.
Game::Game()
{
    this->setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);

    resize(DOT_WIDTH * FIELD_WIDTH, DOT_HEIGHT * FIELD_HEIGHT);
}

//  Таймер (движение игрового процесса).
void Game::timerEvent(QTimerEvent *)
{
    if (m_in_game)
    {
        checkApple();
        move();
        checkField();
    }

    this->repaint();  //  Перерисовать картинку.
}


//  Отрисовка.
void Game::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    doDrawing();
}

//  Главная логика игры, отрисовка.
void Game::doDrawing()
{
    QPainter qp(this);

    if (m_in_game)  //  Пока не проиграли.
    {
        qp.setBrush(Qt::red);

        qp.drawEllipse(m_apple.x() * DOT_WIDTH, m_apple.y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);

        //  Отрисовка змейки.
        for (int i = 0; i < m_dots.size(); i++)
        {
            if (i == 0)  //  Отрисовка головы змейки.
            {
                qp.setBrush(Qt::gray);
                qp.drawEllipse(m_dots[i].x() * DOT_WIDTH, m_dots[i].y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
            }
            else  //  Отрисовка хвоста
            {
                qp.setBrush(Qt::green);
                qp.drawEllipse(m_dots[i].x() * DOT_WIDTH, m_dots[i].y()  * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
            }
        }
    }
    else  //  Проигрышь.
    {
        m_in_game = false;
    }
}

//  Спавн яблока.
void Game::localApple()
{
    QTime time = QTime::currentTime();
    qsrand((uint) time.msec());

    m_apple.rx() = qrand() % FIELD_WIDTH;
    m_apple.ry() = qrand() % FIELD_HEIGHT;
}

//  Движение змейки.
void Game::move()
{

    //  Установка начальной позиции змейки.
    for (int i = m_dots.size() - 1; i > 0; i--)
    {
        m_dots[i] = m_dots[i-1];
    }

    //  В зависимости от направления меняем координаты.
    switch (m_dir)
    {
    case 0:    {m_dots[0].ry() -= 1; break;}  //up
    case 1:    {m_dots[0].rx() += 1; break;}  //right
    case 2:    {m_dots[0].ry() += 1; break;}  //down
    case 3:    {m_dots[0].rx() -= 1; break;}  //left
    }
}

//  Обработчик проигрышей.
void Game::checkField()
{
    //  Не съела ли змейка саму себя.
    if (m_dots.size() > 4)
    {
        for (int i = 1; i < m_dots.size(); i++)
        {
            if (m_dots[0] == m_dots[i])
                m_in_game = false;
        }
    }

    //  Не врезалась ли змейка в границы.
    if (m_dots[0].x() >= FIELD_WIDTH)  { m_in_game = false; }
    if (m_dots[0].x() < 0)             { m_in_game = false; }
    if (m_dots[0].y() >= FIELD_HEIGHT) { m_in_game = false; }
    if (m_dots[0].y() < 0)             { m_in_game = false; }

    if (!m_in_game)
    {
        killTimer(m_timer_id);  //  Остановка таймера, в случае проигрыша.
    }
}

//  Проверка, съела ли змейка яблоко.
void Game::checkApple()
{
    if (m_apple == m_dots[0])
    {
        m_dots.push_back(QPoint(0, 0));
        score++;
        localApple();
    }
}

//  Начальная инициализация игры.
void Game::initGame()
{
    m_in_game = true;
    m_dir = 1;
    score = 0;

    m_dots.resize(3);

    for (int i = 0; i < m_dots.size(); i++)
    {
        m_dots[i].rx() = m_dots.size() - i - 1;
        m_dots[i].ry() = 0;
    }

    localApple();

    m_timer_id = startTimer(DELAY);
}
