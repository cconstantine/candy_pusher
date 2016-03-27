#ifndef __RPI_DRIVER_H__
#define __RPI_DRIVER_H__

#include "opc_client.h"
#include "bcm_host.h"
#include "abstract_driver.h"

extern "C" {
#include "common/backgroundLayer.h"
#include "common/imageLayer.h"
}

class RpiDriver : public AbstractDriver {
public:
  RpiDriver();

  virtual void go(int argc, char** argv);

private:
  void update_image();
  
  uint32_t displayNumber;
  VC_IMAGE_TYPE_T imageType;
  int8_t dmxBytesPerPixel;
  DISPMANX_DISPLAY_HANDLE_T displayHandle;
  DISPMANX_MODEINFO_T modeInfo;
  DISPMANX_RESOURCE_HANDLE_T resourceHandle;
  void *dmxImagePtr;
  int32_t dmxPitch;

  IMAGE_LAYER_T ledLayer;


  int width;
  int height;
  int scale;
};

#endif
