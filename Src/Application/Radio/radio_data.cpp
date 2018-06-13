#include "radio_data.h"
#include <QList>
#include <QDebug>

//---------------
class RadioSharedData : public QSharedData
{
public:
    //----data
     double mCurFmFreq;
     int    mCurFmBand;
     int    mCurFmChannel;

     QList<double> mFmPresetFreqs;
     QList<double> mFmListFreqs;
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
    //---init fm data ASIA[87.5-108];

    mFmPresetFreqs.append(87.50);
    mFmPresetFreqs.append(88.50);
    mFmPresetFreqs.append(90.00);
    mFmPresetFreqs.append(92.00);
    mFmPresetFreqs.append(95.50);
    mFmPresetFreqs.append(98.00);
    mFmPresetFreqs.append(102.50);
    mFmPresetFreqs.append(104.50);
    mFmPresetFreqs.append(106.50);
    mFmPresetFreqs.append(107.00);
    mFmPresetFreqs.append(108.00);

    mFmListFreqs.append(87.5);
    mFmListFreqs.append(88.0);
    mFmListFreqs.append(91.00);
    mFmListFreqs.append(92.50);
    mFmListFreqs.append(93.50);
    mFmListFreqs.append(97.80);
    mFmListFreqs.append(101.50);
    mFmListFreqs.append(102.00);
    mFmListFreqs.append(103.50);
    mFmListFreqs.append(105.50);
    mFmListFreqs.append(107.50);
    mFmListFreqs.append(108.00);

    //mCurFmFreq = 97.8;
    mCurFmBand = 1;  //1~3
    mCurFmChannel = 6; //1~5//1~24
    mCurFmFreq = mFmListFreqs.at(mCurFmChannel-1);

    //---init am data ASIA[531-1602];EURPO[522-1620];USA[530-1710]:LATIN AMERICA[520-1620]

    mAmPresetFreqs.append(531);
    mAmPresetFreqs.append(549);
    mAmPresetFreqs.append(612);
    mAmPresetFreqs.append(661);
    mAmPresetFreqs.append(742);
    mAmPresetFreqs.append(823);
    mAmPresetFreqs.append(895);
    mAmPresetFreqs.append(958);
    mAmPresetFreqs.append(990);
    mAmPresetFreqs.append(1057);
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

double RadioData::getCurFmFreq()
{
  return data->mCurFmFreq;
}

int  RadioData::getCurFmBand(){
  return data->mCurFmBand;
}
int  RadioData::getCurFmChannel(){
  return data->mCurFmChannel;
}

QList<double> RadioData::getFmPresetFreqs()
{
  QList<double> newList;
  newList.append(data->mFmPresetFreqs);
  return newList;
}
QList<double> RadioData::getFmListFreqs()
{
  QList<double> newList;
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

void RadioData::setFmCurFreq(const double &curFreq){
    data->mCurFmFreq = curFreq;
}

void RadioData::setFmCurChannel(const int &curChan){
    data->mCurFmChannel = curChan;
}
void RadioData::setFmCurBand(const int &curBand){
    data->mCurFmBand = curBand;
}

void RadioData::setFmPresetFreqs(const QList<double> &presetFreqs){
    data->mFmPresetFreqs.clear();
    data->mFmPresetFreqs.append(presetFreqs);
}
void RadioData::setFmListFreqs(const QList<double> &listFreqs){
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


