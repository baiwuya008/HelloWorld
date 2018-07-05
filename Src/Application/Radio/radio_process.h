#ifndef RADIO_PROCESS_H
#define RADIO_PROCESS_H
#include <QObject>
#include "Src/Framework/Manager/RadioUnit.h"




class RadioPrivate;
class RadioAmPrivate;
class RadioPresetFreqDelegate;
class RadioListFreqDelegate;
class RadioAmPresetFreqDelegate;
class RadioAmListFreqDelegate;

class RadioProcess :public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(RadioProcess)

public:
    RadioProcess(QObject *parent = NULL);
    ~RadioProcess();

    void linkRadio(RadioPrivate *radio);
    void linkRadioAm(RadioAmPrivate *radio_am);
    static RadioProcess *instance();

signals:
    void callReFreshFmCurFreq(const int &curFreq,bool updatePreset=false,bool updateList=false);
    void callReFreshFmPresetFreqs(const QList<int> &presetFreqs);
    void callReFreshFmListFreqs(const QList<int> &listFreqs);
    void callReFreshAmCurFreq(const int &curAmFreq,bool updatePreset=false,bool updateList=false);
    void callReFreshAmPresetFreqs(const QList<int> &presetFreqs);
    void callReFreshAmListFreqs(const QList<int> &listFreqs);
public slots:
    void updateCurFrequency(BAND band,int freq); //Khz
    void updateFrequencyList(BAND band,QList<int> lists); //Khz

private:
    //-------- this func call by the gui change
    bool mIsRadioLink;
    bool mIsRadioAmLink;
    void setFmCurFreq(const int &curFreq,bool updateMain=false,bool updatePreset=false,bool updateList=false);
    void setFmPresetFreqs(const QList<int> &presetFreqs);
    void setFmListFreqs(const QList<int> &listFreqs);
    void setAmCurFreq(const int &curFreq,bool updateMain=false,bool updatePreset=false,bool updateList=false);
    void setAmPresetFreqs(const QList<int> &presetFreqs);
    void setAmListFreqs(const QList<int> &listFreqs);
    void setCurBand(BAND band);

    void requestFmPrevChannel();
    void requestFmSeekPrev();
    void requestFmSeekPrevLong();
    void requestFmSeekNext();
    void requestFmSeekNextLong();
    void requestFmNextChannel();
    void scanFm();

    void requestAmPrevChannel();
    void requestAmSeekPrev();
    void requestAmSeekPrevLong();
    void requestAmSeekNext();
    void requestAmSeekNextLong();
    void requestAmNextChannel();
    void scanAm();


    static RadioProcess *self;
    static int testCount;
    static BAND mCurBand;
    friend class RadioPrivate;
    friend class RadioAmPrivate;
    friend class RadioPresetFreqDelegate;
    friend class RadioListFreqDelegate;
    friend class RadioAmPresetFreqDelegate;
    friend class RadioAmListFreqDelegate;

};

#endif // RADIO_PROCESS_H
