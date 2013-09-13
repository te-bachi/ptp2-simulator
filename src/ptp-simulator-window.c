#include "ptp-simulator-globals.h"
#include "ptp-simulator-window.h"
#include "ptp-simulator-toolbar.h"
#include "ptp-simulator-packet-list.h"
#include "ptp-simulator-packet-detail.h"
#include "ptp-simulator-packet-dump.h"

/* GObject definitions */
G_DEFINE_TYPE(PtpSimulatorWindow, ptp_simulator_window, GTK_TYPE_WINDOW);
static void ptp_simulator_window_finalize(GObject* obj);
    
static gboolean ptp_simulator_window_delete_event_cb(GtkWidget *, GdkEvent *, gpointer);

/****************************************************************************
 * GObject definitions
 ***************************************************************************/

static void
ptp_simulator_window_class_init(PtpSimulatorWindowClass *klass) {
    G_OBJECT_CLASS(klass)->finalize = ptp_simulator_window_finalize;
}

static void
ptp_simulator_window_init(PtpSimulatorWindow *self) {
    
}

static void
ptp_simulator_window_finalize(GObject* obj) {
    PtpSimulatorWindow *self;
    self = G_TYPE_CHECK_INSTANCE_CAST(obj, PTP_SIMULATOR_TYPE_WINDOW, PtpSimulatorWindow);
    
    /* unreference */
    g_object_unref0(self->menubar);
    g_object_unref0(self->ui_manager);
    g_object_unref0(self->vbox);
    
    G_OBJECT_CLASS(ptp_simulator_window_parent_class)->finalize(obj);
}

/****************************************************************************
 * 
 ***************************************************************************/

GtkWidget *
ptp_simulator_window_new(void) {
    PtpSimulatorWindow *window;
    
    window = g_object_new(PTP_SIMULATOR_TYPE_WINDOW, NULL);
    gtk_window_set_title(GTK_WINDOW(window), "PTP-Simulator");
    
    g_signal_connect(window, "delete-event", G_CALLBACK(ptp_simulator_window_delete_event_cb), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    /* vbox */
    window->vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), window->vbox);
    
    /* ui manager */
    window->ui_manager = ptp_simulator_ui_manager_new();
    gtk_window_add_accel_group(GTK_WINDOW(window), gtk_ui_manager_get_accel_group(GTK_UI_MANAGER(window->ui_manager)));
    
    /* menubar */
    window->menubar = ptp_simulator_ui_manager_get_menubar(window->ui_manager);
    gtk_box_pack_start(GTK_BOX(window->vbox), window->menubar, FALSE, FALSE, 0); /* vbox <= menubar */
    
    /* toolbar */
    window->toolbar = ptp_simulator_toolbar_new(GTK_WIDGET(window));
    gtk_box_pack_start(GTK_BOX(window->vbox), window->toolbar, FALSE, FALSE, 0); /* vbox <= toolbar */
    
    /* ___________________
      |                   |
      |    paned_one1     |
      |________...________|
      |                   |
      |    paned_one2     |
      | _________________ |
      ||                 ||
      ||   paned_two1    ||
      ||_______..._______||
      ||                 ||
      ||   paned_two2    ||
      ||_______..._______||
      |___________________| */
    
    /* paned one */
    window->paned_one = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
    gtk_box_pack_start(GTK_BOX(window->vbox), window->paned_one, TRUE, TRUE, 0); /* vbox <= paned one */
    
    /* paned two */
    window->paned_two = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
    gtk_paned_pack2(GTK_PANED(window->paned_one), window->paned_two, TRUE, FALSE); /* paned one2 <= paned two */
    
    /* packet list */
    window->packet_list_win         = gtk_scrolled_window_new(NULL, NULL);
    window->packet_list_viewport    = gtk_viewport_new(gtk_scrolled_window_get_hadjustment(GTK_SCROLLED_WINDOW(window->packet_list_win)),
                                                       gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(window->packet_list_win)));
    window->packet_list             = ptp_simulator_packet_list_new();
    gtk_container_add(GTK_CONTAINER(window->packet_list_viewport), window->packet_list);
    gtk_container_add(GTK_CONTAINER(window->packet_list_win), window->packet_list_viewport);
    gtk_paned_pack1(GTK_PANED(window->paned_one), window->packet_list_win, TRUE, FALSE); /* paned one1 <= packet list */
    
    /* packet detail */
    window->packet_detail_win       = gtk_scrolled_window_new(NULL, NULL);
    window->packet_detail_viewport  = gtk_viewport_new(gtk_scrolled_window_get_hadjustment(GTK_SCROLLED_WINDOW(window->packet_list_win)),
                                                       gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(window->packet_list_win)));
    window->packet_detail           = ptp_simulator_packet_detail_new();
    gtk_container_add(GTK_CONTAINER(window->packet_detail_viewport), window->packet_detail);
    gtk_container_add(GTK_CONTAINER(window->packet_detail_win), window->packet_detail_viewport);
    gtk_paned_pack1(GTK_PANED(window->paned_two), window->packet_detail_win, TRUE, FALSE); /* paned two1 <= packet detail */
    
    /* packet dump */
    window->packet_dump_win         = gtk_scrolled_window_new(NULL, NULL);
    window->packet_dump_viewport    = gtk_viewport_new(gtk_scrolled_window_get_hadjustment(GTK_SCROLLED_WINDOW(window->packet_list_win)),
                                                       gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(window->packet_list_win)));
    window->packet_dump             = ptp_simulator_packet_dump_new();
    gtk_container_add(GTK_CONTAINER(window->packet_dump_viewport), window->packet_dump);
    gtk_container_add(GTK_CONTAINER(window->packet_dump_win), window->packet_dump_viewport);
    gtk_paned_pack2(GTK_PANED(window->paned_two), window->packet_dump_win, TRUE, FALSE); /* paned two2 <= packet dump */
    
    /* statusbar */
    window->statusbar = gtk_statusbar_new();
    gtk_box_pack_start(GTK_BOX(window->vbox), window->statusbar, FALSE, FALSE, 0); /* vbox <= statusbar */
    
    
    gtk_widget_show_all(GTK_WIDGET(window));
    
    return GTK_WIDGET(window);
}

/****************************************************************************
 * Callbacks
 ***************************************************************************/
 
static gboolean
ptp_simulator_window_delete_event_cb(GtkWidget *widget, GdkEvent *event, gpointer data) {
    
    return FALSE;
}

