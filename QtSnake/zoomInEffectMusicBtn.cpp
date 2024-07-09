#include "zoomInEffectMusicBtn.h"

ZoomInEffectMusicBtn::ZoomInEffectMusicBtn(QWidget *parent): QPushButton(parent)
{
    setFlat(true);
    setStyleSheet(".ZoomInEffectMusicBtn{border: none; }");
    effectSoundList = new QMediaPlaylist;
    effectSoundList->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    effectSound = new QMediaPlayer;
    effectSound->setPlaylist(effectSoundList);
}

void ZoomInEffectMusicBtn::enterEvent(QEvent *event)
{
    this->setIconSize(QSize(iconSize.width() * 10 / 9,
        iconSize.height() * 10 / 9));
    effectSound->play();
}

void ZoomInEffectMusicBtn::leaveEvent(QEvent *event)
{
    this->setIconSize(iconSize);
}

void ZoomInEffectMusicBtn::setIconAndIconSize(QIcon icon,QSize iconSize)
{
    setIcon(icon);
    this->iconSize = iconSize;
    setIconSize(iconSize);
}

void ZoomInEffectMusicBtn::setEffectSound(QUrl soundUrl)
{
    effectSoundList->clear();
    effectSoundList->addMedia(soundUrl);
}

void ZoomInEffectMusicBtn::setMuted(bool muted)
{
    effectSound->setMuted(muted);
}
