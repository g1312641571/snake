#ifndef ZoomInEffectMusicBtn_H
#define ZoomInEffectMusicBtn_H

#include <QPushButton>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class ZoomInEffectMusicBtn : public QPushButton
{
    Q_OBJECT
public:
    explicit ZoomInEffectMusicBtn(QWidget *parent = nullptr);

protected:
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);

public:
    void setIconAndIconSize(QIcon icon, QSize iconSize);
    void setEffectSound(QUrl soundUrl);
    void setMuted(bool muted);

protected:
    //Icon
    QSize iconSize;

    //Music
    QMediaPlayer *effectSound;
    QMediaPlaylist *effectSoundList;

};

#endif // ZoomInEffectMusicBtn_H
