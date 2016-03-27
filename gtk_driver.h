#ifndef __GTK_DRIVER_H__
#define __GTK_DRIVER_H__

#include <gtk/gtk.h>

#include "abstract_driver.h"


class GtkDriver : public AbstractDriver {
public:
  GtkDriver(int argc, char** argv);

  virtual void go();
  void update_image();
  void draw_leds(GtkWidget *widget, cairo_t *cr);

  virtual int getWidth();
  virtual int getHeight();

  GtkWidget *image;

  gint width;
  gint height;
  gint scale = 4;
private:
  void send_leds();
  
  GtkWidget *window;

  GdkPixbuf *gpb = NULL;

};

#endif
