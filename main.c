#include <gtk/gtk.h>
#include "PJ_RPI.h"
#include <stdio.h>
#include <stdbool.h>

bool gpio17_State = false;
bool gpio27_State = false;
bool gpio4_State = false;

void click_function_btn1(GtkWidget *wid, gpointer ptr)
{
    
    if(gpio17_State == false)
    {
        char buffer[30];
        GPIO_SET = 1 << 17;
        sprintf(buffer, "gpio: %d is hoog \n",17);
        gtk_label_set_text(GTK_LABEL(ptr), buffer);
        gpio17_State = true;
    }
    else
    {
        char buffer[30];
        GPIO_CLR = 1 << 17;
        sprintf(buffer, "gpio: %d is laag \n",17);
        gtk_label_set_text(GTK_LABEL(ptr), buffer);
        gpio17_State = false;
    }

}

void click_function_btn2(GtkWidget *wid, gpointer ptr)
{
    if(gpio27_State == false)
    {
        char buffer[30];
        GPIO_SET = 1 << 27;
        sprintf(buffer, "gpio: %d is hoog \n",27);
        gtk_label_set_text(GTK_LABEL(ptr), buffer);
        gpio27_State = true;
    }
    else
    {
        char buffer[30];
        GPIO_CLR = 1 << 27;
        sprintf(buffer, "gpio: %d is laag \n",27);
        gtk_label_set_text(GTK_LABEL(ptr), buffer);
        gpio27_State = false;
    }

}

void click_read_function(GtkWidget *wid, gpointer ptr) {
    char buffer[30];
    if(GPIO_READ(4))
    {
        sprintf(buffer, "Gpio4 is hoog\n");
        gtk_label_set_text(GTK_LABEL(ptr), buffer);
    }
    else
    {
        sprintf(buffer, "Gpio4 is hoog\n");
        gtk_label_set_text(GTK_LABEL(ptr), buffer);
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

    INP_GPIO(27);
    OUT_GPIO(27);

    gtk_init (&argc, &argv);
    GtkWidget *win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    GtkWidget *btn = gtk_button_new_with_label("Toggle Led1");
    GtkWidget *btn2 = gtk_button_new_with_label("Toggle Led2");
    GtkWidget *btn3 = gtk_button_new_with_label("Read Gpio");

    gtk_widget_show (win);

    

    GtkWidget *lbl = gtk_label_new("Label led 1");
    GtkWidget *lbl2 = gtk_label_new("Label led 2");
    GtkWidget *lbl3 = gtk_label_new("Label Button toestand");

    g_signal_connect(btn, "clicked", G_CALLBACK(click_function_btn1),lbl);
    g_signal_connect(btn2, "clicked", G_CALLBACK(click_function_btn2),lbl2);
    g_signal_connect(btn3, "clicked", G_CALLBACK(click_read_function),lbl3);
    
    GtkWidget *box = gtk_box_new (FALSE, 5);
    gtk_box_pack_start (GTK_BOX (box), lbl, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (box), lbl2, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (box), lbl3, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (box), btn, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (box), btn2, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (box), btn3, TRUE, TRUE, 0);
    gtk_container_add (GTK_CONTAINER (win), box);

    gtk_widget_show_all(win);
    gtk_main ();


    return 0;
}