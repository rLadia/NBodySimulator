//Rodelle Ladia Jr.BOUNDARYSIZE
//CSSE 342, Winter 2013 
//Lab 2

//gets rid of assertions
//#define NDEBUG

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cassert>
#include "NBodySimulation.h"
#include "movingsphere.h"
#include "collision.h"
#include "polynomial.h"

using std::string;

static const char* kFileName = "sphere.txt"; // file location
static const int kBoundarySize = 1000; // default boundary size

// uses the information from the file to add bodies to the simulation
// returns false if there was an error opening the file
bool createBodiesFromFile(NBodySimulation &, std::ifstream &);
bool createBlackHoleFromFile(NBodySimulation &, std::ifstream &);

typedef NBodySimulation::Record Record;

// Prints out each sphere's index, its time of collision, and how it was
// destroyed. Information is printed in a 3 column format
void printCollisionResults(const std::vector<Record> &);
void printTableHeader();

//Returns a new string of length n, containing the given string centered and
//surrounded on either side with an equal number of spaces
//If the given string does not fit in the given length, it is truncated to fit
string center(const string &, string::size_type);

//uses string stream to convert a number to a string
template<typename T>
string numberToString(T);

int main()
{
  MovingSphere sphere;
  std::ifstream file(kFileName);
  
  NBodySimulation simulation(kBoundarySize);

  // add the bodies to the simulation
  if(!createBodiesFromFile(simulation, file)) { 
    std::cerr << "File was not successfully opened.\n";
    return EXIT_FAILURE;
  }
  file.close();

  simulation.runSimulation();
  std::vector<Record> results = simulation.getSimulationResults();
  printCollisionResults(results);

  return EXIT_SUCCESS;
}

// Prints out each sphere's index, its time of collision, and how it was
// destroyed. Information is printed in a 3 column format
void printCollisionResults(const std::vector<Record> &results) 
{
  static const unsigned int INDEXWIDTH = 5;
  static const unsigned int COLORWIDTH = 8;
  static const unsigned int TIMEWIDTH = 8;

  printTableHeader();
  
  string collision_type[] = { "Collision", "Black Hole", "Boundary" };

  using std::cout;
  std::vector<Record>::const_iterator i;
  for(i = results.begin(); i != results.end(); ++i) {
    cout << center(numberToString(i->index), INDEXWIDTH).c_str();
    cout << center(Color::toString(i->color), COLORWIDTH).c_str();
    cout << center(numberToString(i->time), TIMEWIDTH).c_str();
    cout << collision_type[i->collision];
    cout << "\n";
  }
}

// prints the table header
void printTableHeader()
{
  using std::cout;
  cout << "Sphere Ellimination Records" << "\n";
  cout << "==========================" << "\n";
  cout << "Index Color Time (s) Event type" << "\n";
  cout << "----- ----- -------- ----------" << "\n";
}

//Returns a new string of length n, containing the given string centered
//surrounded on either side with an equal number of spaces
//If the given string does not fit in the given length, it is truncated to fit
string center(const string &s, string::size_type length) 
{
  if(s.length() > length) 
    return s.substr(0, length);

  string result(length, ' ');
  int spaces = (length - s.length()) / 2;

  for(unsigned int i = 0; i < s.length(); ++i)
    result[i+spaces] = s[i];
  return result;
}

// uses the information from the file to add bodies to the simulation
bool createBodiesFromFile(NBodySimulation &simulation, std::ifstream &file)
{
  if(!file.is_open())
   return false; //file was not able to be read

  if(!createBlackHoleFromFile(simulation, file))
    return false; // could not read black hole

  do { //read rest of bodies
    string c;
    int x, y, z, r, vx, vy, vz;

    file >> c >> x >> y >> z >> r >> vx >> vy >> vz;

    if(file.fail())
       break;

    Color::Color color = Color::toColor(c);
    simulation.addBody(color, Vector3(x, y, z), r, Vector3(vx, vy, vz));
  } while(file.good());
  
  return true;
}

// adds the black hole to the simulation
bool createBlackHoleFromFile(NBodySimulation &simulation, std::ifstream &file)
{
  int x, y, z, m;
  file >> x >> y >> z >> m;
  if(file.fail()) 
    return false; // file could not be read

  simulation.addBlackHole(Vector3(x, y, z), m);
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