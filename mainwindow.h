#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include "game.h"
#include <QKeyEvent>
#include <QTime>
#include <QDebug>
#include <QThread>
#include <QLabel>
#include <QFile>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void gameOver();

    void hideAll();

    void showMainMenu();
protected:
    void keyPressEvent(QKeyEvent*) override;
    void timerEvent(QTimerEvent*) override;

private slots:
    void on_button_start_game_clicked();

    void on_button_go_main_menu_clicked();

    void on_button_restart_clicked();

    void on_button_exit_clicked();

    void on_button_options_clicked();
    
private:
    Ui::MainWindow *ui;
    Game *game;
    QVBoxLayout *layout;
    QLabel *game_bar;

    const char* STYLE_1 = "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 29, 23, 255), stop:1 rgba(0, 8, 34, 255))";
    const char* GAME_OVER_SCORE_TEXT = "Набрано очков: \n\nРекорд: ";
    int timer;

    int checkRecordFile();
};
#endif // MAINWINDOW_H
