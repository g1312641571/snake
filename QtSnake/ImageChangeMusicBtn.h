#ifndef IMAGECHANGEMUSICBTN_H
#define IMAGECHANGEMUSICBTN_H

#include "zoomInEffectMusicBtn.h"
#include <QVector>

class ImageChangeMusicBtn : public ZoomInEffectMusicBtn
{
    Q_OBJECT
public:
    ImageChangeMusicBtn(QWidget *parent = nullptr);
    inline int getCurIconIndex(){return curIconIndex;}
    void addIcon(QString iconFilePath);
    int getIconTotalNum();
    void changeToNextIcon();
    virtual void setIconAndIconSize(QString iconFilePath, QSize iconSize);


private:
    int curIconIndex;
    QVector<QString> icons;


};

#endif // IMAGECHANGEMUSICBTN_H
