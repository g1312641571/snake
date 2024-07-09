#include "ImageChangeMusicBtn.h"

ImageChangeMusicBtn::ImageChangeMusicBtn(QWidget *parent):
    ZoomInEffectMusicBtn(parent)
{
    setStyleSheet(".ImageChangeMusicBtn{border: none; }");
    curIconIndex = 0;
}

void ImageChangeMusicBtn::addIcon(QString iconFilePath)
{
    icons.push_back(iconFilePath);
}

int ImageChangeMusicBtn::getIconTotalNum()
{
    return icons.size();
}

void ImageChangeMusicBtn::changeToNextIcon()
{
    curIconIndex = ++curIconIndex % getIconTotalNum();
    setIcon(QIcon(icons[curIconIndex]));
    setIconSize(iconSize);
}

void ImageChangeMusicBtn::setIconAndIconSize(QString iconFilePath, QSize iconSize)
{
    this->iconSize = iconSize;
    setIcon(QIcon(iconFilePath));
    setIconSize(iconSize);
    icons.push_back(iconFilePath);
}
