#ifndef __GTK_DRIVER_H__
#define __GTK_DRIVER_H__

#include <gtk/gtk.h>

#include "abstract_driver.h"


class GtkDriver : public AbstractDriver {
public:
  GtkDriver();

  virtual void go(int argc, char** argv);
  void update_image();
  void draw_leds(GtkWidget *widget, cairo_t *cr);

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
