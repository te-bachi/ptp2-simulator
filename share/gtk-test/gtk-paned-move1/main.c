
#include <gtk/gtk.h>

static gboolean window_delete_event_cb(GtkWidget *widget, GdkEvent *event, gpointer data);

int
main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *paned;
    GtkWidget *label1;
    GtkWidget *label2;
    
    gtk_init(&argc, &argv);
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "delete-event", G_CALLBACK(window_delete_event_cb), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    paned = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
    
    gtk_paned_pack1(GTK_PANED(paned), gtk_label_new("Label 1"), /* resize = */ TRUE, /* shrink = */ FALSE);
    gtk_paned_pack2(GTK_PANED(paned), gtk_label_new("Label 2"), /* resize = */ TRUE, /* shrink = */ FALSE);
    
    gtk_container_add(GTK_CONTAINER(window), paned);
    
    gtk_widget_show_all(window);
    
    gtk_main();
    
    return 0;
}

static gboolean
window_delete_event_cb(GtkWidget *widget, GdkEvent *event, gpointer data) {
    
    return FALSE;
}

