#ifndef __ABSTRACT_DRIVER_H__
#define __ABSTRACT_DRIVER_H__

class AbstractDriver {
public:
  inline AbstractDriver(int argc, char** argv) : argc(argc), argv(argv) {};

  virtual void go() = 0;

  virtual int getWidth() = 0;
  virtual int getHeight() = 0;
  
  int argc;
  char** argv;
};

#endif