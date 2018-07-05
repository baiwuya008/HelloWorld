#ifndef RADIOSERVICE_H
#define RADIOSERVICE_H

#include <QObject>
#include <QThread>
#include "Src/Framework/Manager/RadioUnit.h"
#include "configuration.h"
#if(COMPILE_IN_SERVICE == 1)
#include "Libs/Etal/etal_api.h"
#else
typedef unsigned int            tU32;
typedef unsigned int            ETAL_EVENTS;
#endif

// nominal step default
#define ETAL_FM_FREQ_STEP 100   //KHz 0.1MHz
#define ETAL_AM_FREQ_STEP 9   //KHz


#ifdef gRadioService
#undef gRadioService
#endif
#define gRadioService RadioService::instance()


class RadioServicePrivate;
class ScanThread;
class RadioService : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(RadioService)
public:
    explicit RadioService(QObject *parent = 0);
    static BAND mCurBand;
    static unsigned int mStartFreq;

    bool SetBand(BAND band);
    bool SetFrequency(BAND band,tU32 freq); //Khz
    bool Seek(BAND band,DIRECT dir);
    bool StopSeek(BAND band);
    bool Scan(BAND band);
    bool StopScan(BAND band);
    tU32 GetFrequency(BAND band); //Khz
    bool SelectRadioAudio();
    bool RadioInit();


    bool setScanningState(bool on);
    bool setSeekingState(bool on);
    bool getScanningState();
    bool getSeekingState();

    bool notifySeekFoundOrFinish(BAND band,int freq);
    bool notifyScanFoundOne(BAND band,int freq);
    bool notifyScanFoundFinish(BAND band);



    static void nativeCallBackByEtal(void *context, ETAL_EVENTS dwEvent, void *pstatus);
    static RadioService * instance();

signals:
    void updateCurFrequency(BAND band,int freq); //Khz
    void updateFrequencyList(BAND band,QList<int> lists); //Khz

public slots:


private:
    Q_DECLARE_PRIVATE(RadioService)
    RadioServicePrivate * const d_ptr;
    static RadioService *mSelf;
    friend class ScanThread;


    static bool nativeSetBand(BAND band);
    static bool nativeSetFrequency(BAND band,tU32 freq); //Khz
    static bool nativeSeek(BAND band,DIRECT dir);
    static bool nativeStopSeek(BAND band);
    static bool nativeScan(BAND band);
    static bool nativeStopScan(BAND band);
    static tU32 nativeGetFrequency(BAND band); //Khz
    static bool nativeSelectRadioAudio();
    static bool nativeEtalInit();
    static bool nativeEtalDeInit();


};

//----------------Scan数据线程
class ScanThreadPrivate;
class ScanThread : public QThread
{
    Q_OBJECT
    Q_DISABLE_COPY(ScanThread)
public:
    explicit ScanThread(QObject *parent = 0);
    void safeExit();

protected:
    void run();

signals:

public slots:

private:
    Q_DECLARE_PRIVATE(ScanThread)
    ScanThreadPrivate * const d_ptr;

};


#endif // RADIOSERVICE_H
