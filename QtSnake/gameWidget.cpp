#include "gameWidget.h"
#pragma execution_character_set("utf-8")

GameWidget::GameWidget(QWidget *parent) : QWidget(parent), time(-0.2),
     pauseBtnPressed(false), musicPackIndex(0)
{
    setFixedSize(1280, 720);

    //Widget design
    QFont font("黑体", 20);
    timeLabel = new QLabel(tr("时间"));
    timeNumLabel = new QLabel(tr("0"));
    lengthLabel = new QLabel(tr("长度"));
    lengthNumLabel = new QLabel(tr("4"));
    scoreLabel = new QLabel(tr("分数"));
    scoreNumLabel = new QLabel(tr("0"));
    pauseBtn = new QPushButton;
    leftVLayout = new QVBoxLayout;
    leftVLayout->addWidget(timeLabel);
    timeLabel->setStyleSheet("border-image: url(:/image/image/Bulletin.png);");
    timeLabel->setFont(font);
    timeLabel->setAlignment(Qt::AlignCenter);
    timeNumLabel->setStyleSheet("border-image: url(:/image/image/Bulletin.png);");
    timeNumLabel->setFont(font);
    timeNumLabel->setAlignment(Qt::AlignCenter);
    lengthLabel->setStyleSheet("border-image: url(:/image/image/Bulletin.png);");
    lengthLabel->setFont(font);
    lengthLabel->setAlignment(Qt::AlignCenter);
    lengthNumLabel->setStyleSheet("border-image: url(:/image/image/Bulletin.png);");
    lengthNumLabel->setFont(font);
    lengthNumLabel->setAlignment(Qt::AlignCenter);
    scoreLabel->setStyleSheet("border-image: url(:/image/image/Bulletin.png);");
    scoreLabel->setFont(font);
    scoreLabel->setAlignment(Qt::AlignCenter);
    scoreNumLabel->setStyleSheet("border-image: url(:/image/image/Bulletin.png);");
    scoreNumLabel->setFont(font);
    scoreNumLabel->setAlignment(Qt::AlignCenter);
    pauseBtn->setIcon(QIcon(":/image/image/pauseBtn.png"));
    pauseBtn->setIconSize(QSize(200, 200));
    pauseBtn->setFlat(true);
    pauseBtn->setFocusPolicy(Qt::NoFocus);
    leftVLayout->addWidget(timeNumLabel);
    leftVLayout->addWidget(lengthLabel);
    leftVLayout->addWidget(lengthNumLabel);
    leftVLayout->addWidget(scoreLabel);
    leftVLayout->addWidget(scoreNumLabel);
    leftVLayout->addWidget(pauseBtn);
    leftVLayout->setStretchFactor(timeLabel, 85);
    leftVLayout->setStretchFactor(timeNumLabel, 85);
    leftVLayout->setStretchFactor(lengthLabel, 85);
    leftVLayout->setStretchFactor(lengthNumLabel, 85);
    leftVLayout->setStretchFactor(scoreLabel, 85);
    leftVLayout->setStretchFactor(scoreNumLabel, 85);
    leftVLayout->setStretchFactor(pauseBtn, 210);
    mainHLayout = new QHBoxLayout;
    setLayout(mainHLayout);
    mainHLayout->addLayout(leftVLayout);
    mainHLayout->addStretch(1080);
    mainHLayout->setStretchFactor(leftVLayout, 200);
    mainHLayout->setMargin(0);
    mainHLayout->setSpacing(0);

    setFocusPolicy(Qt::StrongFocus);

    //Game setting
    timer = new QTimer(this);
    key = KeyRight;
    mode = 0;

    //Music
    scoreSound = new MusicPlayer;
    scoreSound->setPlayBackMode(QMediaPlaylist::CurrentItemOnce);
    scoreSound->addMusic(QUrl("qrc:/music/music/score.mp3"));
    scoreSound->addMusic(QUrl("qrc:/music/music/okashii/score2.mp3"));

    dieSound = new MusicPlayer;
    dieSound->setPlayBackMode(QMediaPlaylist::CurrentItemOnce);
    dieSound->addMusic(QUrl("qrc:/music/music/die.mp3"));
    dieSound->addMusic(QUrl("qrc:/music/music/okashii/die2.mp3"));

    keyboardSound = new MusicPlayer;
    keyboardSound->setPlayBackMode(QMediaPlaylist::CurrentItemOnce);
    keyboardSound->addMusic(QUrl("qrc:/music/music/keyboardMove.mp3"));
    keyboardSound->addMusic(QUrl("qrc:/music/music/okashii/keyboard2.mp3"));

    pauseBtnSound = new MusicPlayer;
    pauseBtnSound->setPlayBackMode(QMediaPlaylist::CurrentItemOnce);
    pauseBtnSound->addMusic(QUrl("qrc:/music/music/button2.mp3"));
    pauseBtnSound->addMusic(QUrl("qrc:/music/music/okashii/button22.mp3"));

    //Skin
    skinIndex = 0;
    snakeSkinImgPathPrefix.push_back(":/image/image/");
    snakeSkinImgPathPrefix.push_back(":/image/image/skin/Skin1/");


    //Singal
    connect(timer, SIGNAL(timeout()), this, SLOT(startGame()));
    connect(pauseBtn, SIGNAL(clicked()), this, SLOT(pauseBtnClicked()));
}

void GameWidget::keyPressEvent(QKeyEvent *event)
{
    updateSnakeHead(event->key());
    switch (event->key())
    {

    case Qt::Key_Up:
    case Qt::Key_W:
        key = KeyUp;
        keyboardSound->setCurMusicIndex(musicPackIndex);
        keyboardSound->play();
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        key = KeyDown;
        keyboardSound->setCurMusicIndex(musicPackIndex);
        keyboardSound->play();
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        key = KeyLeft;
        keyboardSound->setCurMusicIndex(musicPackIndex);
        keyboardSound->play();
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        key = KeyRight;
        keyboardSound->setCurMusicIndex(musicPackIndex);
        keyboardSound->play();
        break;
    case Qt::Key_Space:
        pauseBtnClicked();
        break;
    case Qt::Key_Escape:
        if(!pauseBtnPressed)
        {
            pauseBtn->setIcon(QIcon(":/image/image/continueBtn.png"));
            pauseBtn->setIconSize(QSize(200, 200));
            timer->stop();
            pauseBtnPressed = true;
        }
        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setText(tr("  您确定返回主菜单么？      "));
        msgBox->setWindowTitle(tr("提示"));
        msgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox->setButtonText(QMessageBox::Ok, tr("确定"));
        msgBox->setButtonText(QMessageBox::Cancel, tr("取消"));
        auto ret = msgBox->exec();
        if(ret == QMessageBox::Cancel)
            break;
        else
        {
            mainStackedWidget->setCurrentIndex(0);
            bgmMusic->setCurMusicIndex(0);
            return;
        }
    }
}

void GameWidget::paintEvent(QPaintEvent *event)
{
    QPainter pa(this);
    if(mode == 0)
        pa.drawPixmap(210, 0, QPixmap(":/image/image/gameField.png"));
    else if(mode == 1)
        pa.drawPixmap(210, 0, QPixmap(":/image/image/gameField2.png"));

    for (auto it = chessboard.snake.body.begin() + 1;
         it != chessboard.snake.body.end(); ++it)
    {
        switch ((*it).state)
        {
        case Up:
        case Down:
                pa.drawPixmap(toRealPoint(it->coordinate),
                QPixmap(snakeSkinImgPathPrefix[mode] + "bodyVer.png"));
                break;
        case Left:
        case Right:
                pa.drawPixmap(toRealPoint(it->coordinate),
                QPixmap(snakeSkinImgPathPrefix[mode] + "bodyHor.png"));
                break;
        case UpLeft:
        case LeftUp:
                pa.drawPixmap(toRealPoint(it->coordinate),
                QPixmap(snakeSkinImgPathPrefix[mode] + "up_left.png"));
                break;
        case RightUp:
        case UpRight:
                pa.drawPixmap(toRealPoint(it->coordinate),
                QPixmap(snakeSkinImgPathPrefix[mode] + "up_right.png"));
                break;
        case LeftDown:
        case DownLeft:
                pa.drawPixmap(toRealPoint(it->coordinate),
                QPixmap(snakeSkinImgPathPrefix[mode] + "down_left.png"));
                break;
        case DownRight:
        case RightDown:
                pa.drawPixmap(toRealPoint(it->coordinate),
                QPixmap(snakeSkinImgPathPrefix[mode] + "down_right.png"));
                break;
        }
    }
    //drawSnakeHead();

    //QPainter pa(this);
    static int i = 1;
    if(i > 4)
        i = 1;
    auto &head = chessboard.snake.body[0];
    QString s;
    switch (head.state)
    {
    case Up:
        s = snakeSkinImgPathPrefix[mode] + "headup_" + QString::number(i) +
            ".png";pa.drawPixmap(toRealPoint(head.coordinate), QPixmap(s));
        ++i;
        break;
    case Down:
        s = snakeSkinImgPathPrefix[mode] +"headDown_" + QString::number(i) +
            ".png"; pa.drawPixmap(toRealPoint(head.coordinate), QPixmap(s));
        ++i;
        break;
    case Left:
        s = snakeSkinImgPathPrefix[mode] +"headLeft_" + QString::number(i) +
            ".png"; pa.drawPixmap(toRealPoint(head.coordinate), QPixmap(s));
        ++i;
        break;
    case Right:
        s = snakeSkinImgPathPrefix[mode] +"headRight_" + QString::number(i) +
            ".png"; pa.drawPixmap(toRealPoint(head.coordinate), QPixmap(s));
        ++i;
        break;
    case UpLeft:
        pa.drawPixmap(toRealPoint(head.coordinate),
            QPixmap(snakeSkinImgPathPrefix[mode] +"headUpLeft.png"));
        i = 1;
        break;
    case LeftUp:
        pa.drawPixmap(toRealPoint(head.coordinate),
            QPixmap(snakeSkinImgPathPrefix[mode] +"headLeftUp.png"));
        i = 1;
        break;
    case RightUp:
        pa.drawPixmap(toRealPoint(head.coordinate),
            QPixmap(snakeSkinImgPathPrefix[mode] +"headRightUp.png"));
        i = 1;
        break;
    case UpRight:
        pa.drawPixmap(toRealPoint(head.coordinate),
            QPixmap(snakeSkinImgPathPrefix[mode] +"headUpRight.png"));
        i = 1;
        break;
    case LeftDown:
        pa.drawPixmap(toRealPoint(head.coordinate),
            QPixmap(snakeSkinImgPathPrefix[mode] +"headLeftDown.png"));
        i = 1;
        break;
    case DownLeft:
        pa.drawPixmap(toRealPoint(head.coordinate),
            QPixmap(snakeSkinImgPathPrefix[mode] +"headDownLeft.png"));
        i = 1;
        break;
    case DownRight:
        pa.drawPixmap(toRealPoint(head.coordinate),
            QPixmap(snakeSkinImgPathPrefix[mode] +"headDownRight.png"));
        i = 1;
        break;
    case RightDown:
        pa.drawPixmap(toRealPoint(head.coordinate),
            QPixmap(snakeSkinImgPathPrefix[mode] + "headRightDown.png"));
        i = 1;
        break;
    }

    pa.drawPixmap(toRealPoint(chessboard.getFoodCoordinate()),
        QPixmap(snakeSkinImgPathPrefix[mode] + "food.png"));

    lengthNumLabel->setNum(chessboard.snake.body.size());
    timeNumLabel->setNum(int(time));
    scoreNumLabel->setNum((chessboard.snake.body.size() - 4) * 10 + int(time));
}

void GameWidget::Init()
{    
    Init(40, 26);
}

void GameWidget::Init(int boardWidth, int boardHeight)
{
    chessboard.Init(boardWidth, boardHeight);
    pauseBtnPressed = false;
    pauseBtn->setIcon(QIcon(":/image/image/pauseBtn.png"));
    pauseBtn->setIconSize(QSize(200, 200));
    key = KeyRight;
    time = -0.2;
}

void GameWidget::setMuted(bool muted)
{
    dieSound->setMuted(muted);
    scoreSound->setMuted(muted);
    keyboardSound->setMuted(muted);
    pauseBtnSound->setMuted(muted);
}

void GameWidget::pauseBtnClicked()
{
    pauseBtnSound->setCurMusicIndex(musicPackIndex);
    pauseBtnSound->play();
    if(!pauseBtnPressed)
    {
        pauseBtn->setIcon(QIcon(":/image/image/continueBtn.png"));
        pauseBtn->setIconSize(QSize(200, 200));
        timer->stop();
    }
    else
    {
        pauseBtn->setIcon(QIcon(":/image/image/pauseBtn.png"));
        pauseBtn->setIconSize(QSize(200, 200));
        timer->start(200);
    }
    pauseBtnPressed = !pauseBtnPressed;
}

QPoint GameWidget::toRealPoint(QPoint point)
{
    switch (mode)
    {
    case 0:
        return QPoint(point.x() * 25 + 40 + 210, point.y() * 25 + 35);
    case 1:
        return QPoint(point.x() * 100 + 140 + 210, point.y() * 100 + 110);
    default:
        return point;
    }
}

void GameWidget::updateSnakeHead(int key)
{
    auto &head = chessboard.snake.body[0];
    char comingDirection;

    switch (head.state)
    {
    case Up:
    case DownLeft:
    case DownRight:
        comingDirection = 'D';
        break;
    case Down:
    case UpLeft:
    case UpRight:
        comingDirection = 'U';
        break;
    case Left:
    case RightUp:
    case RightDown:
        comingDirection = 'R';
        break;
    case Right:
    case LeftUp:
    case LeftDown:
        comingDirection = 'L';
        break;
    }
    switch (key)
    {
    case Qt::Key_Up:
    case Qt::Key_W:
        if(comingDirection == 'U' )
            head.state = Down;
        else if(comingDirection == 'D')
            head.state = Up;
        else if(comingDirection == 'L')
            head.state = LeftUp;
        else if(comingDirection == 'R')
            head.state = RightUp;
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        if(comingDirection == 'U')
            head.state = Down;
        else if(comingDirection == 'D')
            head.state = Up;
        else if(comingDirection == 'L')
            head.state = LeftDown;
        else if(comingDirection == 'R')
            head.state = RightDown;
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        if(comingDirection == 'L')
            head.state = Right;
        else if(comingDirection == 'R')
            head.state = Left;
        else if(comingDirection == 'U')
            head.state = UpLeft;
        else if(comingDirection == 'D')
            head.state = DownLeft;
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        if(comingDirection == 'L')
            head.state = Right;
        else if(comingDirection == 'R')
            head.state = Left;
        else if(comingDirection == 'U')
            head.state = UpRight;
        else if(comingDirection == 'D')
            head.state = DownRight;
        break;
    }
    update();
}

void GameWidget::startGame()
{
    int snakeState = chessboard.play(key);
    if(snakeState == 0)
    {
        dieSound->setCurMusicIndex(musicPackIndex);
        dieSound->play();

        timer->stop();
        if(mode == 1)
        {
            bool ok = false;
            QString nameStr;
            while (1)
            {
                QInputDialog *inputDlg = new QInputDialog(this);
                inputDlg->setWindowTitle(tr("提示"));
                inputDlg->setLabelText(tr("请输入您的尊姓大名："));
                inputDlg->setOkButtonText(tr("确定"));
                inputDlg->setCancelButtonText(tr("取消"));
                inputDlg->setTextValue(tr(""));
                Qt::WindowFlags flags = inputDlg->windowFlags();
                inputDlg->setWindowFlags(flags & (~Qt::WindowContextHelpButtonHint));
                if (inputDlg->exec())
                {
                    ok = true;
                    nameStr = inputDlg->textValue();
                }
                if(!ok)
                {
                    mainStackedWidget->setCurrentIndex(0);
                    bgmMusic->setCurMusicIndex(0);
                    return;
                }
                else if(nameStr.isEmpty() || nameStr.size() > 15)
                    QMessageBox::information(nullptr, tr("提示"),
                        tr("您的姓名长度须在1-15个字符之间"), QMessageBox::Ok);
                else
                {
                    RankData rankData;
                    rankData.appendData(nameStr,
                        (chessboard.snake.body.size() - 4) * 10 + int(time));
                    rankData.writeFile();

                    mainStackedWidget->setCurrentIndex(0);
                    bgmMusic->setCurMusicIndex(0);
                    return;
                }
            }
        }
        else
        {
            QMessageBox *msgBox = new QMessageBox(this);
            msgBox->setText(tr("      您输了！          "));
            msgBox->setWindowTitle(tr("提示"));
            msgBox->setStandardButtons(QMessageBox::Ok);
            msgBox->setButtonText(QMessageBox::Ok, tr("确定"));
            msgBox->exec();

            mainStackedWidget->setCurrentIndex(0);
            bgmMusic->setCurMusicIndex(0);
            return;
        }
    }
    if(snakeState == 2)
    {
        scoreSound->setCurMusicIndex(musicPackIndex);
        scoreSound->play();
        if(chessboard.snake.body.size() ==
            chessboard.getBoardWidth() * chessboard.getBoardHeight())
        {
            timer->stop();
            bool ok = false;
            QString nameStr;
            while (1)
            {
                QInputDialog *inputDlg = new QInputDialog(this);
                inputDlg->setWindowTitle(tr("提示"));
                inputDlg->setLabelText(tr("恭喜您通关，请输入您的尊姓大名："));
                inputDlg->setOkButtonText(tr("确定"));
                inputDlg->setCancelButtonText(tr("取消"));
                inputDlg->setTextValue(tr(""));
                Qt::WindowFlags flags = inputDlg->windowFlags();
                inputDlg->setWindowFlags(flags & (~Qt::WindowContextHelpButtonHint));
                if (inputDlg->exec())
                {
                    ok = true;
                    nameStr = inputDlg->textValue();
                }
                if(!ok)
                {
                    mainStackedWidget->setCurrentIndex(0);
                    bgmMusic->setCurMusicIndex(0);
                    return;
                }
                else if(nameStr.isEmpty() || nameStr.size() > 15)
                    QMessageBox::information(nullptr, tr("提示"),
                        tr("您的姓名长度须在1-15个字符之间"), QMessageBox::Ok);
                else
                {
                    RankData rankData;
                    rankData.appendData(nameStr,
                        (chessboard.snake.body.size() - 4) * 10 + int(time));
                    rankData.writeFile();

                    mainStackedWidget->setCurrentIndex(0);
                    bgmMusic->setCurMusicIndex(0);
                    return;
                }
            }
        }
    }
    time += 0.2;
    update();
}

