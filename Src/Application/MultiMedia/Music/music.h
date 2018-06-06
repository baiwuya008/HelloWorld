#ifndef MUSIC_H
#define MUSIC_H

#include <QStackedWidget>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QDebug>
#include <QPushButton>

#include "Src/Framework/Base/Core/activity.h"

#include "musicclickwidget.h"
#include "musiclistitem.h"
#include "musiclistwidget.h"
#include "musicplaywidget.h"
#include "musicprogresswidget.h"


class MusicPrivate;
class Music : public Activity
{
    Q_OBJECT
    Q_DISABLE_COPY(Music)

public:

    Music(QObject *parent = 0);

    void onCreate(QWidget *parent=0);
    void onStart();
    void onResume();
    void onPause();
    void onStop();
    void onDestroy();
    bool onBackPressed();
    void onLanguageChanged();
    void onReceiveBroadcast(AppType appType,OMessage &msg);
    void onReceiveCmd(AppType appType,OMessage &msg);

private slots:
    void onClick();

private:
    Q_DECLARE_PRIVATE(Music)
    MusicPrivate* const d_ptr;

};

class MusicPrivate :public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(MusicPrivate)
public:
    explicit MusicPrivate(Music* parent);
    ~MusicPrivate(){delete q_ptr;}
    void initializeBasicWidget(QWidget *parent);
private slots:
    void onClick(QString objectName);

private:
    Q_DECLARE_PUBLIC(Music)
    Music* const q_ptr;

    void initializePlayView(QWidget *parent);
    void initializeListView(QWidget *parent);
    MusicPlayWidget *mMusicPlayWidget = NULL;
    MusicListWidget *mMusicListWidget = NULL;
    QStackedWidget *mStackedWidget = NULL;


    void initializeToolsWidget(QWidget *parent);
    void setWidgetBackground(QWidget *widget, QString path);
    void setCurrentPageView(int tabIndex);
    QList<QPushButton*> btnList;

    //----------
    BmpWidget *mBackground;
    BmpButton *mBtnTest;
    //----------
private slots:
    void onBtnTestRelease();

};

#endif // MUSIC_H
