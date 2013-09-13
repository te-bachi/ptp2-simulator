#include "ptp-simulator-ui-manager.h"


/* GObject definitions */
G_DEFINE_TYPE(PtpSimulatorUIManager, ptp_simulator_ui_manager, GTK_TYPE_UI_MANAGER);
static void ptp_simulator_ui_manager_finalize(GObject* obj);

#include "ptp-simulator-menubar.h"

/****************************************************************************
 * GObject definitions
 ***************************************************************************/

static void
ptp_simulator_ui_manager_class_init(PtpSimulatorUIManagerClass *klass) {
    G_OBJECT_CLASS(klass)->finalize = ptp_simulator_ui_manager_finalize;
}

static void
ptp_simulator_ui_manager_init(PtpSimulatorUIManager *self) {
    
}

static void
ptp_simulator_ui_manager_finalize(GObject* obj) {
    //PtpSimulatorUIManager *self;
    //self = G_TYPE_CHECK_INSTANCE_CAST(obj, PTP_SIMULATOR_TYPE_UI_MANAGER, PtpSimulatorUIManager);
    
    /* unreference */
    //g_object_unref0(...);
    
    G_OBJECT_CLASS(ptp_simulator_ui_manager_parent_class)->finalize(obj);
}

/****************************************************************************
 * 
 ***************************************************************************/

PtpSimulatorUIManager *
ptp_simulator_ui_manager_new(void)
{
    PtpSimulatorUIManager   *ui_manager;
    GtkActionGroup          *menubar_action_group;
    GError                  *error = NULL;
    
    menubar_action_group = gtk_action_group_new("MenuActionGroup");
    
    gtk_action_group_add_actions(menubar_action_group,                  /* the action group */
                                 menubar_action_entries,                /* an array of action descriptions */
                                 G_N_ELEMENTS(menubar_action_entries),  /* the number of entries */
                                 NULL);                                 /* data to pass to the action callbacks */
    
    ui_manager = g_object_new(PTP_SIMULATOR_TYPE_UI_MANAGER, NULL);
    gtk_ui_manager_insert_action_group(GTK_UI_MANAGER(ui_manager), menubar_action_group, 0);
    
    gtk_ui_manager_add_ui_from_string(GTK_UI_MANAGER(ui_manager), menubar_definition, -1, &error);
    if (error != NULL) {
        fprintf(stderr, "Warning: building menubar failed: %s\n", error->message);
        g_error_free(error);
        error = NULL;
    }
    g_object_unref(menubar_action_group);
    
    return ui_manager;
}

GtkWidget *
ptp_simulator_ui_manager_get_menubar(PtpSimulatorUIManager *self)
{
    return gtk_ui_manager_get_widget(GTK_UI_MANAGER(self), "/Menubar");
}

