#include "rankWidget.h"
#pragma execution_character_set("utf-8")

RankWidget::RankWidget(QWidget *parent) : QWidget(parent)
{
    // 排版
    setFixedSize(1280, 720);
    setAutoFillBackground(true);
    img = new QPixmap(":/image/image/rankBackground.jpg");
    QPalette pal;
    if(!img->isNull())
    {
        *img = img->scaled(1280, 720,
            Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        pal.setBrush(QPalette::Background, QBrush(*img));
    }
    else
    {
        pal.setColor(QPalette::Background, Qt::blue);
    }
    this->setPalette(pal);

    imgRankLabel_1 = new QLabel;
    *img = QPixmap(":/image/image/rank1_70.png");
    imgRankLabel_1->setPixmap(*img);
    imgRankLabel_2 = new QLabel;
    *img = QPixmap(":/image/image/rank2_70.png");
    imgRankLabel_2->setPixmap(*img);
    imgRankLabel_3 = new QLabel;
    *img = QPixmap(":/image/image/rank3_70.png");
    imgRankLabel_3->setPixmap(*img);
    imgRankLabel_4 = new QLabel;
    *img = QPixmap(":/image/image/rank4_70.png");
    imgRankLabel_4->setPixmap(*img);
    imgRankLabel_5 = new QLabel;
    *img = QPixmap(":/image/image/rank5_70.png");
    imgRankLabel_5->setPixmap(*img);
    imgRankLayout = new QVBoxLayout;
    imgRankLayout->addWidget(imgRankLabel_1, 1);
    imgRankLayout->addWidget(imgRankLabel_2, 1);
    imgRankLayout->addWidget(imgRankLabel_3, 1);
    imgRankLayout->addWidget(imgRankLabel_4, 1);
    imgRankLayout->addWidget(imgRankLabel_5, 1);

    nameLabel_1 = new QLabel;
    nameLabel_2 = new QLabel;
    nameLabel_3 = new QLabel;
    nameLabel_4 = new QLabel;
    nameLabel_5 = new QLabel;
    nameLayout = new QVBoxLayout;
    nameLayout->addWidget(nameLabel_1, 1);
    nameLayout->addWidget(nameLabel_2, 1);
    nameLayout->addWidget(nameLabel_3, 1);
    nameLayout->addWidget(nameLabel_4, 1);
    nameLayout->addWidget(nameLabel_5, 1);

    scoreLabel_1 = new QLabel;
    scoreLabel_2 = new QLabel;
    scoreLabel_3 = new QLabel;
    scoreLabel_4 = new QLabel;
    scoreLabel_5 = new QLabel;
    scoreRankLayout = new QVBoxLayout;
    scoreRankLayout->addWidget(scoreLabel_1, 1);
    scoreRankLayout->addWidget(scoreLabel_2, 1);
    scoreRankLayout->addWidget(scoreLabel_3, 1);
    scoreRankLayout->addWidget(scoreLabel_4, 1);
    scoreRankLayout->addWidget(scoreLabel_5, 1);

    returnBtn = new ZoomInEffectMusicBtn(this);
    returnBtn->setIconAndIconSize(QIcon(":/image/image/returnButton.png"),
        QSize(300, 92));
    returnBtn->setEffectSound(QUrl("qrc:/music/music/button.mp3"));
    returnBtn->setGeometry(870, 590, 300, 100);

    mainWidget = new QWidget(this);
    mainLayout = new QHBoxLayout(mainWidget);
    mainLayout->addLayout(imgRankLayout, 120);
    mainLayout->addLayout(nameLayout, 200);
    mainLayout->addLayout(scoreRankLayout, 200);
    mainWidget->setGeometry(700, 30, 500, 450);


    //设置文字样式
    QFont font("黑体", 24);
    nameLabel_1->setFont(font);
    scoreLabel_1->setFont(font);
    nameLabel_2->setFont(font);
    scoreLabel_2->setFont(font);
    nameLabel_3->setFont(font);
    scoreLabel_3->setFont(font);
    nameLabel_4->setFont(font);
    scoreLabel_4->setFont(font);
    nameLabel_5->setFont(font);
    scoreLabel_5->setFont(font);
    nameLabel_1->setAlignment(Qt::AlignCenter);
    scoreLabel_1->setAlignment(Qt::AlignCenter);
    nameLabel_2->setAlignment(Qt::AlignCenter);
    scoreLabel_2->setAlignment(Qt::AlignCenter);
    nameLabel_3->setAlignment(Qt::AlignCenter);
    scoreLabel_3->setAlignment(Qt::AlignCenter);
    nameLabel_4->setAlignment(Qt::AlignCenter);
    scoreLabel_4->setAlignment(Qt::AlignCenter);
    nameLabel_5->setAlignment(Qt::AlignCenter);
    scoreLabel_5->setAlignment(Qt::AlignCenter);

    effectSound = new MusicPlayer;
    effectSound->addMusic(QUrl("qrc:/music/music/button2.mp3"));
    effectSound->setPlayBackMode(QMediaPlaylist::CurrentItemOnce);


    connect(returnBtn, SIGNAL(clicked()), this, SLOT(returnBtnClicked()));

}

void RankWidget::readFile()
{
    RankData rankData;
    nameLabel_1->setText(rankData.getName(1));
    scoreLabel_1->setText(QString::number(rankData.getScore(1)));
    nameLabel_2->setText(rankData.getName(2));
    scoreLabel_2->setText(QString::number(rankData.getScore(2)));
    nameLabel_3->setText(rankData.getName(3));
    scoreLabel_3->setText(QString::number(rankData.getScore(3)));
    nameLabel_4->setText(rankData.getName(4));
    scoreLabel_4->setText(QString::number(rankData.getScore(4)));
    nameLabel_5->setText(rankData.getName(5));
    scoreLabel_5->setText(QString::number(rankData.getScore(5)));
}

void RankWidget::setMuted(bool muted)
{
    effectSound->setMuted(muted);
    returnBtn->setMuted(muted);
}

void RankWidget::returnBtnClicked()
{
    effectSound->setCurMusicIndex(0);
    effectSound->play();
    mainStackedWidget->setCurrentIndex(0);
}
