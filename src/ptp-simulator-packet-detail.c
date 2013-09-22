#include "ptp-simulator-packet-detail.h"

/* GObject definitions */
G_DEFINE_TYPE(PtpSimulatorPacketDetail, ptp_simulator_packet_detail, GTK_TYPE_GRID);
static void ptp_simulator_packet_detail_finalize(GObject* obj);


/****************************************************************************
 * GObject definitions
 ***************************************************************************/

static void
ptp_simulator_packet_detail_class_init(PtpSimulatorPacketDetailClass *klass) {
    G_OBJECT_CLASS(klass)->finalize = ptp_simulator_packet_detail_finalize;
}

static void
ptp_simulator_packet_detail_init(PtpSimulatorPacketDetail *self) {
    
}

static void
ptp_simulator_packet_detail_finalize(GObject* obj) {
    //PtpSimulatorToolbar *self;
    //self = G_TYPE_CHECK_INSTANCE_CAST(obj, PTP_SIMULATOR_TYPE_UI_MANAGER, PtpSimulatorToolbar);
    
    /* unreference */
    //g_object_unref0(...);
    
    G_OBJECT_CLASS(ptp_simulator_packet_detail_parent_class)->finalize(obj);
}

/****************************************************************************
 * 
 ***************************************************************************/
GtkWidget *
ptp_simulator_packet_detail_new(void)
{
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *frame;
    GtkWidget *subgrid;
    
    GdkColor color; 
    
    
    grid = g_object_new(PTP_SIMULATOR_TYPE_PACKET_DETAIL, NULL);
    gtk_container_set_border_width(GTK_CONTAINER(grid), 20);
    //g_object_set(grid, "margin", 12, NULL);
    //gtk_grid_set_row_spacing(GTK_GRID(grid), 6);
    
    
    /*
    gtk_widget_set_halign(label, GTK_ALIGN_START);
    gtk_widget_set_valign(label, GTK_ALIGN_START);
    g_object_set(label, "margin-left", 24, NULL);
    g_object_set(label, "margin-right", 12, NULL);
    //g_object_set(label, "expand", TRUE, NULL);
    
    gdk_color_parse("red", &color); //setting a color - you can also use RGB
    gtk_widget_modify_bg(label, GTK_STATE_NORMAL, &color); //modifying the background color of the widget
    //gtk_widget_modify_fg(label, GTK_STATE_NORMAL, &color); //modifying the background color of the widget
    
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
    */
    
    
    /*
    gtk_widget_set_halign(label, GTK_ALIGN_START);
    gtk_widget_set_valign(label, GTK_ALIGN_START);
    g_object_set(label, "margin-left", 24, NULL);
    g_object_set(label, "margin-right", 12, NULL);
    //g_object_set(label, "expand", TRUE, NULL);
    
    gdk_color_parse("blue", &color); //setting a color - you can also use RGB
    gtk_widget_modify_bg(label, GTK_STATE_NORMAL, &color); //modifying the background color of the widget
    
    gtk_grid_attach(GTK_GRID(grid), label, 0, 1, 1, 1);
    */
    
    
    
    frame = gtk_frame_new("Layer 2");
    g_object_set(frame, "expand", TRUE, NULL);
    subgrid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(frame), subgrid);
    
    label = gtk_label_new("Detail 1");
    gtk_grid_attach(GTK_GRID(subgrid), label, 0, 0, 1, 1);
    
    label = gtk_label_new("Detail 2");
    gtk_grid_attach(GTK_GRID(subgrid), label, 0, 1, 1, 1);
    
    gtk_grid_attach(GTK_GRID(grid), frame, 0, 0, 1, 1);
    
    
    return grid;
}

