#include <assert.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include "LedMatrix.h"
#include "opc_client.h"
#include "bcm_host.h"

extern "C" {
#include "common/backgroundLayer.h"
#include "common/font.h"
#include "common/imageGraphics.h"
#include "common/imageLayer.h"
#include "common/key.h"
}

#ifndef ALIGN_TO_16
#define ALIGN_TO_16(x)  ((x + 15) & ~15)
#endif

#define DEFAULT_DELAY 0
#define DEFAULT_DISPLAY_NUMBER 0

uint32_t displayNumber = DEFAULT_DISPLAY_NUMBER;
VC_IMAGE_TYPE_T imageType = VC_IMAGE_RGBA32;
int8_t dmxBytesPerPixel  = 4;
DISPMANX_DISPLAY_HANDLE_T displayHandle;
DISPMANX_MODEINFO_T modeInfo;
DISPMANX_RESOURCE_HANDLE_T resourceHandle;
void *dmxImagePtr;
int32_t dmxPitch;

IMAGE_LAYER_T ledLayer;


int width;
int height;
int scale = 4;

void send_leds();
bool update_image() {
  //fprintf(stderr, "update_image\n");
  int  result = vc_dispmanx_snapshot(displayHandle,
  			     resourceHandle,
  			     DISPMANX_NO_ROTATE);
  if (result != 0) {
    vc_dispmanx_resource_delete(resourceHandle);
    vc_dispmanx_display_close(displayHandle);
    
    fprintf(stderr,"vc_dispmanx_snapshot() failed\n");
    exit(EXIT_FAILURE);
  }

  VC_RECT_T rect;
  result = vc_dispmanx_rect_set(&rect, 0, 0, width, height);

  if (result != 0)
  {
      vc_dispmanx_resource_delete(resourceHandle);
      vc_dispmanx_display_close(displayHandle);

      fprintf(stderr,
              "vc_dispmanx_resource_read_data() failed\n");
      exit(EXIT_FAILURE);
  }

  result = vc_dispmanx_resource_read_data(resourceHandle,
                                          &rect,
                                          dmxImagePtr,
                                          dmxPitch);


  if (result != 0)
  {
      vc_dispmanx_resource_delete(resourceHandle);
      vc_dispmanx_display_close(displayHandle);

      fprintf(stderr,
              "vc_dispmanx_resource_read_data() failed\n");

      exit(EXIT_FAILURE);
  }
  send_leds();

  IMAGE_T *image = &(ledLayer.image);
  for(std::vector<LedMatrix*>::iterator mx = LedMatrix::matrices.begin(); mx != LedMatrix::matrices.end();++mx) {
    LedMatrix *matrix = *mx;
    std::vector<uint8_t> data(matrix->leds.size() * 3, 0);
    for (std::vector<Point>::iterator it = matrix->leds.begin() ; it != matrix->leds.end(); ++it) {
      Point led = *it;
      unsigned char* pixel = (unsigned char*)dmxImagePtr + led.y * width * dmxBytesPerPixel + led.x * dmxBytesPerPixel;

      RGBA8_T colour = { pixel[0], pixel[1], pixel[2], 255 };

      setPixelRGB(image, led.x/scale, led.y/scale, &colour);
    }
  }

  changeSourceAndUpdateImageLayer(&ledLayer);

  return true;
}

void send_leds() {
  //fprintf(stderr, "send_leds\n");
  for(std::vector<LedMatrix*>::iterator mx = LedMatrix::matrices.begin(); mx != LedMatrix::matrices.end();++mx) {
    LedMatrix *matrix = *mx;
    std::vector<uint8_t> data(matrix->leds.size() * 3, 0);
    for (std::vector<Point>::iterator it = matrix->leds.begin() ; it != matrix->leds.end(); ++it) {
      Point led = *it;
      unsigned char* pixel = (unsigned char*)dmxImagePtr + led.y * width * dmxBytesPerPixel + led.x * dmxBytesPerPixel;

      data.push_back(pixel[0]);
      data.push_back(pixel[1]);
      data.push_back(pixel[2]);
    }
    matrix->opc_client.write(data);
  }
}



main (int    argc,
      char **argv)
{
  bcm_host_init();
  displayHandle = vc_dispmanx_display_open(displayNumber);
  if (displayHandle == 0) {
    fprintf(stderr,
	    "unable to open display %d\n",
	    displayNumber);
    
    exit(EXIT_FAILURE);
  }
  int result = vc_dispmanx_display_get_info(displayHandle, &modeInfo);
  if (result != 0) {
    fprintf(stderr, "unable to get display information\n");
    
    exit(EXIT_FAILURE);
  }
  //printf("modeInfo.width: %d, modeInfo.height: %d\n", modeInfo.width, modeInfo.height);
  
  width = modeInfo.width;
  height = modeInfo.height;
  
  dmxPitch = dmxBytesPerPixel * ALIGN_TO_16(width);
  
  dmxImagePtr = malloc(dmxPitch * height);
  if (dmxImagePtr == NULL) {
    exit(EXIT_FAILURE);
  }
  
  //-------------------------------------------------------------------
  uint32_t vcImagePtr = 0;
  
  resourceHandle = vc_dispmanx_resource_create(imageType,
					       width,
					       height,
					       &vcImagePtr);
  
  initImageLayer(&ledLayer,
		 width / scale,
		 height /scale,
		 VC_IMAGE_RGBA32);
  RGBA8_T colour = { 0, 0, 0, 255 };
  clearImageRGB(
    &(ledLayer.image),
    &colour);
  createResourceImageLayer(&ledLayer, 1);

  DISPMANX_UPDATE_HANDLE_T update = vc_dispmanx_update_start(0);
  assert(update != 0);
  
  addElementImageLayerOffset(&ledLayer,
			     0,
			     0,
			     displayHandle,
			     update);

  result = vc_dispmanx_update_submit_sync(update);
  assert(result == 0);

  LedMatrix::load_lua(argv[1]);

  while(true) {
    std::chrono::steady_clock::time_point nextFrame =
      std::chrono::steady_clock::now() + std::chrono::milliseconds(1000/30);
    
    update_image();

    std::this_thread::sleep_until(nextFrame);
  }
  return 0;

}
