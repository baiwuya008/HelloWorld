#ifndef VIDEO_H
#define VIDEO_H

#include "Src/Framework/Base/Core/activity.h"

#include <QStackedWidget>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QDebug>
#include <QPushButton>

#include "Src/Application/MultiMedia/Tools/mediatoolswidget.h"
#include "videoplaywidget.h"
#include "Src/Application/MultiMedia/Music/musiclistwidget.h"
#include "Src/Application/MultiMedia/multimedia.h"

class VideoPrivate;
class Video : public Activity
{
    Q_OBJECT
    Q_DISABLE_COPY(Video)

public:

    Video(QObject *parent = 0);

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

private:
    Q_DECLARE_PRIVATE(Video)
    VideoPrivate* const d_ptr;

};

class VideoPrivate : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(VideoPrivate)
public:
    explicit VideoPrivate(Video* parent);
    ~VideoPrivate(){delete q_ptr;}
    void initializeBasicWidget(QWidget *parent);


private slots:
    void setCurrentPageView(int tabIndex);

    void setPlayItem(int deviceType, QString filePath);
    void setPlayStatus(bool isPlay);
    void setPlayIndex(bool isNext);
    void setPlaySeek(int progress);


    void playVideo(const int mediaType, const int index,
                   const QString &filePath, const qint64 duration);
    void pauseVideo(const int mediaType);
    void resumeVideo(const int mediaType);
    void stopVideo(const int mediaType, bool isError);
    void updateProgress(const int mediaType, const qint64 currentPosition, const qint64 duration);
    void scanVideoFiles(int deviceType, int queryMode, QString dirPath, QStringList& pathList);


protected slots:
    void backFinish();

private:
    Q_DECLARE_PUBLIC(Video)
    Video* const q_ptr;

    void initializeToolsWidget(QWidget *parent);
    void initializeVideoPlay(QWidget *parent);
    void initializeVideoList(QWidget *parent);
    void connectAllSlots();

    QStackedWidget *mStackedWidget = NULL;
    MediaToolsWidget *mMediaToolsWidget = NULL;
    MusicListWidget *mVideoListWidget = NULL;
    VideoPlayWidget *mVideoPlayWidget = NULL;
    int mCurrentDeviceType = -1;


    //----------
    BmpWidget *mBackground;
    BmpButton *mBtnTest;
    //----------
private slots:
    void onBtnTestRelease();

};

#endif // VIDEO_H
