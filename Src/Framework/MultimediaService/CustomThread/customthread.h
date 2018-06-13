#ifndef CUSTOMTHREAD_H
#define CUSTOMTHREAD_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include <QDebug>

class CustomThreadPrivate;
class CustomThreadListener;
class CustomThread : public QObject
{
    Q_OBJECT
public:
    explicit CustomThread(QObject *parent = nullptr);
    ~CustomThread();
    void setListener(CustomThreadListener *listener);
    void start(int msec);
    void start();
    void stop();
    void stop(bool isSync);
    bool isRunning();

signals:
    void resultReady(const QString &result);
    void onFinish();

public slots:
private slots:
    void onTimeout();
private:
    friend class CustomThreadPrivate;
    QScopedPointer<CustomThreadPrivate> m_Private;
    QTimer *mQTimer = NULL;
    void stopTimer();
};

class CustomThreadListener {
public:
    virtual void onRun() = 0;
};


class CustomThreadPrivate : public QThread {
    Q_OBJECT
    Q_DISABLE_COPY(CustomThreadPrivate)
public:
    explicit CustomThreadPrivate(CustomThread *parent);
    ~CustomThreadPrivate();
    void setThreadListener(CustomThreadListener *listener);
    void startThread();
    void destroyeThread(bool isSync);
    bool isRunning = false;
protected:
    void run() Q_DECL_OVERRIDE;
signals:

private:
    CustomThread *m_Parent;
    CustomThreadListener *mListener = NULL;
};

#endif // CUSTOMTHREAD_H
