#include <gtk/gtk.h>
#include "PJ_RPI.h"
#include <stdio.h>

void click_function(GtkWidget *wid, gpointer ptr)
{
    for (size_t i = 0; i < 10; i++)
    {
        // Gpio toggelen
        GPIO_SET = 1 << 17;
        printf("gpio: %d is hoog \n",17);
        sleep(2);

        GPIO_CLR = 1 << 17;
        printf("gpio: %d is laag \n",17);
        sleep(2);
    }
}

int main (int argc, char *argv[])
{

        if(map_peripheral(&gpio) == -1) 
	{
		printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
		return -1;
	}

    INP_GPIO(17);
    OUT_GPIO(17);

    gtk_init (&argc, &argv);
    GtkWidget *win = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    int ScreenWidth;
	int ScreenHeight;
	GdkScreen *screen = gtk_window_get_screen(GTK_WINDOW(win));
	ScreenWidth = gdk_screen_get_width(screen);			// in pixels
	ScreenHeight = gdk_screen_get_height(screen);

	GtkWidget *fixed;
	fixed = gtk_fixed_new();
	gtk_widget_set_size_request(fixed, ScreenWidth, ScreenHeight);
	gtk_container_add(GTK_CONTAINER(win), fixed);
	gtk_widget_show(fixed);

    gtk_widget_show (win);
    GtkWidget *btn = gtk_button_new_with_label("Toggle Led");
    GtkWidget *statuslbl = GTK_LABEL("Led status");

    g_signal_connect(btn, "clicked", G_CALLBACK(click_function),
        NULL);
    gtk_container_add(GTK_CONTAINER(win), btn);
    gtk_widget_show_all(win);
    gtk_main ();
    return 0;
}