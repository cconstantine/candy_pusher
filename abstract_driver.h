#ifndef __ABSTRACT_DRIVER_H__
#define __ABSTRACT_DRIVER_H__

class AbstractDriver {
public:
  inline AbstractDriver() {};

  virtual void go(int argc, char** argv) = 0;
};

#endif