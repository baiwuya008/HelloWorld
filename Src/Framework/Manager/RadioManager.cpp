#include "RadioManager.h"
#include "Src/Hardware/RadioService.h"

class RadioManagerPrivate{
public:
    explicit RadioManagerPrivate(RadioManager* parent);
    ~RadioManagerPrivate();

private:
    Q_DECLARE_PUBLIC(RadioManager)
    RadioManager * const q_ptr;

};

RadioManagerPrivate::RadioManagerPrivate(RadioManager* parent)
    :q_ptr(parent)
{

}

//---------------
RadioManager::RadioManager(QObject *parent) :
    QObject(parent),d_ptr(new RadioManagerPrivate(this))
{
  gRadioService->RadioInit();
  connectSignal();
}

RadioManager* RadioManager::mSelf =NULL;

RadioManager* RadioManager::instance(){
    if(mSelf == NULL){
        mSelf = new RadioManager();
    }
    return mSelf;
}



bool RadioManager::SetBand(BAND band){
  return gRadioService->SetBand(band);
}

bool RadioManager::SetFrequency(BAND band,int freq){ //Khz
  return gRadioService->SetFrequency(band,freq);
}
bool RadioManager::Seek(BAND band,DIRECT dir){
  return gRadioService->Seek(band,dir);
}

bool RadioManager::StopSeek(BAND band){
  return gRadioService->StopSeek(band);
}

bool RadioManager::Scan(BAND band){
  return gRadioService->Scan(band);
}

bool RadioManager::StopScan(BAND band){
  return gRadioService->StopScan(band);
}

bool RadioManager::getScanningState(){
  return gRadioService->getScanningState();
}

bool RadioManager::getSeekingState(){
  return gRadioService->getSeekingState();
}

unsigned int RadioManager::GetFrequency(BAND band){ //Khz
  return gRadioService->GetFrequency(band);
}

bool RadioManager::SelectRadioAudio(){
  return gRadioService->SelectRadioAudio();
}


void RadioManager::connectSignal(){
  connect(gRadioService,SIGNAL(updateCurFrequency(BAND,int)),this,SIGNAL(updateCurFrequency(BAND,int)));
  connect(gRadioService,SIGNAL(updateFrequencyList(BAND,QList<int>)),this,SIGNAL(updateFrequencyList(BAND,QList<int>)));
}

