#include "ptp-simulator-toolbar.h"
#include "ptp-simulator-actions.h"

#define ptp_simulator_toolbar_item_new(toolbar, new_item, stock, tooltip_text, callback, user_data) { \
    new_item = gtk_tool_button_new_from_stock(stock); \
    gtk_widget_set_tooltip_text(GTK_WIDGET(new_item), tooltip_text); \
    g_signal_connect(new_item, "clicked", G_CALLBACK(callback), user_data); \
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), new_item, -1); \
    gtk_widget_show(GTK_WIDGET(new_item)); \
}


#define ptp_simulator_toolbar_separator_new(toolbar) { \
    GtkToolItem *separator = gtk_separator_tool_item_new(); \
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), separator, -1); \
    gtk_widget_show(GTK_WIDGET(separator)); \
}

/* GObject definitions */
G_DEFINE_TYPE(PtpSimulatorToolbar, ptp_simulator_toolbar, GTK_TYPE_TOOLBAR);
static void ptp_simulator_toolbar_finalize(GObject* obj);


/****************************************************************************
 * GObject definitions
 ***************************************************************************/

static void
ptp_simulator_toolbar_class_init(PtpSimulatorToolbarClass *klass) {
    G_OBJECT_CLASS(klass)->finalize = ptp_simulator_toolbar_finalize;
}

static void
ptp_simulator_toolbar_init(PtpSimulatorToolbar *self) {
    
}

static void
ptp_simulator_toolbar_finalize(GObject* obj) {
    //PtpSimulatorToolbar *self;
    //self = G_TYPE_CHECK_INSTANCE_CAST(obj, PTP_SIMULATOR_TYPE_UI_MANAGER, PtpSimulatorToolbar);
    
    /* unreference */
    //g_object_unref0(...);
    
    G_OBJECT_CLASS(ptp_simulator_toolbar_parent_class)->finalize(obj);
}

/****************************************************************************
 * 
 ***************************************************************************/

GtkWidget *
ptp_simulator_toolbar_new(GtkWidget *window)
{
    PtpSimulatorToolbar *toolbar;
    
    toolbar = g_object_new(PTP_SIMULATOR_TYPE_TOOLBAR, NULL);
    gtk_orientable_set_orientation(GTK_ORIENTABLE(toolbar), GTK_ORIENTATION_HORIZONTAL);
    
    ptp_simulator_toolbar_item_new(toolbar, toolbar->item_new,      GTK_STOCK_NEW,          "New",         ptp_simulation_action_new,      window);
    ptp_simulator_toolbar_item_new(toolbar, toolbar->item_open,     GTK_STOCK_OPEN,         "Open",        ptp_simulation_action_open,     window);
    ptp_simulator_toolbar_item_new(toolbar, toolbar->item_save,     GTK_STOCK_SAVE,         "Save",        ptp_simulation_action_save,     window);
    ptp_simulator_toolbar_item_new(toolbar, toolbar->item_save_as,  GTK_STOCK_SAVE_AS,      "Save As...",  ptp_simulation_action_save_as,  window);
    ptp_simulator_toolbar_separator_new(toolbar);
    ptp_simulator_toolbar_item_new(toolbar, toolbar->item_add,      GTK_STOCK_ADD,          "Add",         ptp_simulation_action_add,      window);
    ptp_simulator_toolbar_item_new(toolbar, toolbar->item_remove,   GTK_STOCK_REMOVE,       "Remove",      ptp_simulation_action_remove,   window);
    ptp_simulator_toolbar_separator_new(toolbar);
    ptp_simulator_toolbar_item_new(toolbar, toolbar->item_play,     GTK_STOCK_MEDIA_PLAY,   "Play",        ptp_simulation_action_play,     window);
    ptp_simulator_toolbar_item_new(toolbar, toolbar->item_pause,    GTK_STOCK_MEDIA_PAUSE,  "Pause",       ptp_simulation_action_pause,    window);
    ptp_simulator_toolbar_item_new(toolbar, toolbar->item_stop,     GTK_STOCK_MEDIA_STOP,   "Stop",        ptp_simulation_action_stop,     window);
    
    return GTK_WIDGET(toolbar);
}

