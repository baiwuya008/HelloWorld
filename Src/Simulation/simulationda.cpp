#include "simulationda.h"




//-----------------


SimulationDa::SimulationDa(QObject *parent):
    Simulation(parent),
    d_ptr(new SimulationDaPrivate(this))
{

}

void SimulationDa::onCreate(QWidget *parent)
{
    Q_D(SimulationDa);
    d->initializeBasicWidget(parent);
}


SimulationDaPrivate::SimulationDaPrivate(SimulationDa *parent):
    QObject(),q_ptr(parent)
{

}

void SimulationDaPrivate::initializeBasicWidget(QWidget *parent)
{
    Q_Q(SimulationDa);

      mBackground = new BmpWidget(parent); //设置背景图片
      mBackground->setBackgroundBmpPath(QString(":/Res/drawable/simulation/simulation_da.png"));
      mBackground->setFixedSize(QSize(1088, 498));
      mBackground->setVisible(true);

      mBtnPWR= new BmpButton(parent);
      mBtnPWR->setNormalBmpPath(QString(":/Res/drawable/simulation/simulation_da_btn_normal.png"));
      mBtnPWR->setPressBmpPath(QString(":/Res/drawable/simulation/simulation_da_btn_pressed.png"));
      mBtnPWR->setGeometry(10,24,110,76);
      mBtnPWR->setVisible(true);
      q->connect(mBtnPWR,SIGNAL(released()),this,SLOT(onBtnPWR_Release()));

      mBtnFM_AM= new BmpButton(parent);
      mBtnFM_AM->setNormalBmpPath(QString(":/Res/drawable/simulation/simulation_da_btn_normal.png"));
      mBtnFM_AM->setPressBmpPath(QString(":/Res/drawable/simulation/simulation_da_btn_pressed.png"));
      mBtnFM_AM->setGeometry(10,100,110,76);
      mBtnFM_AM->setVisible(true);
      q->connect(mBtnFM_AM,SIGNAL(released()),this,SLOT(onBtnFM_AM_Release()));

      mBtnVOL_UP= new BmpButton(parent);
      mBtnVOL_UP->setNormalBmpPath(QString(":/Res/drawable/simulation/simulation_da_btn_normal.png"));
      mBtnVOL_UP->setPressBmpPath(QString(":/Res/drawable/simulation/simulation_da_btn_pressed.png"));
      mBtnVOL_UP->setGeometry(10,180,110,76);
      mBtnVOL_UP->setVisible(true);
      q->connect(mBtnVOL_UP,SIGNAL(released()),this,SLOT(onBtnVOL_UP_Release()));

      mBtnVOL_DOWN= new BmpButton(parent);
      mBtnVOL_DOWN->setNormalBmpPath(QString(":/Res/drawable/simulation/simulation_da_btn_normal.png"));
      mBtnVOL_DOWN->setPressBmpPath(QString(":/Res/drawable/simulation/simulation_da_btn_pressed.png"));
      mBtnVOL_DOWN->setGeometry(10,260,110,76);
      mBtnVOL_DOWN->setVisible(true);
      q->connect(mBtnVOL_DOWN,SIGNAL(released()),this,SLOT(onBtnVOL_DOWN_Release()));

      mBtnPHONE= new BmpButton(parent);
      mBtnPHONE->setNormalBmpPath(QString(":/Res/drawable/simulation/simulation_da_btn_normal.png"));
      mBtnPHONE->setPressBmpPath(QString(":/Res/drawable/simulation/simulation_da_btn_pressed.png"));
      mBtnPHONE->setGeometry(970,24,110,76);
      mBtnPHONE->setVisible(true);
      q->connect(mBtnPHONE,SIGNAL(released()),this,SLOT(onBtnPHONE_Release()));

      mBtnMEDIA= new BmpButton(parent);
      mBtnMEDIA->setNormalBmpPath(QString(":/Res/drawable/simulation/simulation_da_btn_normal.png"));
      mBtnMEDIA->setPressBmpPath(QString(":/Res/drawable/simulation/simulation_da_btn_pressed.png"));
      mBtnMEDIA->setGeometry(970,103,110,76);
      mBtnMEDIA->setVisible(true);
      q->connect(mBtnMEDIA,SIGNAL(released()),this,SLOT(onBtnMEDIA_Release()));

      mBtnDISP= new BmpButton(parent);
      mBtnDISP->setNormalBmpPath(QString(":/Res/drawable/simulation/simulation_da_btn_normal.png"));
      mBtnDISP->setPressBmpPath(QString(":/Res/drawable/simulation/simulation_da_btn_pressed.png"));
      mBtnDISP->setGeometry(970,180,110,76);
      mBtnDISP->setVisible(true);
      q->connect(mBtnDISP,SIGNAL(released()),this,SLOT(onBtnDISP_Release()));

      mBtnSETUP= new BmpButton(parent);
      mBtnSETUP->setNormalBmpPath(QString(":/Res/drawable/simulation/simulation_da_btn_normal.png"));
      mBtnSETUP->setPressBmpPath(QString(":/Res/drawable/simulation/simulation_da_btn_pressed.png"));
      mBtnSETUP->setGeometry(970,260,110,76);
      mBtnSETUP->setVisible(true);
      q->connect(mBtnSETUP,SIGNAL(released()),this,SLOT(onBtnSETUP_Release()));


}

void SimulationDaPrivate::onBtnPWR_Release()
{

}
void SimulationDaPrivate::onBtnFM_AM_Release()
{
    Q_Q(SimulationDa);
    q->startApplication(T_Radio);
}
void SimulationDaPrivate::onBtnVOL_UP_Release()
{

}
void SimulationDaPrivate::onBtnVOL_DOWN_Release()
{

}
void SimulationDaPrivate::onBtnPHONE_Release()
{
    Q_Q(SimulationDa);
    q->startApplication(T_Bluetooth);
}
void SimulationDaPrivate::onBtnMEDIA_Release()
{
    Q_Q(SimulationDa);
    q->startApplication(T_Home);
}
void SimulationDaPrivate::onBtnDISP_Release()
{

}
void SimulationDaPrivate::onBtnSETUP_Release()
{
    Q_Q(SimulationDa);
    q->startApplication(T_Setting);
}
