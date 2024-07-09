#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QPoint>
#include <QQueue>
#include <QTime>
#include <QVector>

enum State
{
    Up = 1,
    Down,
    Left,
    Right,
    UpLeft,
    UpRight,
    DownLeft,
    DownRight,
    LeftUp,
    LeftDown,
    RightUp,
    RightDown,
};

class SnakeNode
{
public:
    SnakeNode();
    SnakeNode(QPoint p, State s);
    QPoint coordinate;
    State state;
};

class Snake
{
public:
    Snake();
    void Init();
    bool generateFoodCorrect(QPoint p);
    QQueue<SnakeNode> body;
    ~Snake();

};

class Food
{
public:
    QPoint coordinate;
    void createFood(int width, int height);
};

enum keyState
{
    KeyUp = 1,
    KeyDown,
    KeyLeft,
    KeyRight,
};

class GameBoard
{
public:
    GameBoard();
    GameBoard(int boardWidth, int boardHeight);
    void Init(int boardWidth, int boardHeight);

    Snake snake;
    void createCorrectFood();
    int getBoardWidth(){return boardWidth;}
    int getBoardHeight(){return boardHeight;}

    QPoint getFoodCoordinate(){return food.coordinate;}


public:
    /*
     Function "play" return value
     0:dead
     1:nothing
     2:eat the food
    */
    int play(keyState key);

private:
    int boardWidth;
    int boardHeight;
    Food food;
    QVector<QVector<char>> checkFoodOk;

    void selectFood();

};

#endif // CHESSBOARD_H
