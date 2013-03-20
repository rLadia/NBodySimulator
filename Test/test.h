#ifndef LADIA_NBODYSIMULATOR_TEST_H
#define LADIA_NBODYSIMULATOR_TEST_H

#include "../nbodysimulator.h"

namespace NBodySimulatorTestSuite 
{
  static const char* kFileName = "sphere.txt";
  void TestFile();
  void TestData();

  // Animates an ascii text representation of the model onto the screen. The 
  // animation runs for a preset period of time and works best on square 
  // console screens.
  void TestDraw();
};

#endif
