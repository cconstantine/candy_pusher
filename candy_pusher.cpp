#include "LedMatrix.h"
#include "gtk_driver.h"


int main (int    argc,
      char **argv)
{
  LedMatrix::load_lua(argv[1]);

  GtkDriver driver = GtkDriver();
  driver.go(argc, argv);
}
