#include "RadioService.h"
#include <QDebug>

class RadioServicePrivate{
    Q_DISABLE_COPY(RadioServicePrivate)
public:
    explicit RadioServicePrivate(RadioService *parent);
    ~RadioServicePrivate();
private:
    Q_DECLARE_PUBLIC(RadioService)
    RadioService * const q_ptr;
    bool mIsSeeking;
    bool mIsScanning;
    ScanThread *mScanthread;
    QList<int> *mScanStoreFreqs;

};

RadioServicePrivate::RadioServicePrivate(RadioService *parent)
    :q_ptr(parent)
{
   mIsSeeking = false;
   mIsScanning = false;
   mScanthread = NULL;
   mScanStoreFreqs = NULL;
}

//----------

//--------------------------
RadioService::RadioService(QObject *parent) :
    QObject(parent),d_ptr(new RadioServicePrivate(this))
{

}


bool RadioService::nativeSetBand(BAND band){
    qDebug()<< "RadioService::nativeSetBand() +++"<<QString("Band= %1").arg((band==BAND_AM)?"AM":"FM")<<endl;
#if (COMPILE_IN_SERVICE == 1)
    ETAL_HANDLE vl_handle = ETAL_INVALID_HANDLE;
    ETAL_STATUS ret;
    EtalReceiverAttr attr;

    if(band == BAND_AM){
       ret = etaltml_getFreeReceiverForPath(&vl_handle, ETAL_PATH_NAME_AM, &attr);
    }else{
       ret = etaltml_getFreeReceiverForPath(&vl_handle, ETAL_PATH_NAME_FM_FG, &attr);
    }
    if (ETAL_RET_SUCCESS != ret)
    {
        qDebug()<< QString("etaltml_getFreeReceiverForPath %1 ERROR (%2)").arg((band == BAND_AM)?"AM":"FM").arg(ret)<<endl;
        return 0;
    }

    EtalProcessingFeatures processingFeatures;
    processingFeatures.u.m_processing_features = ETAL_PROCESSING_FEATURE_NONE;
    EtalFrequencyBand FMBand=ETAL_BAND_FM;
    if(band = BAND_AM){
        FMBand=ETAL_BAND_AM;
    }
    if ((ret = etal_change_band_receiver(vl_handle, FMBand, 0, 0, processingFeatures)) != ETAL_RET_SUCCESS)
    {
        qDebug()<< QString("etal_change_band_receiver %1 ERROR").arg((band == BAND_AM)?"AM":"FM")<<endl;
        return false;
    }
    else
    {
        qDebug()<< QString("etal_change_band_receiver %1 ok").arg((band == BAND_AM)?"AM":"FM")<<endl;
    }
#endif
    qDebug()<< "RadioService::nativeSetBand() ---"<<endl;
    return true;
}

bool RadioService::nativeSetFrequency(BAND band,tU32 freq){//Khz
    qDebug()<< "RadioService::nativeSetFrequency() +++"<<QString("Band= %1,Freq= %2").arg((band==BAND_AM)?"AM":"FM").arg(freq)<<endl;
#if (COMPILE_IN_SERVICE == 1)
    ETAL_HANDLE vl_handle = ETAL_INVALID_HANDLE;
    ETAL_STATUS ret;
    EtalReceiverAttr attr;

    if(band == BAND_AM){
       ret = etaltml_getFreeReceiverForPath(&vl_handle, ETAL_PATH_NAME_AM, &attr);
    }else{
       ret = etaltml_getFreeReceiverForPath(&vl_handle, ETAL_PATH_NAME_FM_FG, &attr);
    }
    if (ETAL_RET_SUCCESS != ret)
    {
        qDebug()<< QString("etaltml_getFreeReceiverForPath %1 ERROR (%2)").arg((band == BAND_AM)?"AM":"FM").arg(ret)<<endl;
        return 0;
    }

    EtalProcessingFeatures processingFeatures;
    processingFeatures.u.m_processing_features = ETAL_PROCESSING_FEATURE_NONE;
    EtalFrequencyBand FMBand=ETAL_BAND_FM;
    if(band = BAND_AM){
        FMBand=ETAL_BAND_AM;
    }
    if ((ret = etal_change_band_receiver(vl_handle, FMBand, 0, 0, processingFeatures)) != ETAL_RET_SUCCESS)
    {
        qDebug()<< QString("etal_change_band_receiver %1 ERROR").arg((band == BAND_AM)?"AM":"FM")<<endl;
        return false;
    }
    else
    {
        qDebug()<< QString("etal_change_band_receiver %1 ok").arg((band == BAND_AM)?"AM":"FM")<<endl;
    }


    ret = etal_tune_receiver(vl_handle, freq);

    if (ETAL_RET_SUCCESS != ret)
    {
        qDebug()<< QString("ERROR: etal_tune_receiver %1 (%2)").arg((band == BAND_AM)?"AM":"FM").arg(ret)<<endl;
        return false;
    }
    else
    {
        qDebug()<< QString("etal_tune_receiver %1 ok, freq = %2").arg((band == BAND_AM)?"AM":"FM").arg(freq)<<endl;
    }

#endif
    qDebug()<< "RadioService::nativeSetFrequency() ---"<<endl;
    return true;
}

bool RadioService::nativeSeek(BAND band,DIRECT dir){
    qDebug()<< "RadioService::nativeSeek() +++"<<QString("Band= %1,Dir=%2").arg((band==BAND_AM)?"AM":"FM").arg((dir==DIR_UP)?"UP":"DOWN")<<endl;
#if (COMPILE_IN_SERVICE == 1)
    ETAL_HANDLE vl_handle = ETAL_INVALID_HANDLE;
    ETAL_STATUS ret;
    EtalReceiverAttr attr;

    if(band == BAND_AM){
       ret = etaltml_getFreeReceiverForPath(&vl_handle, ETAL_PATH_NAME_AM, &attr);
    }else{
       ret = etaltml_getFreeReceiverForPath(&vl_handle, ETAL_PATH_NAME_FM_FG, &attr);
    }
    if (ETAL_RET_SUCCESS != ret)
    {
        qDebug()<< QString("etaltml_getFreeReceiverForPath %1 ERROR (%2)").arg((band == BAND_AM)?"AM":"FM").arg(ret)<<endl;
        return 0;
    }

    etal_autoseek_stop(vl_handle,lastFrequency);
    if(band == BAND_AM){
       if(dir == DIR_UP){
           if ((ret = etal_autoseek_start(vl_handle, cmdDirectionUp, ETAL_AM_FREQ_STEP, cmdAudioUnmuted, seekInSPS, TRUE)) != ETAL_RET_SUCCESS)
           {
               qDebug()<< QString("etal_autoseek_start am up %1 ERROR (%2)").arg(ret)<<endl;
               return 1;
           }
       }else{
           if ((ret = etal_autoseek_start(vl_handle, cmdDirectionDown, ETAL_AM_FREQ_STEP, cmdAudioUnmuted, seekInSPS, TRUE)) != ETAL_RET_SUCCESS)
           {
               qDebug()<< QString("etal_autoseek_start am down %1 ERROR (%2)").arg(ret)<<endl;
               return 1;
           }
       }

    }else{
        if(dir == DIR_UP){
            if ((ret = etal_autoseek_start(vl_handle, cmdDirectionUp, ETAL_FM_FREQ_STEP, cmdAudioUnmuted, seekInSPS, TRUE)) != ETAL_RET_SUCCESS)
            {
                qDebug()<< QString("etal_autoseek_start fm up %1 ERROR (%2)").arg(ret)<<endl;
                return 1;
            }
        }else{
            if ((ret = etal_autoseek_start(vl_handle, cmdDirectionDown, ETAL_FM_FREQ_STEP, cmdAudioUnmuted, seekInSPS, TRUE)) != ETAL_RET_SUCCESS)
            {
                qDebug()<< QString("etal_autoseek_start fm down %1 ERROR (%2)").arg(ret)<<endl;
                return 1;
            }
        }
    }

#endif
    qDebug()<< "RadioService::nativeSeek() ---"<<endl;
    return true;
}
bool RadioService::nativeStopSeek(BAND band){
    qDebug()<< "RadioService::nativeStopSeek() +++"<<QString("Band= %1").arg((band==BAND_AM)?"AM":"FM")<<endl;
#if (COMPILE_IN_SERVICE == 1)
    ETAL_HANDLE vl_handle = ETAL_INVALID_HANDLE;
    ETAL_STATUS ret;
    EtalReceiverAttr attr;

    if(band == BAND_AM){
       ret = etaltml_getFreeReceiverForPath(&vl_handle, ETAL_PATH_NAME_AM, &attr);
    }else{
       ret = etaltml_getFreeReceiverForPath(&vl_handle, ETAL_PATH_NAME_FM_FG, &attr);
    }
    if (ETAL_RET_SUCCESS != ret)
    {
        qDebug()<< QString("etaltml_getFreeReceiverForPath %1 ERROR (%2)").arg((band == BAND_AM)?"AM":"FM").arg(ret)<<endl;
        return 0;
    }

    etal_autoseek_stop(vl_handle,lastFrequency);

#endif
    qDebug()<< "RadioService::nativeStopSeek() ---"<<endl;
    return true;
}

//must call in a thread
bool RadioService::nativeScan(BAND band){
    qDebug()<< "RadioService::nativeScan() +++"<<QString("Band= %1").arg((band==BAND_AM)?"AM":"FM")<<endl;
#if (COMPILE_IN_SERVICE == 1)
    ETAL_HANDLE vl_handle = ETAL_INVALID_HANDLE;
    ETAL_STATUS ret;
    EtalReceiverAttr attr;

    if(band == BAND_AM){
       ret = etaltml_getFreeReceiverForPath(&vl_handle, ETAL_PATH_NAME_AM, &attr);
    }else{
       ret = etaltml_getFreeReceiverForPath(&vl_handle, ETAL_PATH_NAME_FM_FG, &attr);
    }
    if (ETAL_RET_SUCCESS != ret)
    {
        qDebug()<< QString("etaltml_getFreeReceiverForPath %1 ERROR (%2)").arg((band == BAND_AM)?"AM":"FM").arg(ret)<<endl;
        return 0;
    }

    if(band == BAND_AM){
       etaltml_scan_start(vl_handle,0,cmdDirectionUp,ETAL_AM_FREQ_STEP);
    }else{
       etaltml_scan_start(vl_handle,0,cmdDirectionUp,ETAL_FM_FREQ_STEP);
    }

    //-------------Here TODO something

    //--------------------------------

#endif
    qDebug()<< "RadioService::nativeScan() ---"<<endl;
    return true;
}

bool RadioService::nativeStopScan(BAND band){
    qDebug()<< "RadioService::nativeStopScan() +++"<<QString("Band= %1").arg((band==BAND_AM)?"AM":"FM")<<endl;
#if (COMPILE_IN_SERVICE == 1)
    ETAL_HANDLE vl_handle = ETAL_INVALID_HANDLE;
    ETAL_STATUS ret;
    EtalReceiverAttr attr;

    if(band == BAND_AM){
       ret = etaltml_getFreeReceiverForPath(&vl_handle, ETAL_PATH_NAME_AM, &attr);
    }else{
       ret = etaltml_getFreeReceiverForPath(&vl_handle, ETAL_PATH_NAME_FM_FG, &attr);
    }
    if (ETAL_RET_SUCCESS != ret)
    {
        qDebug()<< QString("etaltml_getFreeReceiverForPath %1 ERROR (%2)").arg((band == BAND_AM)?"AM":"FM").arg(ret)<<endl;
        return 0;
    }

    etaltml_scan_stop(vl_handle,lastFrequency);
#endif
    qDebug()<< "RadioService::nativeStopScan() ---"<<endl;
    return true;
}


tU32  RadioService::nativeGetFrequency(BAND band){//Khz
    qDebug()<< "RadioService::nativeGetFrequency() +++"<<QString("Band= %1").arg((band==BAND_AM)?"AM":"FM")<<endl;
#if (COMPILE_IN_SERVICE == 1)
    ETAL_HANDLE vl_handle = ETAL_INVALID_HANDLE;
    ETAL_STATUS ret;
    EtalReceiverAttr attr;
    tU32 curFreq;
    if(band == BAND_AM){
       ret = etaltml_getFreeReceiverForPath(&vl_handle, ETAL_PATH_NAME_AM, &attr);
    }else{
       ret = etaltml_getFreeReceiverForPath(&vl_handle, ETAL_PATH_NAME_FM_FG, &attr);
    }
    if (ETAL_RET_SUCCESS != ret)
    {
        qDebug()<< QString("etaltml_getFreeReceiverForPath %1 ERROR (%2)").arg((band == BAND_AM)?"AM":"FM").arg(ret)<<endl;
        return 0;
    }

    etal_get_receiver_frequency(vl_handle, &curFreq);
    return curFreq;
#endif
    qDebug()<< "RadioService::nativeGetFrequency() ---"<<endl;
}

bool RadioService::nativeSelectRadioAudio(){
    qDebug()<< "RadioService::nativeSelectRadioAudio() +++"<<endl;
#if (COMPILE_IN_SERVICE == 1)
    ETAL_HANDLE vl_handlefm = ETAL_INVALID_HANDLE;
    ETAL_STATUS ret;
    EtalReceiverAttr attr;

    ret = etaltml_getFreeReceiverForPath(&vl_handlefm, ETAL_PATH_NAME_FM_FG, &attr);
    if (ETAL_RET_SUCCESS != ret)
    {
        qDebug()<< QString("etaltml_getFreeReceiverForPath FM ERROR (%1)").arg(ret)<<endl;
        return false;
    }
    ret = etal_audio_select(vl_handlefm, ETAL_AUDIO_SOURCE_STAR_AMFM);
    if (ETAL_RET_SUCCESS != ret)
    {
        qDebug()<< "etal_audio_select FM error"<<endl;
        return false;
    }

#endif
    qDebug()<< "RadioService::nativeSelectRadioAudio() ---"<<endl;
    return true;
}

void RadioService::nativeCallBackByEtal(void *context, ETAL_EVENTS dwEvent, void *pstatus){
    qDebug()<< "RadioService::nativeCallBackByEtal() +++"<<QString("dwEvent= %1").arg(dwEvent)<<endl;
#if (COMPILE_IN_SERVICE == 1)

    if (dwEvent == ETAL_INFO_TUNE)
    {

        EtalTuneStatus *status = (EtalTuneStatus *)pstatus;
        qDebug()<< QString("Tune info event, Frequency %1, good station found %2").arg(status->m_stopFrequency)
                   .arg((status->m_sync & ETAL_TUNESTATUS_SYNCMASK_FOUND) == ETAL_TUNESTATUS_SYNCMASK_FOUND)<<endl;

        if (((status->m_sync & ETAL_TUNESTATUS_SYNCMASK_FOUND) == ETAL_TUNESTATUS_SYNCMASK_FOUND)
            )
            {


            }

    }
    else if (dwEvent == ETAL_INFO_SEEK)
    {
        EtalSeekStatus *status = (EtalSeekStatus *)pstatus;

        if (((true == status->m_frequencyFound)
            ||(status->m_frequency == RadioService::mStartFreq)
            ||(true == status->m_fullCycleReached))
            ||(ETAL_SEEK_FINISHED == status->m_status)
            )
        {
            // found or end of  the seek
            qDebug()<< QString("AutoSeek info event, Frequency %1, good station found %2, status = %3")
                       .arg(status->m_frequency)
                       .arg(status->m_frequencyFound)
                       .arg(status->m_status)<<endl;

            gRadioService->StopSeek(RadioService::mCurBand);
            tU32 curValidFreq = status->m_frequency;
            if(RadioService::mCurBand == BAND_AM){
                if(curValidFreq>=AM_MIN && curValidFreq <= AM_MAX){
                   gRadioService->notifySeekFoundOrFinish(RadioService::mCurBand,curValidFreq);
                }
            }else if(RadioService::mCurBand == BAND_FM){
                if(curValidFreq>=FM_MIN && curValidFreq <= FM_MAX){
                   gRadioService->notifySeekFoundOrFinish(RadioService::mCurBand,curValidFreq);
                }
            }

            //etalDemo_PostEvent(ETALDEMO_EVENT_TUNED_RECEIVED);
        }

    }
    else if (dwEvent == ETAL_INFO_SCAN)
    {
        EtalScanStatusTy *status = (EtalScanStatusTy *)pstatus;

        if (true == status->m_frequencyFound)
        {
            // found during scan
            qDebug()<< QString("Scan info event, good station found at Frequency %1")
                       .arg(status->m_frequency)<<endl;

            //etalDemo_PostEvent(ETALDEMO_EVENT_SCAN_FOUND);
            tU32 curValidFreq = status->m_frequency;
            if(RadioService::mCurBand == BAND_AM){
                if(curValidFreq>=AM_MIN && curValidFreq <= AM_MAX){
                   gRadioService->notifyScanFoundOne(RadioService::mCurBand,curValidFreq);
                }
            }else if(RadioService::mCurBand == BAND_FM){
                if(curValidFreq>=FM_MIN && curValidFreq <= FM_MAX){
                   gRadioService->notifyScanFoundOne(RadioService::mCurBand,curValidFreq);
                }
            }

        }
        if (ETAL_SCAN_FINISHED == status->m_status)
        {
            //etalDemo_PostEvent(ETALDEMO_EVENT_SCAN_FINISHED);
            gRadioService->notifyScanFoundFinish(RadioService::mCurBand);
        }
    }
    else
    {
        qDebug()<< QString("Unexpected event %1").arg(dwEvent)<<endl;
    }
#endif
    qDebug()<< "RadioService::nativeCallBackByEtal() ---"<<endl;
}

bool RadioService::nativeEtalInit(){
    qDebug()<< "RadioService::nativeEtalInit() +++"<<endl;
#if (COMPILE_IN_SERVICE == 1)
    int ret;
    EtalHardwareAttr init_params;

    memset(&init_params, 0x0, sizeof(EtalHardwareAttr));
    init_params.m_cbNotify = nativeCallBackByEtal;

    if ((ret = etal_initialize(&init_params)) != ETAL_RET_SUCCESS)
    {
        qDebug()<< "ERROR: etal_initialize ret="<< ret<<endl;
        return false;
    }
#endif
   qDebug()<< "RadioService::nativeEtalInit() ---"<<endl;
   return true;
}

bool RadioService::nativeEtalDeInit(){
    qDebug()<< "RadioService::nativeEtalDeInit() +++"<<endl;
#if (COMPILE_IN_SERVICE == 1)
    int ret;
    if ((ret = etal_deinitialize()) != ETAL_RET_SUCCESS)
    {
        qDebug()<< "ERROR: etal_deinitialize ret="<< ret<<endl;
        return false;
    }
#endif
   qDebug()<< "RadioService::nativeEtalDeInit() ---"<<endl;
   return true;
}

RadioService * RadioService::mSelf = NULL;
BAND RadioService::mCurBand = BAND_UNKNOW;
unsigned int RadioService::mStartFreq = 0;

RadioService * RadioService::instance(){
    if(mSelf == NULL){
        mSelf = new RadioService();
    }
    return mSelf;
}


bool RadioService::SetBand(BAND band){
  mCurBand = band;
  return nativeSetBand(band);
}

bool RadioService::SetFrequency(BAND band,tU32 freq){//Khz
  Q_D(RadioService);
    if(getScanningState()){
       StopScan(band);
    }
    if(getSeekingState()){
       StopSeek(band);
    }
  RadioService::mStartFreq = freq;
  return nativeSetFrequency(band,freq);
}

bool RadioService::Seek(BAND band,DIRECT dir){
  if(getScanningState()){
     StopScan(band);
     qDebug()<<"RadioService::Scan Last time scaning Just stop scan this time -------"<<endl;
     return true;
  }
  if(getSeekingState()){
     StopSeek(band);
     qDebug()<<"RadioService::Scan Last time seeking Just stop seek this time -------"<<endl;
     return true;
  }
  setSeekingState(true);
  return nativeSeek(band,dir);
}

bool RadioService::StopSeek(BAND band){
  setSeekingState(false);
  return nativeStopSeek(band);
}

bool RadioService::Scan(BAND band){
  //need create a thread to do
  //return nativeScan(band);
  qDebug()<<"RadioService::Scan"<<QString("Band= %1").arg((band==BAND_AM)?"AM":"FM")<<endl;
  Q_D(RadioService);
  if(getScanningState()){
     StopScan(band);
     qDebug()<<"RadioService::Scan Last time scaning Just stop scan this time -------"<<endl;
     return true;
  }
  if(getSeekingState()){
     StopSeek(band);
     qDebug()<<"RadioService::Scan Last time seeking Just stop seek this time -------"<<endl;
     return true;
  }
  if(d->mScanStoreFreqs == NULL){
    d->mScanStoreFreqs = new QList<int>();
  }
  d->mScanStoreFreqs->clear();
  d->mScanthread = new ScanThread();
  d->mScanthread->start();
  qDebug()<<"RadioService::Scan -------"<<endl;
  return true;
}

bool RadioService::StopScan(BAND band){
    Q_D(RadioService);
    if(d->mScanthread != NULL){
       d->mScanthread->safeExit();
       qDebug()<<"RadioService::Scan last thread not exit here wait until it exit !!"<<endl;
       d->mScanthread->wait(500);
       d->mScanthread = NULL;
    }
    setScanningState(false);
    return true;
}

tU32 RadioService::GetFrequency(BAND band){ //Khz
  return nativeGetFrequency(band);
}

bool RadioService::SelectRadioAudio(){
  return nativeSelectRadioAudio();
}

bool RadioService::RadioInit(){
  return nativeEtalInit();
}

bool RadioService::setScanningState(bool on){
   Q_D(RadioService);
   d->mIsScanning = on;
}

bool RadioService::setSeekingState(bool on){
   Q_D(RadioService);
   d->mIsSeeking = on;
}

bool RadioService::getScanningState(){
   Q_D(RadioService);
   return d->mIsScanning;
}

bool RadioService::getSeekingState(){
   Q_D(RadioService);
   return d->mIsSeeking;
}

bool RadioService::notifySeekFoundOrFinish(BAND band,int freq){
   qDebug()<<"RadioService::notifySeekFoundOrFinish +++++++"<<QString("Band= %1,Freq=%2").arg((band==BAND_AM)?"AM":"FM").arg(freq)<<endl;
   emit updateCurFrequency(band,freq);
   qDebug()<<"RadioService::notifySeekFoundOrFinish -------"<<endl;
}

bool RadioService::notifyScanFoundOne(BAND band,int freq){
    qDebug()<<"RadioService::notifyScanFoundOne +++++++"<<QString("Band= %1,Freq=%2").arg((band==BAND_AM)?"AM":"FM").arg(freq)<<endl;
    Q_D(RadioService);
    if(d->mScanStoreFreqs == NULL){
      d->mScanStoreFreqs = new QList<int>();
    }
    d->mScanStoreFreqs->append(freq);
    qDebug()<<"RadioService::notifyScanFoundOne -------"<<endl;
}

bool RadioService::notifyScanFoundFinish(BAND band){
   qDebug()<<"RadioService::notifyScanFoundFinish +++++++"<<QString("Band= %1").arg(band)<<endl;
   Q_D(RadioService);
   StopScan(band);
   if(d->mScanStoreFreqs != NULL && d->mScanStoreFreqs->size()>0){

     QList<int> scanList = * d->mScanStoreFreqs;
     emit updateFrequencyList(band,scanList);
     //play the first chanel
     SetFrequency(band,scanList.at(0));
     //update the cur frequency
     emit updateCurFrequency(band,scanList.at(0));
   }
   qDebug()<<"RadioService::notifyScanFoundFinish -------"<<endl;
}


//-------------------Scan数据线程
class ScanThreadPrivate
{
    Q_DISABLE_COPY(ScanThreadPrivate)
public:
    explicit ScanThreadPrivate(ScanThread *parent);
private:
    Q_DECLARE_PUBLIC(ScanThread)

    //-------
    bool mExit;
    int mTimeOutCount;
    ScanThread * const q_ptr;

};

ScanThreadPrivate::ScanThreadPrivate(ScanThread *parent)
    :q_ptr(parent)
{
   mExit = false;
   mTimeOutCount = 0;
}

//----------------------
ScanThread::ScanThread(QObject *parent) :
    QThread(parent),
    d_ptr(new ScanThreadPrivate(this))
{

}

void ScanThread::run()
{
    qDebug()<<"ScanThread::run"<<endl;
    Q_D(ScanThread);
    //setPriority(QThread::HighestPriority);
    d->mExit = false;
    d->mTimeOutCount = 60*1000/50;
    //start scan here!!
    if(RadioService::mCurBand == BAND_AM){
       RadioService::mStartFreq = AM_MIN;
    }else{
       RadioService::mStartFreq = FM_MIN;
    }

    RadioService::nativeScan(RadioService::mCurBand);
    gRadioService->setScanningState(true);
    while (true) {
        if(d->mExit) break;
        //----------Do something here
        if(d->mTimeOutCount<=0) break;

        //----------
        msleep(50);
        d->mTimeOutCount--;
    }
    //stop scan here!!
    RadioService::nativeStopScan(RadioService::mCurBand);
    gRadioService->setScanningState(false);
    qDebug()<<"ScanThread::run->exit"<<endl;
}

void ScanThread::safeExit()
{
    qDebug()<<"ScanThread::safeExit"<<endl;
    Q_D(ScanThread);
    d->mExit = true;
}

//----------------------


