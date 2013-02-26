//Rodelle Ladia Jr.
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

using namespace std;
using namespace COLLISION;
using namespace POLYNOMIAL;

//file location
static const char* FILENAME = "sphere.txt";
static const int BOUNDARYSIZE = 1000;

//Fills the fields of sphere with information from the file
//returns false if there was an error opening the file
bool createBodiesFromFile(NBodySimulation &, ifstream &);
bool createBlackHoleFromFile(NBodySimulation &, ifstream &);

typedef NBodySimulation::Record Record;

//Prints out each sphere's index, its time of collision, and whether it was 
//destroyed by colliding with a sphere or by hitting the boundary
//Information is printed in a 3 column format
void printCollisionResults(const vector<Record> &);

//Returns a new string of length n, containing the given string centered and
//surrounded on either side with an equal number of spaces
//If the given string does not fit in the given length, it is truncated to fit
string center(const string &, string::size_type);

//uses string stream to convert a number to a string
string numberToString(int);

int main()
{
  MovingSphere sphere;
  ifstream file(FILENAME);
  
  NBodySimulation simulation(BOUNDARYSIZE);
  if(!createBodiesFromFile(simulation, file)) {
    cerr << "File was not successfully opened.\n";
    return EXIT_FAILURE;
  }
  file.close();

  simulation.runSimulation();
  vector<Record> results = simulation.getSimulationResults();
  printCollisionResults(results);

  return EXIT_SUCCESS;
}

//Prints out each sphere's index, its time of collision, and whether it was 
//destroyed by colliding with a sphere or by hitting the boundary
//Information is printed in a 3 column format
void printCollisionResults(const vector<Record> &results) 
{
  static const unsigned int INDEXWIDTH = 5;
  static const unsigned int TIMEWIDTH = 16;

  cout << "Sphere Ellimination Records" << endl;
  cout << "==========================" << endl << endl;
  cout << "Index    Time (s)    Event type" << endl;
  cout << "-----    --------    ----------" << endl;
  
  string collision_name[] = { "Collision", "Black Hole", "Boundary" };

  vector<Record>::const_iterator i;
  for(i = results.begin(); i != results.end(); ++i) {
    cout << center(numberToString(i->index), INDEXWIDTH).c_str();
    cout << center(numberToString(i->time), TIMEWIDTH).c_str();
    cout << collision_name[i->collision];
    cout << endl;
  }
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

//uses string stream to convert a number to a string
string numberToString(int number) 
{
  ostringstream ss;
  ss << number;
  return ss.str();
}

//Uses the information from the file to create spheres in NBodySimulation
//*TODO* handle errors from incorrect file format
bool createBodiesFromFile(NBodySimulation &simulation, ifstream &file)
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

bool createBlackHoleFromFile(NBodySimulation &simulation, ifstream &file)
{
  int x, y, z, m;
  file >> x >> y >> z >> m;
  if(file.fail()) 
    return false; // file could not be read

  simulation.addBlackHole(Vector3(x, y, z), m);
  return true;
}
