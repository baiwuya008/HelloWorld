#ifndef RADIO_PROCESS_H
#define RADIO_PROCESS_H
#include <QObject>

class RadioPrivate;
class RadioAmPrivate;
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
    void callReFreshFmCurFreq(const double &curFreq);
    void callReFreshFmPresetFreqs(const QList<double> &presetFreqs);
    void callReFreshFmListFreqs(const QList<double> &listFreqs);
    void callReFreshAmCurFreq(const int &curAmFreq);
    void callReFreshAmPresetFreqs(const QList<int> &presetFreqs);
    void callReFreshAmListFreqs(const QList<int> &listFreqs);

private:
    //-------- this func call by the gui change
    bool mIsRadioLink;
    bool mIsRadioAmLink;
    void setFmCurFreq(const double &curFreq);
    void setFmPresetFreqs(const QList<double> &presetFreqs);
    void setFmListFreqs(const QList<double> &listFreqs);
    void setAmCurFreq(const int &curFreq);
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

    //-------- this from the radio ic module state sync//need call ReFreshXXX
    void syncFmCurFreq(const double &curFreq);
    void syncFmPresetFreqs(const QList<double> &presetFreqs);
    void syncFmListFreqs(const QList<double> &listFreqs);
    void syncAmCurFreq(const int &curAmFreq);
    void syncAmPresetFreqs(const QList<int> &presetFreqs);
    void syncAmListFreqs(const QList<int> &listFreqs);


    static RadioProcess *self;
    static int testCount;
    friend class RadioPrivate;
    friend class RadioAmPrivate;

};

#endif // RADIO_PROCESS_H
