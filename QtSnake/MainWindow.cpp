#include "mainWindow.h"
#pragma execution_character_set("utf-8")

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //Music
    bgmPlayer = new MusicPlayer;
    bgmPlayer->setPlayBackMode(QMediaPlaylist::CurrentItemInLoop);
    bgmPlayer->addMusic(QUrl("qrc:/music/music/maintheme.mp3"));
    bgmPlayer->addMusic(QUrl("qrc:/music/music/untitled.mp3"));
    bgmPlayer->play();
    btnMusic = new MusicPlayer;
    btnMusic->setPlayBackMode(QMediaPlaylist::CurrentItemOnce);
    btnMusic->addMusic(QUrl("qrc:/music/music/button2.mp3"));

    //All game widgets
    mainStackedWidget = new QStackedWidget;
    startWidget = new StartWidget;
    mainStackedWidget->addWidget(startWidget);
    setCentralWidget(mainStackedWidget);
    gameWidget = new GameWidget;
    gameWidget->mainStackedWidget = mainStackedWidget;
    mainStackedWidget->addWidget(gameWidget);
    gameWidget->bgmMusic = bgmPlayer;
    rankWidget = new RankWidget;
    rankWidget->mainStackedWidget = mainStackedWidget;
    mainStackedWidget->addWidget(rankWidget);

    //Set property
    menuBar()->hide();
    setFixedSize(1280, 720);

    modeChangeBtnClicked();

    //Signal
    connect(startWidget->startBtn, SIGNAL(clicked()), this, SLOT(startBtnClicked()));
    connect(startWidget->endBtn, SIGNAL(clicked()), this, SLOT(endBtnClicked()));
    connect(startWidget->rankBtn, SIGNAL(clicked()), this, SLOT(rankBtnClicked()));
    connect(startWidget->musicControlBtn, SIGNAL(clicked()), this, SLOT(musicControlBtnClicked()));
    connect(startWidget->modeChangeBtn, SIGNAL(clicked()), this, SLOT(modeChangeBtnClicked()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::setMuted(bool muted)
{
    bgmPlayer->setMuted(muted);
    btnMusic->setMuted(muted);
}

void MainWindow::endBtnClicked()
{
    QApplication::quit();
}

void MainWindow::startBtnClicked()
{
    btnMusic->setCurMusicIndex(0);
    btnMusic->play();
    if(startWidget->modeChangeBtn->getCurIconIndex() == 0)
        gameWidget->Init();
    else if(startWidget->modeChangeBtn->getCurIconIndex() == 1)
    {
        gameWidget->Init(8, 5);
    }
    gameWidget->startTime();
    mainStackedWidget->setCurrentIndex(1);
    bgmPlayer->setCurMusicIndex(1);
}

void MainWindow::rankBtnClicked()
{
    btnMusic->setCurMusicIndex(0);
    btnMusic->play();
    rankWidget->readFile();
    mainStackedWidget->setCurrentIndex(2);
}

void MainWindow::musicControlBtnClicked()
{
    startWidget->musicControlBtn->changeToNextIcon();
    int index = startWidget->musicControlBtn->getCurIconIndex();
    if(index == startWidget->musicControlBtn->getIconTotalNum() - 1)
    {
        setMusicMute(true);
    }
    else if(index == 0)
    {
        setMusicMute(false);
        musicChange(0);
    }
    else
    {
        musicChange(index);
    }
}

void MainWindow::modeChangeBtnClicked()
{
    startWidget->modeChangeBtn->changeToNextIcon();
    gameWidget->setMode(startWidget->modeChangeBtn->getCurIconIndex());
}



void MainWindow::musicChange(int index)
{
    gameWidget->setMusicPackIndex(index);
}

void MainWindow::setMusicMute(bool muted)
{
    this->setMuted(muted);
    startWidget->setMuted(muted);
    rankWidget->setMuted(muted);
    gameWidget->setMuted(muted);

}

