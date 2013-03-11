//Rodelle Ladia Jr.BOUNDARYSIZE
//CSSE 342, Winter 2013 
//Lab 4

//gets rid of assertions
//#define NDEBUG

#include <cassert>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/foreach.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/timer/timer.hpp>
#include <boost/thread/thread.hpp>


#include "collision.h"
#include "movingsphere.h"
#include "nbodysimulator.h"
#include "polynomial.h"
#include "tablelogger.h"

#include "display.h"

using std::string;

static const char* kFileName = "sphere.txt"; // file location
static const int kBoundarySize = 1000; // default boundary size

typedef NBodySimulator::BodyPtr BodyPtr;
typedef NBodySimulator::Record Record;

// uses the information from the file to add bodies to the list of bodies
// returns false if there was an error opening the file
bool createBodiesFromFile(std::list<BodyPtr> *, std::ifstream &);

// Prints out each sphere's index, its time of collision, and how it was
// destroyed. Information is printed in a 3 column format
void printCollisionResults(const std::vector<Record> &);

//uses string stream to convert a number to a string
template<typename T>
string numberToString(T);

int main()
{
  Display display(1000,1000);
  using namespace boost::timer;
  const nanosecond_type one_second = 1000000000LL;

  typedef Display::Point Point;
  std::vector<Display::Point> points;
  points.push_back(Display::Point(500, 500));

  for(int i = 0; i < 10; ++i) {
    boost::timer::cpu_timer timer;
    const cpu_times elapsed_times(timer.elapsed());
    nanosecond_type elapsed = elapsed_times.wall + elapsed_times.system;
    if(elapsed < one_second) {
      nanosecond_type time = one_second - elapsed;
      nanosecond_type milliseconds = time / 1000000;

      points[0]+=Point(15, 15);
      boost::this_thread::sleep(boost::posix_time::milliseconds(milliseconds));
    }

    display.Draw(points);
  }
  /*
  std::ifstream file(kFileName);
  
  NBodySimulator simulation(kBoundarySize);

  std::list<BodyPtr> bodies;

  
  // add the bodies to the simulation
  if(!createBodiesFromFile(&bodies, file)) { 
    std::cerr << "File was not successfully opened.\n";
    return EXIT_FAILURE;
  }
  file.close();

  simulation.SetBodyList(bodies);

  std::vector<Record> results;
  do {
    simulation.RunSimulation(0.01);
    results = simulation.getSimulationResults();
  } while(results.empty());
    

  printCollisionResults(results);

  return EXIT_SUCCESS;
  */
}

// Prints out each sphere's index, its time of collision, and how it was
// destroyed. Information is printed in a 3 column format
void printCollisionResults(const std::vector<Record> &results) 
{
  std::string title("Sphere Elimination Records\n==========================");

  std::vector<TableLogger::HeaderStyle> header;
  typedef TableLogger::Justification Just;
  header.push_back(std::make_pair("Index", Just::kCenter));
  header.push_back(std::make_pair("Color", Just::kLeft));
  header.push_back(std::make_pair("Time", Just::kCenter));
  header.push_back(std::make_pair("Event Type", Just::kLeft));
  TableLogger table(title, header);

  table.LogTableHead();
 
  string collision_type[] = { "Collision", "Black Hole", "Boundary" };

  std::vector<string> data;

  //std::vector<Record>::const_iterator i;
  //for(i = results.begin(); i != results.end(); ++i) {
  BOOST_FOREACH(const Record& i, results) {
    data.push_back(boost::lexical_cast<std::string, int>(i.index));
    data.push_back(Color::toString(i.color));
    data.push_back(boost::lexical_cast<std::string, double>(i.time));
    data.push_back(collision_type[i.collision]);
    table.LogTableRow(data);
  }
}

// uses the information from the file to add bodies to the simulation
bool createBodiesFromFile(std::list<BodyPtr> *bodies, std::ifstream &file)
{
  if(!file.is_open())
   return false; //file was not able to be read

  do { //read rest of bodies
    int x, y, z, r, vx, vy, vz;

    file >> x >> y >> z >> r >> vx >> vy >> vz;

    if(file.fail())
       break;

    BodyPtr body(new SimulatedBody(
      Vector3(x, y, z), 
      r, 
      Vector3(vx, vy, vz), 
      Vector3(0,0,0),
      r)
    );
    bodies->push_back(body);
  } while(file.good());
  
  return true;
}

//uses string stream to convert a number to a string
template<typename T>
string numberToString(T number) 
{
  std::ostringstream ss;
  ss << number;
  return ss.str();
}
