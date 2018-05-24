#ifndef IMAGE_H
#define IMAGE_H

#include "Src/Framework/Base/Core/activity.h"


class ImagePrivate;
class Image : public Activity
{
    Q_OBJECT
    Q_DISABLE_COPY(Image)

public:

    Image(QObject *parent = 0);

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
    Q_DECLARE_PRIVATE(Image)
    ImagePrivate* const d_ptr;

};

class ImagePrivate :public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ImagePrivate)
public:
    explicit ImagePrivate(Image* parent);
    ~ImagePrivate(){delete q_ptr;}
    void initializeBasicWidget(QWidget *parent);

private:
    Q_DECLARE_PUBLIC(Image)
    Image* const q_ptr;

    //----------
    BmpWidget *mBackground;
    BmpButton *mBtnTest;
    //----------
private slots:
    void onBtnTestRelease();

};

#endif // IMAGE_H
