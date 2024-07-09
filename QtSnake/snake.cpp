#include "snake.h"
#include <QDebug>

GameBoard::GameBoard(): checkFoodOk(40, QVector<char>(26, '0'))
{
    Init(40, 26);
}

GameBoard::GameBoard(int boardWidth, int boardHeight):
    checkFoodOk(boardWidth, QVector<char>(boardHeight, '0'))
{
    Init(boardWidth, boardHeight);
}

void GameBoard::Init(int boardWidth, int boardHeight)
{
    this->boardWidth = boardWidth;
    this->boardHeight = boardHeight;
    snake.Init();
    food.createFood(boardWidth, boardHeight);
    while(!snake.generateFoodCorrect(food.coordinate))
        food.createFood(boardWidth, boardHeight);
}

void GameBoard::createCorrectFood()
{
    for(auto n = snake.body.begin(); n != snake.body.end(); ++n)
    {
        checkFoodOk[n->coordinate.x()][n->coordinate.y()] = '1';
    }

    selectFood();

    for(auto n = snake.body.begin(); n != snake.body.end(); ++n)
    {
        checkFoodOk[n->coordinate.x()][n->coordinate.y()] = '0';
    }
}

Snake::Snake()
{
    Init();
}

void Snake::Init()
{
    body.clear();
    for(int i = 0; i != 4; ++i)
    {
        SnakeNode node(QPoint(i, 0), Right);
        body.push_front(node);
    }
}

bool Snake::generateFoodCorrect(QPoint p)
{
    for (auto n = body.begin(); n != body.end(); ++n)
    {
        if(n->coordinate == p)
            return false;
    }
    return true;
}

Snake::~Snake()
{

}


void Food::createFood(int width, int height)
{

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    coordinate.setX((qrand() % width));
    coordinate.setY((qrand() % height));
}

SnakeNode::SnakeNode()
{

}

SnakeNode::SnakeNode(QPoint p, State s): coordinate(p), state(s)
{

}

int GameBoard::play(keyState key)
{
    SnakeNode node;
    node.coordinate = snake.body[0].coordinate;
    switch (snake.body[0].state)
    {
    case Up:
    case LeftUp:
    case RightUp:
        node.coordinate.ry()--;
        switch (key)
        {
        case KeyUp:
        case KeyDown: node.state = Up; break;
        case KeyLeft: node.state = DownLeft; break;
        case KeyRight: node.state = DownRight; break;
        }
        break;
    case Down:
    case LeftDown:
    case RightDown:
        node.coordinate.ry()++;
        switch (key)
        {
        case KeyUp:
        case KeyDown: node.state = Down; break;
        case KeyLeft: node.state = UpLeft; break;
        case KeyRight: node.state = UpRight; break;
        }
        break;
    case Left:
    case UpLeft:
    case DownLeft:
        node.coordinate.rx()--;
        switch (key)
        {
        case KeyUp: node.state = RightUp; break;
        case KeyDown: node.state = RightDown; break;
        case KeyLeft:
        case KeyRight: node.state = Left; break;
        }
        break;
    case Right:
    case UpRight:
    case DownRight:
        node.coordinate.rx()++;
        switch (key)
        {
        case KeyUp: node.state = LeftUp; break;
        case KeyDown: node.state = LeftDown; break;
        case KeyLeft:
        case KeyRight: node.state = Right; break;
        }
        break;
    }

    if(node.coordinate.x() < 0 || node.coordinate.y() < 0 ||
            node.coordinate.x() >= boardWidth || node.coordinate.y() >= boardHeight)
        return 0;
    foreach(SnakeNode n, snake.body)
    {
        if(n.coordinate == node.coordinate)
            return 0;
    }
    snake.body.push_front(node);
    if(food.coordinate != node.coordinate)
    {
        snake.body.pop_back();
        return 1;
    }
    else
    {
        createCorrectFood();
        return 2;
    }
}

void GameBoard::selectFood()
{
    food.createFood(boardWidth, boardHeight);

    for(int x = food.coordinate.x(); x != boardWidth; ++x)
    {
        food.coordinate.setX(x);
        if(checkFoodOk[x][food.coordinate.y()] == '0')
            return;
    }

    for (int y = food.coordinate.y(); y != boardHeight; ++y)
    {
        food.coordinate.setY(y);
        for(int x = 0; x != boardWidth; ++x)
        {
            food.coordinate.setX(x);
            if(checkFoodOk[x][food.coordinate.y()] == '0')
                return;
        }
    }
    for (int y = 0; y != boardHeight; ++y)
    {
        food.coordinate.setY(y);
        for(int x = 0; x != boardWidth; ++x)
        {
            food.coordinate.setX(x);
            if(checkFoodOk[x][food.coordinate.y()] == '0')
                return;
        }
    }
}
