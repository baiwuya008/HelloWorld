#ifndef RADIOMANAGER_H
#define RADIOMANAGER_H

#include <QObject>
#include "RadioUnit.h"

#ifdef gRadioManager
#undef gRadioManager
#endif
#define gRadioManager RadioManager::instance()

class RadioManagerPrivate;
class RadioManager : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(RadioManager)
public:
    explicit RadioManager(QObject *parent = 0);

    static RadioManager* instance();

    bool SetBand(BAND band);
    bool SetFrequency(BAND band,int freq); //Khz
    bool Seek(BAND band,DIRECT dir);
    bool StopSeek(BAND band);
    bool Scan(BAND band);
    bool StopScan(BAND band);
    bool getScanningState();
    bool getSeekingState();

    unsigned int GetFrequency(BAND band); //Khz
    bool SelectRadioAudio();

signals:
    void updateCurFrequency(BAND band,int freq); //Khz
    void updateFrequencyList(BAND band,QList<int> lists); //Khz

public slots:


private:
    Q_DECLARE_PRIVATE(RadioManager)
    RadioManagerPrivate * const d_ptr;
    static RadioManager* mSelf;
    void connectSignal();

};






#endif // RADIOMANAGER_H
