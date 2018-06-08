#ifndef RADIO_DATA_H
#define RADIO_DATA_H
#include <QObject>
#include <QList>
#include <QSharedDataPointer>

#if defined(gRadioData)
#undef gRadioData
#endif
#define gRadioData RadioDataManager::instance()

class RadioProcess;
class RadioSharedData;
class RadioData
{

public:
    RadioData();
    RadioData(const RadioData &);
    RadioData &operator=(const RadioData &);
    ~RadioData();

    //-------
    double getCurFmFreq();
    int    getCurFmBand();
    int    getCurFmChannel();

    QList<double> getFmPresetFreqs();
    QList<double> getFmListFreqs();
    int    getCurAmFreq();
    int    getCurAmBand();
    int    getCurAmChannel();

    QList<int> getAmPresetFreqs();
    QList<int> getAmListFreqs();
    //-------

private:
    QSharedDataPointer<RadioSharedData> data;

    void setFmCurFreq(const double &curFreq);
    void setFmCurChannel(const int &curChan);
    void setFmCurBand(const int &curBand);

    void setFmPresetFreqs(const QList<double> &presetFreqs);
    void setFmListFreqs(const QList<double> &listFreqs);
    void setAmCurFreq(const int &curAmFreq);
    void setAmCurChannel(const int &curChan);
    void setAmCurBand(const int &curBand);

    void setAmPresetFreqs(const QList<int> &presetFreqs);
    void setAmListFreqs(const QList<int> &listFreqs);

    friend class RadioProcess;
    friend class RadioDataManager;

};



class RadioDataManager :public  QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(RadioDataManager)
public:
    RadioDataManager(QObject* parent = NULL);
    ~RadioDataManager();
    RadioData & getData();
    static RadioDataManager *instance();

private:
    RadioData *mRadioData;
    static RadioDataManager *self;
};




#endif // RADIO_DATA_H
