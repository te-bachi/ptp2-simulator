#ifndef __PTP_SIMULATOR_UI_MANAGER_H__
#define __PTP_SIMULATOR_UI_MANAGER_H__

#include <gtk/gtk.h>

typedef struct _PtpSimulatorUIManager               PtpSimulatorUIManager;
typedef struct _PtpSimulatorUIManagerClass          PtpSimulatorUIManagerClass;

#define PTP_SIMULATOR_TYPE_UI_MANAGER               (ptp_simulator_ui_manager_get_type())
#define PTP_SIMULATOR_UI_MANAGER(obj)               (G_TYPE_CHECK_INSTANCE_CAST((obj), PTP_SIMULATOR_TYPE_WINDOW_UI_MANAGER, PtpSimulatorWindow))
#define PTP_SIMULATOR_IS_UI_MANAGER(obj)            (G_TYPE_CHECK_INSTANCE_TYPE((obj), PTP_SIMULATOR_TYPE_WINDOW_UI_MANAGER))
#define PTP_SIMULATOR_UI_MANAGER_CLASS(klass)       (G_TYPE_CHECK_CLASS_CAST((klass),  PTP_SIMULATOR_TYPE_WINDOW_UI_MANAGER, PtpSimulatorWindowClass))
#define PTP_SIMULATOR_IS_UI_MANAGER_CLASS(klass)    (G_TYPE_CHECK_CLASS_TYPE((klass),  PTP_SIMULATOR_TYPE_WINDOW_UI_MANAGER))
#define PTP_SIMULATOR_UI_MANAGER_GET_CLASS(obj)     (G_TYPE_INSTANCE_GET_CLASS((obj),  PTP_SIMULATOR_TYPE_WINDOW_UI_MANAGER, PtpSimulatorWindowClass))

struct _PtpSimulatorUIManager {
    GtkUIManager        parent_instance;
};

struct _PtpSimulatorUIManagerClass {
    GtkUIManagerClass   parent_class;
};

PtpSimulatorUIManager *ptp_simulator_ui_manager_new(void);
GtkWidget *ptp_simulator_ui_manager_get_menubar(PtpSimulatorUIManager *self);

#endif
