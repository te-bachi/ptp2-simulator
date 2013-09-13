#include <gtk/gtk.h>

#include "ptp-simulator-window.h"

int
main(int argc, char *argv[])
{
    //GtkWidget *toplevel;
    
    gtk_init(&argc, &argv);
    
    /*toplevel = */ptp_simulator_window_new();
    
    gtk_main();
    
    return 0;
}

