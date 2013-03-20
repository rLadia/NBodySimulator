#include <iostream>

#include "../util.h"
#include "../test.h"

const double elapsed = 1.0;

typedef NBodySimulator::Body Body;
typedef NBodySimulator::BodyList BodyList;

// initializes the body data
void initBodies(BodyList &bodies) 
{
  NBodySimulator::Body body1(new SimulatedBody(
    Vector3(10, 0, 0), 
    1, 
    Vector3(0, 0, 0), 
    Vector3(0, 0, 0),
    1)
  );

  NBodySimulator::Body body2(new SimulatedBody(
    Vector3(20, 0, 0), 
    1, 
    Vector3(0, 0, 0), 
    Vector3(0, 0, 0),
    1)
  );

  bodies.push_back(body1);
  bodies.push_back(body2);
}

void NBodySimulatorTestSuite::TestData() 
{
  NBodySimulator simulation;
  NBodySimulator::BodyList bodies;

  initBodies(bodies);

  std::cout << "\n--- Program Start ---\n";
  NBodySimulatorUtil::PrintPosition(bodies, 0);
  
  simulation.Simulate(&bodies, elapsed);

  std::cout << "\n--- Simulation Complete ---\n";
  NBodySimulatorUtil::PrintPosition(bodies, elapsed);
}


