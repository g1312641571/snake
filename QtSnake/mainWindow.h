#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "startWidget.h"
#include "gameWidget.h"
#include "rankWidget.h"
#include <QMainWindow>
#include <QStackedWidget>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QApplication>
#include <QMessageBox>
#include "musicPlayer.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();
    void setMuted(bool muted);

    MusicPlayer *bgmPlayer;


private slots:
    void endBtnClicked();
    void startBtnClicked();
    void rankBtnClicked();
    void musicControlBtnClicked();
    void modeChangeBtnClicked();


private:
    StartWidget *startWidget;
    GameWidget *gameWidget;
    RankWidget *rankWidget;
    QStackedWidget *mainStackedWidget;

    MusicPlayer *btnMusic;

    void musicChange(int index);
    void setMusicMute(bool muted);

};

#endif // MAINWINDOW_H
