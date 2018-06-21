#include "customthread.h"


CustomThread::CustomThread(QObject *parent)
    : QObject(parent)
    , m_Private(new CustomThreadPrivate(this))
{
    mQTimer = new QTimer(this);
    mQTimer->setSingleShot(true);//这个设置触发单次调用,不会循环一直调用
    connect(mQTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

CustomThread::~CustomThread()
{
    stopTimer();
    mQTimer = NULL;
}

void CustomThread::setListener(CustomThreadListener *listener)
{
    m_Private->setThreadListener(listener);
}

void CustomThread::start(int msec)
{
    if (mQTimer != NULL) {
        mQTimer->start(msec);
    }
}

void CustomThread::start()
{
    stopTimer();
    m_Private->startThread();
}

void CustomThread::stop()
{
    stop(false);
}

void CustomThread::stop(bool isSync)
{
    stopTimer();
    m_Private->destroyeThread(isSync);
}

bool CustomThread::isRunning()
{
    return m_Private->isRunning;
}

void CustomThread::onTimeout()
{
    start();
}

void CustomThread::stopTimer()
{
    if (mQTimer != NULL && mQTimer->isActive()) {
        mQTimer->stop();
    }
}


void CustomThreadPrivate::setThreadListener(CustomThreadListener *listener)
{
    this->mListener = listener;
}

void CustomThreadPrivate::startThread()
{
    if (isRunning) {
        return;
    }

    isRunning = true;
    this->start();
}

void CustomThreadPrivate::destroyeThread(bool isSync)
{
    this->quit();
    if (isSync) {
        this->wait();
    }
    isRunning = false;
}

void CustomThreadPrivate::run() {
    if (mListener != NULL) {
        mListener->onRun();
    }

    emit m_Parent->resultReady("run finish");
}

CustomThreadPrivate::CustomThreadPrivate(CustomThread *parent) : m_Parent(parent)
{
    isRunning = false;
    connect(this, &CustomThreadPrivate::finished, m_Parent, &QObject::deleteLater);
    connect(this, &CustomThreadPrivate::finished, m_Parent, &CustomThread::onFinish);
}

CustomThreadPrivate::~CustomThreadPrivate()
{
    mListener = NULL;
    m_Parent = NULL;
    isRunning = false;
}













