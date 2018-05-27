#ifndef SIMULATIONDA_H
#define SIMULATIONDA_H
#include<QObject>
#include "Src/Framework/Base/Core/simulation.h"

class SimulationDaPrivate;
class SimulationDa : public Simulation
{
    Q_OBJECT
    Q_DISABLE_COPY(SimulationDa)
public:
    SimulationDa(QObject *parent = 0);
    void onCreate(QWidget *parent);

private:
    Q_DECLARE_PRIVATE(SimulationDa)
    SimulationDaPrivate * const d_ptr;

};


class SimulationDaPrivate :public QObject{
    Q_OBJECT
    Q_DISABLE_COPY(SimulationDaPrivate)
public:
    explicit SimulationDaPrivate(SimulationDa *parent);
    ~SimulationDaPrivate(){delete q_ptr;}
    void initializeBasicWidget(QWidget *parent);

private:
    //data
    BmpWidget *mBackground;

    BmpButton *mBtnPWR;
    BmpButton *mBtnFM_AM;
    BmpButton *mBtnVOL_UP;
    BmpButton *mBtnVOL_DOWN;
    BmpButton *mBtnPHONE;
    BmpButton *mBtnMEDIA;
    BmpButton *mBtnDISP;
    BmpButton *mBtnSETUP;


    Q_DECLARE_PUBLIC(SimulationDa)
    SimulationDa * const q_ptr;

private slots:
    void onBtnPWR_Release();
    void onBtnFM_AM_Release();
    void onBtnVOL_UP_Release();
    void onBtnVOL_DOWN_Release();
    void onBtnPHONE_Release();
    void onBtnMEDIA_Release();
    void onBtnDISP_Release();
    void onBtnSETUP_Release();


};



#endif // SIMULATIONDA_H
