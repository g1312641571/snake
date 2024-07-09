#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QPalette>
#include "zoomInEffectMusicBtn.h"
#include "ImageChangeMusicBtn.h"

class StartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StartWidget(QWidget *parent = nullptr);
    ImageChangeMusicBtn *musicControlBtn;
    ImageChangeMusicBtn *modeChangeBtn;
    ZoomInEffectMusicBtn *startBtn;
    ZoomInEffectMusicBtn *rankBtn;
    ZoomInEffectMusicBtn *endBtn;

    void setMuted(bool muted);


private:

    QPixmap *bgImg;

    QLabel *snakeImgLabel;
    QPixmap *snakeImg;



};

#endif // STARTWIDGET_H
