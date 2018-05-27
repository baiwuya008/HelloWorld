#include "simulation.h"

SimulationPrivate::SimulationPrivate(Simulation *parent):
    QObject(),q_ptr(parent)
{

}


Simulation::Simulation(QObject *parent) : Context(parent)
  ,d_ptr(new SimulationPrivate(this))
{

}
