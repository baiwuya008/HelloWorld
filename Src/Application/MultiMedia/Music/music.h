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
    ~MusicPrivate(){delete q_ptr;}
    void initializeBasicWidget(QWidget *parent);
private slots:
    void setCurrentPageView(int tabIndex);
    void onSelectItem(QString filePath, int index);

    void playMusic(const int mediaType, const int index,
                      const QString &fileName, const qint64 endTime);
    void pauseMusic(const int mediaType);
    void updateMusic(const int mediaType, const QString& title,
                       const QString& artist, const QString& album);
    void resumeMusic(const int mediaType);
    void stopMusic(const int mediaType);
    void setPlayModeMusic(const int mediaType, const int playMode);
    void updateProgressMusic(const int mediaType, const qint64 currentPosition, const qint64 duration);


    void scanMusicFiles(int deviceType, QStringList& pathList);

private:
    Q_DECLARE_PUBLIC(Music)
    Music* const q_ptr;

     void setWidgetBackground(QWidget *widget, QString path);

    void initializeToolsWidget(QWidget *parent);
    void initializePlayView(QWidget *parent);
    void initializeListView(QWidget *parent);
    MediaToolsWidget *mMediaToolsWidget = NULL;
    MusicPlayWidget *mMusicPlayWidget = NULL;
    MusicListWidget *mMusicListWidget = NULL;
    QStackedWidget *mStackedWidget = NULL;


    void connectAllSlots();

    //----------
    BmpWidget *mBackground;
    BmpButton *mBtnTest;
    //----------
private slots:
    void onBtnTestRelease();

};

#endif // MUSIC_H
