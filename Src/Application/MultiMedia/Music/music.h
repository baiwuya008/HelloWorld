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
#include "Src/Application/MultiMedia/Tools/mediatoolswidget.h"
#include "Src/Application/MultiMedia/multimedia.h"


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
    ~MusicPrivate();
    void initializeBasicWidget(QWidget *parent);
private slots:
    void setCurrentPageView(int tabIndex);

    void backPlay(const int mediaType, const int index, QString path, const qint64 duration);
    void backPause(const int mediaType);
    void backResume(const int mediaType);
    void backStop(const int mediaType, bool isError);
    void backPlayMode(const int mediaType, const int playMode);
    void backProgress(const int mediaType, const qint64 currentPosition, const qint64 duration);
    void backScanFiles(int deviceType, int queryMode, QString dirPath, QStringList& pathList);

    void setPlayItem(int deviceType, QString filePath);
    void setPlayStatus(bool isPlay);
    void setPlayMode(int mode);
    void setPlayIndex(bool isNext);
    void setPlayProgress(int progress);

private:
    Q_DECLARE_PUBLIC(Music)
    Music* const q_ptr;

    void initializeToolsWidget(QWidget *parent);
    void initializePlayView(QWidget *parent);
    void initializeListView(QWidget *parent);
    void connectAllSlots();

    MediaToolsWidget *mMediaToolsWidget = NULL;
    MusicPlayWidget *mMusicPlayWidget = NULL;
    MusicListWidget *mMusicListWidget = NULL;
    QStackedWidget *mStackedWidget = NULL;

    int mCurrentDeviceType = -1;
private slots:
    void onBtnTestRelease();

};

#endif // MUSIC_H
