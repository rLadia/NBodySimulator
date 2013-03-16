
#define TEST

#ifdef TEST
#include "test.h"
#endif

int main() 
{

#ifdef TEST
NBodySimulatorTestSuite::Test();
#endif

  return 0;
}