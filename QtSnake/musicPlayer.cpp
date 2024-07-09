#include "musicPlayer.h"

MusicPlayer::MusicPlayer()
{
    musicList = new QMediaPlaylist;
    musicPlayer = new QMediaPlayer;
    musicPlayer->setPlaylist(musicList);
}

void MusicPlayer::play()
{
    musicPlayer->play();
}

void MusicPlayer::setCurMusicIndex(int index)
{
    musicList->setCurrentIndex(index);
}

void MusicPlayer::addMusic(QUrl musicUrl)
{
    musicList->addMedia(musicUrl);
}

void MusicPlayer::pause()
{
    musicPlayer->pause();
}

void MusicPlayer::stop()
{
    musicPlayer->stop();
}

void MusicPlayer::setPlayBackMode(QMediaPlaylist::PlaybackMode mode)
{
    musicList->setPlaybackMode(mode);
}

void MusicPlayer::setMuted(bool muted)
{
    musicPlayer->setMuted(muted);
}
