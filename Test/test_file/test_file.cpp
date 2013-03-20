#include <iostream>
#include <fstream>

#include "../util.h"
#include "../display.h"
#include "../test.h"

using std::string;

typedef NBodySimulator::Body Body;
typedef NBodySimulator::BodyList BodyList;

void NBodySimulatorTestSuite::TestFile() 
{
  NBodySimulator simulation;
  NBodySimulator::BodyList bodies;
  std::ifstream file(NBodySimulatorTestSuite::kFileName);

  // add the bodies to the simulation
  NBodySimulatorUtil::createBodiesFromFile(bodies, file);
  file.close();

  std::cout << "\n--- Program Start ---\n";
  NBodySimulatorUtil::PrintPosition(bodies, 0);
  
  double time = 2;
  simulation.Simulate(&bodies, 1);
  simulation.Simulate(&bodies, 1);

  std::cout << "\n--- Simulation Complete ---\n";
  NBodySimulatorUtil::PrintPosition(bodies, time);
}