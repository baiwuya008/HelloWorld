#include "radio_process.h"
#include "radio.h"
#include "radio_am.h"
#include "radio_data.h"

#include <QDebug>


//for ASIA
#define AM_MIN   531
#define AM_MAX   1602
#define AM_STEP  9

#define FM_MIN   87.5
#define FM_MAX   108
#define FM_STEP  0.1



RadioProcess * RadioProcess::self = NULL;
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
}

RadioProcess::~RadioProcess()
{

}

void RadioProcess::linkRadio(RadioPrivate *radio)
{
  connect(this,SIGNAL(callReFreshFmCurFreq(const double &)),radio,SLOT(doReFreshCurFreq(const double &)));
  connect(this,SIGNAL(callReFreshFmPresetFreqs(const QList<double> &)),radio,SLOT(doReFreshPresetFreqs(const QList<double> &)));
  connect(this,SIGNAL(callReFreshFmListFreqs(const QList<double> &)),radio,SLOT(doReFreshListFreqs(const QList<double> &)));
  mIsRadioLink = true;
}
void RadioProcess::linkRadioAm(RadioAmPrivate *radio_am)
{
  connect(this,SIGNAL(callReFreshAmCurFreq(const int &)),radio_am,SLOT(doReFreshCurFreq(const int &)));
  connect(this,SIGNAL(callReFreshAmPresetFreqs(const QList<int> &)),radio_am,SLOT(doReFreshPresetFreqs(const QList<int> &)));
  connect(this,SIGNAL(callReFreshAmListFreqs(const QList<int> &)),radio_am,SLOT(doReFreshListFreqs(const QList<int> &)));
  mIsRadioAmLink = true;
}


//-------- this func call by the gui change
void RadioProcess::setFmCurFreq(const double &curFreq){
  gRadioData->getData().setFmCurFreq(curFreq);
}
void RadioProcess::setFmPresetFreqs(const QList<double> &presetFreqs){
  gRadioData->getData().setFmPresetFreqs(presetFreqs);
}
void RadioProcess::setFmListFreqs(const QList<double> &listFreqs){
  gRadioData->getData().setFmListFreqs(listFreqs);
}
void RadioProcess::setAmCurFreq(const int &curFreq){
  gRadioData->getData().setAmCurFreq(curFreq);
}
void RadioProcess::setAmPresetFreqs(const QList<int> &presetFreqs){
  gRadioData->getData().setAmPresetFreqs(presetFreqs);
}
void RadioProcess::setAmListFreqs(const QList<int> &listFreqs){
  gRadioData->getData().setAmListFreqs(listFreqs);
}


void RadioProcess::requestFmPrevChannel(){
     int chan = gRadioData->getData().getCurFmChannel();
     double reqFreq=0;
     QList<double> myList =gRadioData->getData().getFmListFreqs();
     if(myList.size()<2){ return;}  //do nothing here!!
     if(chan>myList.size()||chan<1){
         //force change to channel 1
         reqFreq = myList.at(0);
         if(reqFreq<FM_MIN){reqFreq = FM_MIN;}
         if(reqFreq>FM_MAX){reqFreq = FM_MAX;}
         gRadioData->getData().setFmCurFreq(reqFreq);
         gRadioData->getData().setFmCurChannel(1);
         if(mIsRadioLink){
             emit callReFreshFmCurFreq(reqFreq);
         }
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
         emit callReFreshFmCurFreq(reqFreq);
     }

}
void RadioProcess::requestFmSeekPrev(){
    double freq = gRadioData->getData().getCurFmFreq();
     freq=freq-FM_STEP;
     if(freq<FM_MIN){freq = FM_MAX;}
     gRadioData->getData().setFmCurFreq(freq);
     if(mIsRadioLink){
         emit callReFreshFmCurFreq(freq);
     }
}
void RadioProcess::requestFmSeekNext(){
    double freq = gRadioData->getData().getCurFmFreq();
     freq=freq+FM_STEP;
     if(freq>FM_MAX){freq = FM_MIN;}
     gRadioData->getData().setFmCurFreq(freq);
     if(mIsRadioLink){
         emit callReFreshFmCurFreq(freq);
     }
}
void RadioProcess::requestFmNextChannel(){
    int chan = gRadioData->getData().getCurFmChannel();
    double reqFreq=0;
    QList<double> myList =gRadioData->getData().getFmListFreqs();
    if(myList.size()<2){ return;}  //do nothing here!!
    if(chan>myList.size()||chan<1){
        //force change to channel 1
        reqFreq = myList.at(0);
        if(reqFreq<FM_MIN){reqFreq = FM_MIN;}
        if(reqFreq>FM_MAX){reqFreq = FM_MAX;}
        gRadioData->getData().setFmCurFreq(reqFreq);
        gRadioData->getData().setFmCurChannel(1);
        if(mIsRadioLink){
            emit callReFreshFmCurFreq(reqFreq);
        }
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
        emit callReFreshFmCurFreq(reqFreq);
    }
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
            emit callReFreshAmCurFreq(reqFreq);
        }
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
        emit callReFreshAmCurFreq(reqFreq);
    }
}
void RadioProcess::requestAmSeekPrev(){
    int freq = gRadioData->getData().getCurAmFreq();
     freq=freq-AM_STEP;
     if(freq<AM_MIN){freq = AM_MAX;}
     gRadioData->getData().setAmCurFreq(freq);
     if(mIsRadioAmLink){
         emit callReFreshAmCurFreq(freq);
     }
}
void RadioProcess::requestAmSeekNext(){
    int freq = gRadioData->getData().getCurAmFreq();
     freq=freq+AM_STEP;
     if(freq>AM_MAX){freq = AM_MIN;}
     gRadioData->getData().setAmCurFreq(freq);
     if(mIsRadioAmLink){
         emit callReFreshAmCurFreq(freq);
     }
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
            emit callReFreshAmCurFreq(reqFreq);
        }
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
        emit callReFreshAmCurFreq(reqFreq);
    }
}


//-------- this from the radio ic module state sync//need call ReFreshXXX
void RadioProcess::syncFmCurFreq(const double &curFreq){

}
void RadioProcess::syncFmPresetFreqs(const QList<double> &presetFreqs){

}
void RadioProcess::syncFmListFreqs(const QList<double> &listFreqs){

}
void RadioProcess::syncAmCurFreq(const int &curAmFreq){

}
void RadioProcess::syncAmPresetFreqs(const QList<int> &presetFreqs){

}
void RadioProcess::syncAmListFreqs(const QList<int> &listFreqs){

}

