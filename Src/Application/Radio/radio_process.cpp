#include "radio_process.h"
#include "radio.h"
#include "radio_am.h"
#include "radio_data.h"
#include "Src/Framework/Manager/RadioManager.h"
#include <QDebug>






RadioProcess * RadioProcess::self = NULL;
BAND RadioProcess::mCurBand = BAND_UNKNOW;

int RadioProcess::testCount = 0;


RadioProcess * RadioProcess::instance(){
    if(self == NULL){self = new RadioProcess();}
    return self;
}


RadioProcess::RadioProcess(QObject *parent):QObject(parent)
{
  mIsRadioLink = false;
  mIsRadioAmLink = false;


  qDebug()<<"RadioProcess count="+QString::number(testCount++)<<endl;
  //connect
  connect(gRadioManager,SIGNAL(updateCurFrequency(BAND,int)),this,SLOT(updateCurFrequency(BAND,int)));
  connect(gRadioManager,SIGNAL(updateFrequencyList(BAND,QList<int>)),this,SLOT(updateFrequencyList(BAND,QList<int>)));

}

RadioProcess::~RadioProcess()
{

}

void RadioProcess::linkRadio(RadioPrivate *radio)
{
  connect(this,SIGNAL(callReFreshFmCurFreq(const int &,bool,bool)),radio,SLOT(doReFreshCurFreq(const int &,bool,bool)));
  connect(this,SIGNAL(callReFreshFmPresetFreqs(const QList<int> &)),radio,SLOT(doReFreshPresetFreqs(const QList<int> &)));
  connect(this,SIGNAL(callReFreshFmListFreqs(const QList<int> &)),radio,SLOT(doReFreshListFreqs(const QList<int> &)));
  mIsRadioLink = true;
}
void RadioProcess::linkRadioAm(RadioAmPrivate *radio_am)
{
  connect(this,SIGNAL(callReFreshAmCurFreq(const int &,bool,bool)),radio_am,SLOT(doReFreshCurFreq(const int &,bool,bool)));
  connect(this,SIGNAL(callReFreshAmPresetFreqs(const QList<int> &)),radio_am,SLOT(doReFreshPresetFreqs(const QList<int> &)));
  connect(this,SIGNAL(callReFreshAmListFreqs(const QList<int> &)),radio_am,SLOT(doReFreshListFreqs(const QList<int> &)));
  mIsRadioAmLink = true;
}


//-------- this func call by the gui change
void RadioProcess::setFmCurFreq(const int &curFreq,bool updateMain,bool updatePreset,bool updateList){
  gRadioData->getData().setFmCurFreq(curFreq);
  if(updateMain){
      emit callReFreshFmCurFreq(curFreq,updatePreset,updateList);
  }
  //-----call set hardware freq
  setCurBand(BAND_FM);
  gRadioManager->SetFrequency(BAND_FM,(int)curFreq);
  //-----
}
void RadioProcess::setFmPresetFreqs(const QList<int> &presetFreqs){
  gRadioData->getData().setFmPresetFreqs(presetFreqs);
  emit callReFreshFmPresetFreqs(presetFreqs);
}
void RadioProcess::setFmListFreqs(const QList<int> &listFreqs){
  gRadioData->getData().setFmListFreqs(listFreqs);
}
void RadioProcess::setAmCurFreq(const int &curFreq,bool updateMain,bool updatePreset,bool updateList){
  gRadioData->getData().setAmCurFreq(curFreq);
  if(updateMain){
      emit callReFreshAmCurFreq(curFreq,updatePreset,updateList);
  }
  //-----call set hardware freq
  setCurBand(BAND_AM);
  gRadioManager->SetFrequency(BAND_AM,curFreq);
  //-----

}
void RadioProcess::setAmPresetFreqs(const QList<int> &presetFreqs){
  gRadioData->getData().setAmPresetFreqs(presetFreqs);
  emit callReFreshAmPresetFreqs(presetFreqs);
}
void RadioProcess::setAmListFreqs(const QList<int> &listFreqs){
  gRadioData->getData().setAmListFreqs(listFreqs);
}


void RadioProcess::requestFmPrevChannel(){
     int chan = gRadioData->getData().getCurFmChannel();
     int reqFreq=0;
     QList<int> myList =gRadioData->getData().getFmListFreqs();
     if(myList.size()<2){ return;}  //do nothing here!!
     if(chan>myList.size()||chan<1){
         //force change to channel 1
         reqFreq = myList.at(0);
         if(reqFreq<FM_MIN){reqFreq = FM_MIN;}
         if(reqFreq>FM_MAX){reqFreq = FM_MAX;}
         gRadioData->getData().setFmCurFreq(reqFreq);
         gRadioData->getData().setFmCurChannel(1);
         if(mIsRadioLink){
             emit callReFreshFmCurFreq(reqFreq,true,true);
         }
         //-----call set hardware freq
         setCurBand(BAND_FM);
         gRadioManager->SetFrequency(BAND_FM,(int)reqFreq);
         //-----

         return;
     }
     chan = chan - 1;
     if(chan < 1){
         //turn to the list end channel
         chan = myList.size();
     }
     reqFreq = myList.at(chan-1);
     if(reqFreq<FM_MIN){reqFreq = FM_MIN;}
     if(reqFreq>FM_MAX){reqFreq = FM_MAX;}
     gRadioData->getData().setFmCurFreq(reqFreq);
     gRadioData->getData().setFmCurChannel(chan);
     if(mIsRadioLink){
         emit callReFreshFmCurFreq(reqFreq,true,true);
     }
     //-----call set hardware freq
     setCurBand(BAND_FM);
     gRadioManager->SetFrequency(BAND_FM,(int)reqFreq);
     //-----

}
void RadioProcess::requestFmSeekPrev(){
    int freq = gRadioData->getData().getCurFmFreq();
     freq=freq-FM_STEP;
     if(freq<FM_MIN){freq = FM_MAX;}
     gRadioData->getData().setFmCurFreq(freq);
     if(mIsRadioLink){
         emit callReFreshFmCurFreq(freq,true,true);
     }
     //-----call set hardware freq
     setCurBand(BAND_FM);
     gRadioManager->SetFrequency(BAND_FM,(int)freq);
     //-----
}

void RadioProcess::requestFmSeekNext(){
    int freq = gRadioData->getData().getCurFmFreq();
     freq=freq+FM_STEP;
     if(freq>FM_MAX){freq = FM_MIN;}
     gRadioData->getData().setFmCurFreq(freq);
     if(mIsRadioLink){
         emit callReFreshFmCurFreq(freq,true,true);
     }
     //-----call set hardware freq
     setCurBand(BAND_FM);
     gRadioManager->SetFrequency(BAND_FM,(int)freq);
     //-----
}

void RadioProcess::requestFmSeekPrevLong(){
    //-----call hardware seek
    setCurBand(BAND_FM);
    gRadioManager->Seek(BAND_FM,DIR_DOWN);
    //-----
}

void RadioProcess::requestFmSeekNextLong(){
    //-----call hardware seek
    setCurBand(BAND_FM);
    gRadioManager->Seek(BAND_FM,DIR_UP);
    //-----
}

void RadioProcess::requestFmNextChannel(){
    int chan = gRadioData->getData().getCurFmChannel();
    int reqFreq=0;
    QList<int> myList =gRadioData->getData().getFmListFreqs();
    if(myList.size()<2){ return;}  //do nothing here!!
    if(chan>myList.size()||chan<1){
        //force change to channel 1
        reqFreq = myList.at(0);
        if(reqFreq<FM_MIN){reqFreq = FM_MIN;}
        if(reqFreq>FM_MAX){reqFreq = FM_MAX;}
        gRadioData->getData().setFmCurFreq(reqFreq);
        gRadioData->getData().setFmCurChannel(1);
        if(mIsRadioLink){
            emit callReFreshFmCurFreq(reqFreq,true,true);
        }
        //-----call set hardware freq
        setCurBand(BAND_FM);
        gRadioManager->SetFrequency(BAND_FM,(int)reqFreq);
        //-----
        return;
    }
    chan = chan + 1;
    if(chan > myList.size()){
        //turn to the list end channel
        chan = 1;
    }
    reqFreq = myList.at(chan-1);
    if(reqFreq<FM_MIN){reqFreq = FM_MIN;}
    if(reqFreq>FM_MAX){reqFreq = FM_MAX;}
    gRadioData->getData().setFmCurFreq(reqFreq);
    gRadioData->getData().setFmCurChannel(chan);
    if(mIsRadioLink){
        emit callReFreshFmCurFreq(reqFreq,true,true);
    }
    //-----call set hardware freq
    setCurBand(BAND_FM);
    gRadioManager->SetFrequency(BAND_FM,(int)reqFreq);
    //-----
}

void RadioProcess::scanFm(){
    //-----call hardware scan
    setCurBand(BAND_FM);
    gRadioManager->Scan(BAND_FM);
    //-----
}

void RadioProcess::requestAmPrevChannel(){
    int chan = gRadioData->getData().getCurAmChannel();
    int reqFreq=0;
    QList<int> myList =gRadioData->getData().getAmListFreqs();
    if(myList.size()<2){ return;}  //do nothing here!!
    if(chan>myList.size()||chan<1){
        //force change to channel 1
        reqFreq = myList.at(0);
        if(reqFreq<AM_MIN){reqFreq = AM_MIN;}
        if(reqFreq>AM_MAX){reqFreq = AM_MAX;}
        gRadioData->getData().setAmCurFreq(reqFreq);
        gRadioData->getData().setAmCurChannel(1);
        if(mIsRadioAmLink){
            emit callReFreshAmCurFreq(reqFreq,true,true);
        }
        //-----call set hardware freq
        setCurBand(BAND_AM);
        gRadioManager->SetFrequency(BAND_AM,(int)reqFreq);
        //-----
        return;
    }
    chan = chan - 1;
    if(chan < 1){
        //turn to the list end channel
        chan = myList.size();
    }
    reqFreq = myList.at(chan-1);
    if(reqFreq<AM_MIN){reqFreq = AM_MIN;}
    if(reqFreq>AM_MAX){reqFreq = AM_MAX;}
    gRadioData->getData().setAmCurFreq(reqFreq);
    gRadioData->getData().setAmCurChannel(chan);
    if(mIsRadioAmLink){
        emit callReFreshAmCurFreq(reqFreq,true,true);
    }
    //-----call set hardware freq
    setCurBand(BAND_AM);
    gRadioManager->SetFrequency(BAND_AM,(int)reqFreq);
    //-----
}
void RadioProcess::requestAmSeekPrev(){
    int freq = gRadioData->getData().getCurAmFreq();
     freq=freq-AM_STEP;
     if(freq<AM_MIN){freq = AM_MAX;}
     gRadioData->getData().setAmCurFreq(freq);
     if(mIsRadioAmLink){
         emit callReFreshAmCurFreq(freq,true,true);
     }
     //-----call set hardware freq
     setCurBand(BAND_AM);
     gRadioManager->SetFrequency(BAND_AM,(int)freq);
     //-----
}


void RadioProcess::requestAmSeekNext(){
    int freq = gRadioData->getData().getCurAmFreq();
     freq=freq+AM_STEP;
     if(freq>AM_MAX){freq = AM_MIN;}
     gRadioData->getData().setAmCurFreq(freq);
     if(mIsRadioAmLink){
         emit callReFreshAmCurFreq(freq,true,true);
     }
     //-----call set hardware freq
     setCurBand(BAND_AM);
     gRadioManager->SetFrequency(BAND_AM,(int)freq);
     //-----
}

void RadioProcess::requestAmSeekPrevLong(){
    //-----call hardware seek
    setCurBand(BAND_AM);
    gRadioManager->Seek(BAND_AM,DIR_DOWN);
    //-----
}

void RadioProcess::requestAmSeekNextLong(){
    //-----call hardware seek
    setCurBand(BAND_AM);
    gRadioManager->Seek(BAND_AM,DIR_UP);
    //-----
}

void RadioProcess::requestAmNextChannel(){
    int chan = gRadioData->getData().getCurAmChannel();
    int reqFreq=0;
    QList<int> myList =gRadioData->getData().getAmListFreqs();
    if(myList.size()<2){ return;}  //do nothing here!!
    if(chan>myList.size()||chan<1){
        //force change to channel 1
        reqFreq = myList.at(0);
        if(reqFreq<AM_MIN){reqFreq = AM_MIN;}
        if(reqFreq>AM_MAX){reqFreq = AM_MAX;}
        gRadioData->getData().setAmCurFreq(reqFreq);
        gRadioData->getData().setAmCurChannel(1);
        if(mIsRadioAmLink){
            emit callReFreshAmCurFreq(reqFreq,true,true);
        }
        //-----call set hardware freq
        setCurBand(BAND_AM);
        gRadioManager->SetFrequency(BAND_AM,(int)reqFreq);
        //-----
        return;
    }
    chan = chan + 1;
    if(chan > myList.size()){
        //turn to the list end channel
        chan = 1;
    }
    reqFreq = myList.at(chan-1);
    if(reqFreq<AM_MIN){reqFreq = AM_MIN;}
    if(reqFreq>AM_MAX){reqFreq = AM_MAX;}
    gRadioData->getData().setAmCurFreq(reqFreq);
    gRadioData->getData().setAmCurChannel(chan);
    if(mIsRadioAmLink){
        emit callReFreshAmCurFreq(reqFreq,true,true);
    }
    //-----call set hardware freq
    setCurBand(BAND_AM);
    gRadioManager->SetFrequency(BAND_AM,(int)reqFreq);
    //-----
}

void RadioProcess::scanAm(){
    //-----call hardware scan
    setCurBand(BAND_AM);
    gRadioManager->Scan(BAND_AM);
    //-----
}


void RadioProcess::setCurBand(BAND band){
    if(mCurBand != band){
        mCurBand = band;
        //-----call set hardware band
        gRadioManager->SetBand(band);
        //-----
    }
}


//---callback update frequency
void RadioProcess::updateCurFrequency(BAND band,int freq){ //Khz
   if(band == BAND_AM){
       gRadioData->getData().setAmCurFreq(freq);
       emit callReFreshAmCurFreq(freq,true,true);
   }else if(band == BAND_FM){
       gRadioData->getData().setFmCurFreq(freq);
       emit callReFreshFmCurFreq(freq,true,true);
   }
}

//---callback update freq lists
void RadioProcess::updateFrequencyList(BAND band,QList<int> lists){ //Khz
   if(band == BAND_AM){
       gRadioData->getData().setAmListFreqs(lists);
       if(mIsRadioAmLink){
           emit callReFreshAmListFreqs(lists);
       }
   }else if(band == BAND_FM){
       gRadioData->getData().setFmListFreqs(lists);
       if(mIsRadioLink){
           emit callReFreshFmListFreqs(lists);
       }
   }
}













