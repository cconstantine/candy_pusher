#include <gtk/gtk.h>

#include "gtk_driver.h"
#include "LedMatrix.h"


GtkDriver::GtkDriver() : scale(4), gpb(NULL) { }


void GtkDriver::send_leds() {
  int channels = gdk_pixbuf_get_n_channels(gpb);
  int rowstride = gdk_pixbuf_get_rowstride(gpb);
  guchar* pixels = gdk_pixbuf_get_pixels (gpb);

  for(std::vector<LedMatrix*>::iterator mx = LedMatrix::matrices.begin(); mx != LedMatrix::matrices.end();++mx) {
    LedMatrix *matrix = *mx;
    std::vector<uint8_t> data(matrix->leds.size() * 3, 0);
    for (std::vector<Point>::iterator it = matrix->leds.begin() ; it != matrix->leds.end(); ++it) {
      Point led = *it;
      guchar* pixel = pixels + led.y * rowstride + led.x * channels;
      data.push_back(pixel[0]);
      data.push_back(pixel[1]);
      data.push_back(pixel[2]);
    }
    matrix->opc_client.write(data);
  }
}

void GtkDriver::update_image() {
  if (gpb) {
    g_object_unref (gpb);
  }

  gpb = gdk_pixbuf_get_from_window(gdk_get_default_root_window(),0, 0, width, height);
  
  send_leds();
  gtk_widget_queue_draw(image);

}


void GtkDriver::draw_leds(GtkWidget *widget, cairo_t *cr) {
  if (gpb == NULL) {
    return;
  }

  int channels = gdk_pixbuf_get_n_channels(gpb);
  int rowstride = gdk_pixbuf_get_rowstride(gpb);
  guchar* pixels = gdk_pixbuf_get_pixels (gpb);
  int pixel_width = 4/scale;

  cairo_set_operator(cr, CAIRO_OPERATOR_LIGHTEN);

  for(std::vector<LedMatrix*>::iterator mx = LedMatrix::matrices.begin(); mx != LedMatrix::matrices.end();++mx) {
    LedMatrix *matrix = *mx;
    for (std::vector<Point>::iterator it = matrix->leds.begin() ; it != matrix->leds.end(); ++it) {
      Point led = *it;
      guchar* pixel = pixels + led.y * rowstride + led.x * channels;
      cairo_set_source_rgb (cr, float(pixel[0]) / 255, float(pixel[1]) / 255, float(pixel[2]) / 255);
      cairo_rectangle(cr, led.x/scale-pixel_width/2, led.y/scale-pixel_width/2, pixel_width, pixel_width);
      cairo_fill(cr);
    }
  }
}


gboolean
draw_leds_gtk(GtkWidget *widget, cairo_t *cr, gpointer data)
{
  GtkDriver * driver = (GtkDriver*)data;
  driver->draw_leds(widget, cr);

  return false;
}

gboolean update_image_gtk(gpointer data)
{
  GtkDriver * driver = (GtkDriver*)data;
  driver->update_image();

  return true;
}

void
activate (GtkApplication* app, gpointer user_data) {
  GtkDriver * driver = (GtkDriver*)user_data;

  GtkWidget *window;

  GdkDisplay *display = gdk_display_get_default();
  GdkScreen  *screen  = gdk_display_get_default_screen(display);

  driver->width  = gdk_screen_get_width(screen);
  driver->height = gdk_screen_get_height(screen);

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size(GTK_WINDOW(window), driver->width/driver->scale, driver->height/driver->scale);
  GdkRGBA black = {.0, .0, .0, 1.0};
  gtk_widget_override_background_color(window, GTK_STATE_FLAG_NORMAL, &black);

  driver->image = gtk_drawing_area_new ();
  g_signal_connect (driver->image, "draw", G_CALLBACK (draw_leds_gtk), (gpointer)driver);

  gtk_container_add (GTK_CONTAINER (window), driver->image);
  gtk_widget_show_all (window);

}

void GtkDriver::go(int argc, char** argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), (gpointer)this);
  g_timeout_add (1000/30, update_image_gtk, (gpointer)this);

  status = g_application_run (G_APPLICATION (app), 1, argv);
  g_object_unref (app);
}