#ifndef SIMULATION_H
#define SIMULATION_H

#include "context.h"
#include<QWidget>
#include "Src/CommonUserWidget/BmpWidget.h"
#include "Src/CommonUserWidget/BmpButton.h"

class SimulationPrivate;
class Simulation : public Context
{
    Q_OBJECT
    Q_DISABLE_COPY(Simulation)
public:
    explicit Simulation(QObject *parent = 0);
    virtual void onCreate(QWidget *parent)=0;

private:
    Q_DECLARE_PRIVATE(Simulation)
    SimulationPrivate * const d_ptr;

signals:

public slots:
};

class SimulationPrivate :public QObject{
    Q_OBJECT
    Q_DISABLE_COPY(SimulationPrivate)
public:
    explicit SimulationPrivate(Simulation *parent);
    ~SimulationPrivate(){delete q_ptr;}

private:
    //data

    Q_DECLARE_PUBLIC(Simulation)
    Simulation * const q_ptr;

private slots:

};

#endif // SIMULATION_H
