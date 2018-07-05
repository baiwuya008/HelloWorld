#include "radio_data.h"
#include <QList>
#include <QDebug>

//---------------
class RadioSharedData : public QSharedData
{
public:
    //----data
     int mCurFmFreq;
     int    mCurFmBand;
     int    mCurFmChannel;

     QList<int> mFmPresetFreqs;
     QList<int> mFmListFreqs;
     int    mCurAmFreq;
     int    mCurAmBand;
     int    mCurAmChannel;

     QList<int> mAmPresetFreqs;
     QList<int> mAmListFreqs;
    //-----data
     void initWholeData();
     void readDataFromDataBase();
     void writeData2DataBase();

};

void RadioSharedData::initWholeData()
{
    readDataFromDataBase();
    //for test
    //---init fm data ASIA[87500-108000]; KHz

    mFmPresetFreqs.append(87500);
    mFmPresetFreqs.append(88500);
    mFmPresetFreqs.append(90000);
    mFmPresetFreqs.append(92000);
    mFmPresetFreqs.append(95500);
    mFmPresetFreqs.append(98000);
    mFmPresetFreqs.append(102500);
    mFmPresetFreqs.append(104500);
    mFmPresetFreqs.append(106500);
    mFmPresetFreqs.append(107000);
    mFmPresetFreqs.append(108000);

    mFmListFreqs.append(87500);
    mFmListFreqs.append(88000);
    mFmListFreqs.append(91000);
    mFmListFreqs.append(92500);
    mFmListFreqs.append(93500);
    mFmListFreqs.append(97800);
    mFmListFreqs.append(101500);
    mFmListFreqs.append(102000);
    mFmListFreqs.append(103500);
    mFmListFreqs.append(105500);
    mFmListFreqs.append(107500);
    mFmListFreqs.append(108000);

    //mCurFmFreq = 97.8;
    mCurFmBand = 1;  //1~3
    mCurFmChannel = 6; //1~5//1~24
    mCurFmFreq = mFmListFreqs.at(mCurFmChannel-1);

    //---init am data ASIA[531-1602];EURPO[522-1620];USA[530-1710]:LATIN AMERICA[520-1620]

    mAmPresetFreqs.append(531);
    mAmPresetFreqs.append(549);
    mAmPresetFreqs.append(612);
    mAmPresetFreqs.append(675);
    mAmPresetFreqs.append(711);
    mAmPresetFreqs.append(828);
    mAmPresetFreqs.append(891);
    mAmPresetFreqs.append(1008);
    mAmPresetFreqs.append(1062);
    mAmPresetFreqs.append(1332);
    mAmPresetFreqs.append(1602);

    mAmListFreqs.append(540);
    mAmListFreqs.append(558);
    mAmListFreqs.append(684);
    mAmListFreqs.append(774);
    mAmListFreqs.append(855);
    mAmListFreqs.append(918);
    mAmListFreqs.append(981);
    mAmListFreqs.append(1080);
    mAmListFreqs.append(1179);
    mAmListFreqs.append(1269);
    mAmListFreqs.append(1449);
    mAmListFreqs.append(1557);

    //mCurAmFreq = 1066;
    mCurAmBand = 1;  //1~2
    mCurAmChannel = 8; //1~5//1~18
    mCurAmFreq = mAmListFreqs.at(mCurAmChannel-1);
    //--------

}
void RadioSharedData::readDataFromDataBase()
{

}
void RadioSharedData::writeData2DataBase()
{

}

//----------------
RadioData::RadioData() :data(new RadioSharedData)
{

}

RadioData::RadioData(const RadioData &rhs) :data(rhs.data)
{

}

RadioData &RadioData::operator=(const RadioData &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

RadioData::~RadioData()
{

}

int RadioData::getCurFmFreq()
{
  return data->mCurFmFreq;
}

int  RadioData::getCurFmBand(){
  return data->mCurFmBand;
}
int  RadioData::getCurFmChannel(){
  return data->mCurFmChannel;
}

QList<int> RadioData::getFmPresetFreqs()
{
  QList<int> newList;
  newList.append(data->mFmPresetFreqs);
  return newList;
}
QList<int> RadioData::getFmListFreqs()
{
  QList<int> newList;
  newList.append(data->mFmListFreqs);
  return newList;
}
int RadioData::getCurAmFreq()
{
  return data->mCurAmFreq;
}

int RadioData::getCurAmBand(){
  return data->mCurAmBand;
}
int RadioData::getCurAmChannel(){
  return data->mCurAmChannel;
}

QList<int> RadioData::getAmPresetFreqs()
{
  QList<int> newList;
  newList.append(data->mAmPresetFreqs);
  return newList;
}
QList<int> RadioData::getAmListFreqs()
{
  QList<int> newList;
  newList.append(data->mAmListFreqs);
  return newList;
}

void RadioData::setFmCurFreq(const int &curFreq){
    data->mCurFmFreq = curFreq;
}

void RadioData::setFmCurChannel(const int &curChan){
    data->mCurFmChannel = curChan;
}
void RadioData::setFmCurBand(const int &curBand){
    data->mCurFmBand = curBand;
}

void RadioData::setFmPresetFreqs(const QList<int> &presetFreqs){
    data->mFmPresetFreqs.clear();
    data->mFmPresetFreqs.append(presetFreqs);
}
void RadioData::setFmListFreqs(const QList<int> &listFreqs){
    data->mFmListFreqs.clear();
    data->mFmListFreqs.append(listFreqs);
}
void RadioData::setAmCurFreq(const int &curAmFreq){
    data->mCurAmFreq = curAmFreq;
}

void RadioData::setAmCurChannel(const int &curChan){
    data->mCurAmChannel = curChan;
}
void RadioData::setAmCurBand(const int &curBand){
    data->mCurAmBand = curBand;
}

void RadioData::setAmPresetFreqs(const QList<int> &presetFreqs){
    data->mAmPresetFreqs.clear();
    data->mAmPresetFreqs.append(presetFreqs);
}
void RadioData::setAmListFreqs(const QList<int> &listFreqs){
    data->mAmListFreqs.clear();
    data->mAmListFreqs.append(listFreqs);
}


//------------------
RadioDataManager::RadioDataManager(QObject* parent) :QObject(parent)
{
 qDebug()<<"init RadioData here!! "<<endl;
 mRadioData = new RadioData();
 mRadioData->data->initWholeData();
}
RadioDataManager::~RadioDataManager()
{
 delete mRadioData;
}
RadioData & RadioDataManager::getData()
{
  return * mRadioData;
}

RadioDataManager * RadioDataManager::self = NULL;

RadioDataManager * RadioDataManager::instance() {
    if(self == NULL){self = new RadioDataManager();}
    return self;
}


