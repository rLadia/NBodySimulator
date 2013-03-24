#include "Model.h"
#include "nbodysimulator.h"

void Model::Update(ObjectList &objects, const double time)
{
  UpdateGravitationalForces(objects, time);
  HandleOverlaps(objects);
}

void Model::UpdateGravitationalForces(ObjectList &objects, const double time)
{
  NBodySimulator simulator;
  simulator.Simulate(objects, time);
}

void Model::HandleOverlaps(ObjectList &objects)
{

}
