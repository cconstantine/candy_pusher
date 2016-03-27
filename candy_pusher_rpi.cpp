#include "LedMatrix.h"
#include "rpi_driver.h"


int main (int    argc,
      char **argv)
{
  LedMatrix::load_lua(argv[1]);

  RpiDriver driver = RpiDriver();
  driver.go(argc, argv);
}
