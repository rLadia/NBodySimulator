#ifndef LADIA_NBODYSIMULATOR_TEST_H
#define LADIA_NBODYSIMULATOR_TEST_H

#include "../src/nbodysimulator.h"
#include "../src/model.h"

namespace NBodySimulatorTestSuite
{
  // Reads initial conditions from a file and runs the simulation for a preset
  // period of time. The initial and final conditions are logged.
  void TestModel();

  // Runs the simulation for a preset period of time using hard-coded initial
  // conditions. The initial and final conditions are logged.
  void TestData();
}

#endif
