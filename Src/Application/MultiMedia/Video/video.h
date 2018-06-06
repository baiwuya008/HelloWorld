#ifndef VIDEO_H
#define VIDEO_H

#include "Src/Framework/Base/Core/activity.h"


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

class VideoPrivate :public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(VideoPrivate)
public:
    explicit VideoPrivate(Video* parent);
    ~VideoPrivate(){delete q_ptr;}
    void initializeBasicWidget(QWidget *parent);

private:
    Q_DECLARE_PUBLIC(Video)
    Video* const q_ptr;

    //----------
    BmpWidget *mBackground;
    BmpButton *mBtnTest;
    //----------
private slots:
    void onBtnTestRelease();

};

#endif // VIDEO_H
