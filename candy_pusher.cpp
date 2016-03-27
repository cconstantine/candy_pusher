#include "LedMatrix.h"
#include "gtk_driver.h"


int main (int    argc,
      char **argv)
{
  GtkDriver driver = GtkDriver(argc, argv);
  driver.go();
}
