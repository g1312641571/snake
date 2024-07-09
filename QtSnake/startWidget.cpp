#include "startWidget.h"
#pragma execution_character_set("utf-8")

StartWidget::StartWidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(1280, 720);

    setAutoFillBackground(true);
    bgImg = new QPixmap(":/image/image/background.png");
    snakeImg = new QPixmap(":/image/image/snake.png");
    snakeImgLabel = new QLabel(this);
    snakeImgLabel->setPixmap(*snakeImg);
    snakeImgLabel->setGeometry(160, 80, 200, 200);

    QPalette pal;
    if(!bgImg->isNull())
    {
        *bgImg = bgImg->scaled(1280, 720,
            Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        pal.setBrush(QPalette::Background, QBrush(*bgImg));
    }
    else
    {
        pal.setColor(QPalette::Background, Qt::blue);
    }
    this->setPalette(pal);

    startBtn = new ZoomInEffectMusicBtn(this);
    startBtn->setIconAndIconSize(QIcon(":/image/image/startBtn.png"),
        QSize(200, 92));
    startBtn->setEffectSound(QUrl("qrc:/music/music/button.mp3"));
    startBtn->setGeometry(120, 280, 300, 120);


    rankBtn = new ZoomInEffectMusicBtn(this);
    rankBtn->setIconAndIconSize(QIcon(":/image/image/rankBtn.png"),
        QSize(200, 92));
    rankBtn->setEffectSound(QUrl("qrc:/music/music/button.mp3"));
    rankBtn->setGeometry(120, 380, 300, 120);

    endBtn = new ZoomInEffectMusicBtn(this);
    endBtn->setIconAndIconSize(QIcon(":/image/image/endBtn.png"),
        QSize(200, 92));
    endBtn->setEffectSound(QUrl("qrc:/music/music/button.mp3"));
    endBtn->setGeometry(120, 480, 300, 120);

    musicControlBtn = new ImageChangeMusicBtn(this);
    musicControlBtn->setIconAndIconSize(":/image/image/musicalNoteClassic.png",
        QSize(120, 120));
    musicControlBtn->addIcon(":/image/image/musicalNoteGay.png");
    musicControlBtn->addIcon(":/image/image/musicalNoteMute.png");
    musicControlBtn->setEffectSound(QUrl("qrc:/music/music/button.mp3"));
    musicControlBtn->setGeometry(1110, 550, 200, 200);

    modeChangeBtn = new ImageChangeMusicBtn(this);
    modeChangeBtn->setIconAndIconSize(":/image/image/casualModeBtn.png", QSize(120, 120));
    modeChangeBtn->addIcon(":/image/image/competitiveModeBtn.png");
    modeChangeBtn->setEffectSound(QUrl("qrc:/music/music/button.mp3"));
    modeChangeBtn->setGeometry(1110, 400, 200, 200);

}

void StartWidget::setMuted(bool muted)
{
    startBtn->setMuted(muted);
    rankBtn->setMuted(muted);
    endBtn->setMuted(muted);
    musicControlBtn->setMuted(muted);
    modeChangeBtn->setMuted(muted);
}
