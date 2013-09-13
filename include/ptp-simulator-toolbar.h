#ifndef __PTP_SIMULATOR_TOOLBAR_H__
#define __PTP_SIMULATOR_TOOLBAR_H__

#include <gtk/gtk.h>

typedef struct _PtpSimulatorToolbar                 PtpSimulatorToolbar;
typedef struct _PtpSimulatorToolbarClass            PtpSimulatorToolbarClass;

#define PTP_SIMULATOR_TYPE_TOOLBAR                  (ptp_simulator_toolbar_get_type())
#define PTP_SIMULATOR_TOOLBAR(obj)                  (G_TYPE_CHECK_INSTANCE_CAST((obj), PTP_SIMULATOR_TYPE_TOOLBAR, PtpSimulatorToolbar))
#define PTP_SIMULATOR_IS_TOOLBAR(obj)               (G_TYPE_CHECK_INSTANCE_TYPE((obj), PTP_SIMULATOR_TYPE_TOOLBAR))
#define PTP_SIMULATOR_TOOLBAR_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST((klass),  PTP_SIMULATOR_TYPE_TOOLBAR, PtpSimulatorToolbarClass))
#define PTP_SIMULATOR_IS_TOOLBAR_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE((klass),  PTP_SIMULATOR_TYPE_TOOLBAR))
#define PTP_SIMULATOR_TOOLBAR_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS((obj),  PTP_SIMULATOR_TYPE_TOOLBAR, PtpSimulatorToolbarClass))

struct _PtpSimulatorToolbar {
    GtkToolbar          parent_instance;
    
    GtkToolItem        *item_new;
    GtkToolItem        *item_open;
    GtkToolItem        *item_save;
    GtkToolItem        *item_save_as;
    
    GtkToolItem        *item_add;
    GtkToolItem        *item_remove;
    
    GtkToolItem        *item_play;
    GtkToolItem        *item_pause;
    GtkToolItem        *item_stop;
};

struct _PtpSimulatorToolbarClass {
    GtkToolbarClass     parent_class;
};

GtkWidget *ptp_simulator_toolbar_new(GtkWidget *window);

#endif
