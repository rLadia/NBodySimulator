#include "Model.h"

void Model::Update(ObjectList &objects, double time)
{
  UpdateGravitationalForces(objects);
  HandleOverlaps(objects);
}

void Model::UpdateGravitationalForces(ObjectList &objects)
{

}

void Model::HandleOverlaps(ObjectList &objects)
{

}
