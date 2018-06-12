#ifndef RADIO_PROCESS_H
#define RADIO_PROCESS_H
#include <QObject>

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
    void callReFreshFmCurFreq(const double &curFreq,bool updatePreset=false,bool updateList=false);
    void callReFreshFmPresetFreqs(const QList<double> &presetFreqs);
    void callReFreshFmListFreqs(const QList<double> &listFreqs);
    void callReFreshAmCurFreq(const int &curAmFreq,bool updatePreset=false,bool updateList=false);
    void callReFreshAmPresetFreqs(const QList<int> &presetFreqs);
    void callReFreshAmListFreqs(const QList<int> &listFreqs);

private:
    //-------- this func call by the gui change
    bool mIsRadioLink;
    bool mIsRadioAmLink;
    void setFmCurFreq(const double &curFreq,bool updateMain=false,bool updatePreset=false,bool updateList=false);
    void setFmPresetFreqs(const QList<double> &presetFreqs);
    void setFmListFreqs(const QList<double> &listFreqs);
    void setAmCurFreq(const int &curFreq,bool updateMain=false,bool updatePreset=false,bool updateList=false);
    void setAmPresetFreqs(const QList<int> &presetFreqs);
    void setAmListFreqs(const QList<int> &listFreqs);

    void requestFmPrevChannel();
    void requestFmSeekPrev();
    void requestFmSeekNext();
    void requestFmNextChannel();

    void requestAmPrevChannel();
    void requestAmSeekPrev();
    void requestAmSeekNext();
    void requestAmNextChannel();

    static RadioProcess *self;
    static int testCount;
    friend class RadioPrivate;
    friend class RadioAmPrivate;
    friend class RadioPresetFreqDelegate;
    friend class RadioListFreqDelegate;
    friend class RadioAmPresetFreqDelegate;
    friend class RadioAmListFreqDelegate;

};

#endif // RADIO_PROCESS_H
