#include "LedMatrix.h"

#include "abstract_driver.h"
//#include "rpi_driver.h"
#include "gtk_driver.h"


int main (int    argc,
      char **argv)
{
  LedMatrix::load_lua(argv[1]);

  AbstractDriver *driver = new GtkDriver();
  driver->go(argc, argv);
}
