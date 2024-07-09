#ifndef RANKWIDGET_H
#define RANKWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPalette>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRect>
#include <QFile>
#include <QTextStream>
#include <QtAlgorithms>
#include <QFont>
#include <QPushButton>
#include <QStackedWidget>
#include "zoomInEffectMusicBtn.h"
#include "rankData.h"
#include "musicPlayer.h"

class RankWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RankWidget(QWidget *parent = nullptr);

    void readFile();

public:
    QStackedWidget *mainStackedWidget;
    void setMuted(bool muted);


signals:

private slots:
    void returnBtnClicked();

private:
    QPixmap *img;
    QLabel *imgRankLabel_1;
    QLabel *imgRankLabel_2;
    QLabel *imgRankLabel_3;
    QLabel *imgRankLabel_4;
    QLabel *imgRankLabel_5;

    QLabel *nameLabel_1;
    QLabel *nameLabel_2;
    QLabel *nameLabel_3;
    QLabel *nameLabel_4;
    QLabel *nameLabel_5;

    QLabel *scoreLabel_1;
    QLabel *scoreLabel_2;
    QLabel *scoreLabel_3;
    QLabel *scoreLabel_4;
    QLabel *scoreLabel_5;

    QVBoxLayout *imgRankLayout;
    QVBoxLayout *nameLayout;
    QVBoxLayout *scoreRankLayout;

    QHBoxLayout *mainLayout;
    QWidget *mainWidget;

    //Music
    MusicPlayer *effectSound;
    ZoomInEffectMusicBtn *returnBtn;




};

#endif // RANKWIDGET_H
