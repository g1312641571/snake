#ifndef GAMEFIELDWIDGET_H
#define GAMEFIELDWIDGET_H

#include <QDialog>
#include <QVector>
#include <QTimer>
#include <QKeyEvent>
#include "snake.h"


/*
class GameFieldWidget : public QDialog
{
    Q_OBJECT
public:
    QTimer *timer;

    GameFieldWidget();

    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    int snakeLength(){return chessboard.snake.body.length();}
    double gameTime(){return time;}

private:
    Chessboard chessboard;

    double time;
    keyState key;


    QPoint toRealPoint(QPoint point);
    //Chessboard chessboard;

public slots:
    void updateGame();

public:
    void pauseGame(){disconnect(timer, SIGNAL(timeout()), this, SLOT(updateGame()));;}
    void continueGame(){connect(timer, SIGNAL(timeout()), this, SLOT(updateGame()));;}
};

*/

#endif // GAMEFIELDWIDGET_H
