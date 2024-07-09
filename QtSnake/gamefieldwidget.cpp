/*#include "gamefieldwidget.h"
#include <QPainter>
#include <QMessageBox>
#include <QApplication>
#pragma execution_character_set("utf-8")

GameFieldWidget::GameFieldWidget():time(0.0)
{
    setStyleSheet(".GameFieldWidget{border-image: url(:/image/image/gameField.png);}");
    setFixedSize(1080, 720);
    key = KeyRight;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGame()));
    timer->start(200);
    key = KeyRight;
    setFocusPolicy(Qt::StrongFocus);
    QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier);
    keyPressEvent(&keyEvent);
}

void GameFieldWidget::paintEvent(QPaintEvent *event)
{
    QPainter pa(this);
    static int i = 1;
    if(i > 4)
        i = 1;
    time += 0.2;

    for (auto it = chessboard.snake.body.begin() + 1; it != chessboard.snake.body.end(); ++it)
    {
        switch ((*it).state)
        {
        case Up:
        case Down: pa.drawPixmap(toRealPoint(it->coordinate), QPixmap(":/image/image/BodyVer.png")); break;
        case Left:
        case Right: pa.drawPixmap(toRealPoint(it->coordinate), QPixmap(":/image/image/BodyHor.png")); break;
        case UpLeft:
        case LeftUp: pa.drawPixmap(toRealPoint(it->coordinate), QPixmap(":/image/image/up_left.png")); break;
        case RightUp:
        case UpRight: pa.drawPixmap(toRealPoint(it->coordinate), QPixmap(":/image/image/up_right.png")); break;
        case LeftDown:
        case DownLeft: pa.drawPixmap(toRealPoint(it->coordinate), QPixmap(":/image/image/down_left.png")); break;
        case DownRight:
        case RightDown: pa.drawPixmap(toRealPoint(it->coordinate), QPixmap(":/image/image/down_right.png")); break;
        }
    }
    auto &head = chessboard.snake.body[0];
    QString s;
    switch (head.state)
    {
    case Up: s = ":/image/image/headup_" + QString::number(i) + ".png";pa.drawPixmap(toRealPoint(head.coordinate), QPixmap(s)); ++i; break;
    case Down: s = ":/image/image/headDown_" + QString::number(i) + ".png"; pa.drawPixmap(toRealPoint(head.coordinate), QPixmap(s)); ++i; break;
    case Left: s = ":/image/image/headLeft_" + QString::number(i) + ".png"; pa.drawPixmap(toRealPoint(head.coordinate), QPixmap(s)); ++i; break;
    case Right: s = ":/image/image/headRight_" + QString::number(i) + ".png"; pa.drawPixmap(toRealPoint(head.coordinate), QPixmap(s)); ++i; break;
    case UpLeft: pa.drawPixmap(toRealPoint(head.coordinate), QPixmap(":/image/image/headUpLeft.png")); i = 1;break;
    case LeftUp: pa.drawPixmap(toRealPoint(head.coordinate), QPixmap(":/image/image/headLeftUp.png")); i = 1; break;
    case RightUp: pa.drawPixmap(toRealPoint(head.coordinate), QPixmap(":/image/image/headRightUp.png")); i = 1; break;
    case UpRight: pa.drawPixmap(toRealPoint(head.coordinate), QPixmap(":/image/image/headUpRight.png")); i = 1; break;
    case LeftDown: pa.drawPixmap(toRealPoint(head.coordinate), QPixmap(":/image/image/headLeftDown.png")); i = 1;break;
    case DownLeft: pa.drawPixmap(toRealPoint(head.coordinate), QPixmap(":/image/image/headDownLeft.png")); i = 1; break;
    case DownRight: pa.drawPixmap(toRealPoint(head.coordinate), QPixmap(":/image/image/headDownRight.png")); i = 1; break;
    case RightDown: pa.drawPixmap(toRealPoint(head.coordinate), QPixmap(":/image/image/headRightDown.png")); i = 1; break;
    }
    pa.drawPixmap(toRealPoint(chessboard.food.coordinate), QPixmap(":/image/image/food.png"));

}

void GameFieldWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Up: key = KeyUp; break;
    case Qt::Key_Down: key = KeyDown; break;
    case Qt::Key_Left: key = KeyLeft; break;
    case Qt::Key_Right: key = KeyRight; break;
    default: break;
    }
}

QPoint GameFieldWidget::toRealPoint(QPoint point)
{
    return QPoint(point.x() * 25 + 40, point.y() * 25 + 35);
}

void GameFieldWidget::updateGame()
{
    if(!chessboard.play(key))
    {
        pauseGame();
        switch(QMessageBox::critical(NULL, tr("警告"), tr("哈哈哈哈哈沙比黄天越这都能玩输掉哈哈哈哈哈"), QMessageBox::Ok))
        {
            case QMessageBox::Ok:QApplication::quit(); break;
        }
    }
    else
        update();
}

Chessboard::Chessboard()//:board(H + 2, QVector<char>(W + 2, 'n'))
{
    //for(auto it = snake.body.begin(); it != snake.body.end(); ++it)
    //    board[(*it).coordinate.x()][(*it).coordinate.y()] = 's';
    food.createFood(W, H);
    foreach(SnakeNode n, snake.body)
    {
        if(n.coordinate == food.coordinate)
            food.createFood(W, H);
    }

}

bool Chessboard::play(keyState key)
{
    //key = rectify(key);
    /*if(key == KeyUp && (snake.body[0].state == Down || snake.body[0].state == LeftDown || snake.body[0].state == RightDown))
        key = KeyDown;
    else if(key == KeyDown && (snake.body[0].state == Up || snake.body[0].state ==LeftUp || snake.body[0].state == LeftDown))
        key = KeyUp;
    else if(key == KeyLeft && (snake.body[0].state == Right || snake.body[0].state == DownRight|| snake.body[0].state == UpRight))
        key = KeyRight;
    else if(key == KeyRight && (snake.body[0].state == Left || snake.body[0].state == UpLeft || snake.body[0].state == DownLeft))
        key = KeyLeft;*/
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
    /*if(key == KeyUp)
    {
        //node.coordinate.setY(snake.body[0].coordinate.y() - 1);
        switch (snake.body[0].state)
        {
        case Up:
        case LeftUp:
        case RightUp: node.state = Up; break;
        case Left:
        case UpLeft:
        case DownLeft: node.state = LeftUp; break;
        case Right:
        case UpRight:
        case DownRight: node.state = RightUp; break;
        }
    }
    else if(key == KeyDown)
    {
        //node.coordinate.setY(snake.body[0].coordinate.y() + 1);
        switch (snake.body[0].state)
        {
        case Down:
        case LeftDown:
        case RightDown: node.state = Down; break;
        case Left:
        case UpLeft:
        case DownLeft: node.state = LeftDown; break;
        case Right:
        case UpRight:
        case DownRight: node.state = RightDown; break;
        }
    }
    else if(key == KeyLeft)
    {
        //node.coordinate.setX(snake.body[0].coordinate.x() - 1);
        switch (snake.body[0].state)
        {
        case Down:
        case LeftDown:
        case RightDown: node.state = DownLeft; break;
        case Left:
        case UpLeft:
        case DownLeft: node.state = Left; break;
        case Up:
        case RightUp:
        case LeftUp: node.state = UpLeft; break;
        }
    }
    else
    {
        //node.coordinate.setX(snake.body[0].coordinate.x() + 1);
        switch (snake.body[0].state)
        {
        case Down:
        case LeftDown:
        case RightDown: node.state = DownRight; break;
        case Up:
        case LeftUp:
        case RightUp: node.state = UpRight; break;
        case Right:
        case UpRight:
        case DownRight: node.state = Right; break;
        }
    }*/
    if(node.coordinate.x() < 0 || node.coordinate.y() < 0 || node.coordinate.x() >= W || node.coordinate.y() >= H)
        return false;
    foreach(SnakeNode n, snake.body)
    {
        if(n.coordinate == node.coordinate)
            return false;
    }
    snake.body.push_front(node);
    if(food.coordinate != node.coordinate)
        snake.body.pop_back();
    else
    {
        foreach(SnakeNode n, snake.body)
        {
            if(n.coordinate == food.coordinate)
                food.createFood(W, H);
        }
    }
    return true;
}
*/
