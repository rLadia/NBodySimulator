#include <iostream>
#include <fstream>

#include <boost/foreach.hpp>

#include "util.h"
#include "display.h"
#include "test.h"

using std::string;

typedef NBodySimulator::Body Body;
typedef NBodySimulator::BodyList BodyList;

void draw(BodyList& bodies) 
{
  Display display(1000,1000);
  NBodySimulator simulation;

  typedef Display::Point Point;
  std::vector<Display::Point> points;
   
  // runs for 50 seconds
  for(int i = 0; i < 50000; ++i) {
    
    if(i % 250 == 0) { // once a second
      points.clear();
      BOOST_FOREACH(Body b, bodies) {
        int x = static_cast<int>(b.position().x());
        int y = static_cast<int>(b.position().y());
        points.push_back(Point(x, y));
      }
      display.Draw(points);
    } 
    simulation.Simulate(bodies, 0.01);
  }
}

void NBodySimulatorTestSuite::TestDraw() 
{  
  // reads the initial state
  NBodySimulator::BodyList bodies;
  std::ifstream file(NBodySimulatorTestSuite::kFileName);

  // add the bodies to the simulation
  NBodySimulatorUtil::createBodiesFromFile(bodies, file);
  file.close();

  // begins the animation
  draw(bodies);
}


