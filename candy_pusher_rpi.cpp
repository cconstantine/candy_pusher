#include "LedMatrix.h"
#include "rpi_driver.h"


int main (int    argc,
      char **argv)
{
  RpiDriver driver = RpiDriver(argc, argv);
  driver.go();
}
