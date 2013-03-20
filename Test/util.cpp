#include "util.h"

#include <iomanip>
#include <boost/lexical_cast.hpp>
#include "TableLogger.h"

// uses the information from the file to add bodies to the simulation
bool NBodySimulatorUtil::createBodiesFromFile(BodyList &bodies, std::ifstream &file)
{
  if(!file.is_open())
   return false; //file was not able to be read

  do { //read rest of bodies
    int x, y, z, r, vx, vy, vz;

    file >> x >> y >> z >> r >> vx >> vy >> vz;

    if(file.fail())
       break;
    
    NBodySimulator::Body body(new SimulatedBody(
      Vector3(x, y, z), 
      r, 
      Vector3(vx, vy, vz), 
      Vector3(0,0,0),
      r));
    bodies.push_back(body);
  } while(file.good());
  
  return true;
}

void NBodySimulatorUtil::PrintPosition(BodyList &bodies, double elapsed)
  {
    using boost::lexical_cast;
    using std::string;

    std::vector<TableLogger::HeaderStyle> header;
    header.push_back(std::make_pair("Index", TableLogger::kCenter));
    header.push_back(std::make_pair("X-Position", TableLogger::kCenter));
    header.push_back(std::make_pair("Y-Position", TableLogger::kCenter));

    std::string title = "Position at " + lexical_cast<string, double>(elapsed) + " seconds"; 

    TableLogger table(title, header);

    table.LogTableHead();

    int index = 0;
    for(BodyList::iterator i = bodies.begin(); i != bodies.end(); ++i) {
  
      std::vector<std::string> row; 
      row.push_back(lexical_cast<string, int>(index));
      row.push_back(lexical_cast<string, double>((*i)->getCenter().x()));
      row.push_back(lexical_cast<string, double>((*i)->getCenter().y()));
      index ++;
      table.LogTableRow(row);
    }
  }