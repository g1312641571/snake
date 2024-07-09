#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFont>
#include <QTimer>
#include <QKeyEvent>
#include <QPainter>
#include <QMessageBox>
#include <QApplication>
#include <QFile>
#include <QVector>
#include <QInputDialog>
#include <QStackedWidget>
#include "snake.h"
#include "rankData.h"
#include "musicPlayer.h"


class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);
    QLabel *timeNumLabel;
    QLabel *lengthNumLabel;
    QLabel *scoreNumLabel;
    QPushButton *pauseBtn;
    QStackedWidget *mainStackedWidget;

    MusicPlayer *bgmMusic;

    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
    int snakeLength(){return chessboard.snake.body.length();}
    void startTime(){timer->start(200);}
    void Init();
    void Init(int boardWidth, int boardHeight);

    //Music Functions
    void setMusicPackIndex(int index){musicPackIndex = index;}
    void setMuted(bool muted);
    void changeSnakeSkin(int index){skinIndex = index;}
    void setMode(int mode){this->mode = mode;}

signals:

private slots:
    void startGame();
    void pauseBtnClicked();

private:
    QHBoxLayout *mainHLayout;
    QVBoxLayout *leftVLayout;
    QLabel *timeLabel;
    QLabel *lengthLabel;
    QLabel *scoreLabel;
    QTimer *timer;
    GameBoard chessboard;
    keyState key;
    double time;

    bool pauseBtnPressed;

    QPoint toRealPoint(QPoint point);

    //snake update
    void updateSnakeHead(int key);

    //Snake skin
    int skinIndex;
    QVector<QString> snakeSkinImgPathPrefix;

    //Music Pack
    int musicPackIndex;
    MusicPlayer *scoreSound;
    MusicPlayer *dieSound;
    MusicPlayer *keyboardSound;
    MusicPlayer *pauseBtnSound;

    //Game mode 0 = casual, 1 = competitive
    int mode;
    int timeInterval;

};

#endif // GAMEWIDGET_H
