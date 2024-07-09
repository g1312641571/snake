#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class MusicPlayer
{
public:
    MusicPlayer();
    void play();
    void setCurMusicIndex(int index);
    void addMusic(QUrl musicUrl);
    void pause();
    void stop();
    void setPlayBackMode(QMediaPlaylist::PlaybackMode mode);
    void setMuted(bool muted);

private:
    QMediaPlayer *musicPlayer;
    QMediaPlaylist *musicList;

};

#endif // BGMPLAYER_H
