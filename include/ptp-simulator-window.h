#ifndef __PTP_SIMULATOR_WINDOW_H__
#define __PTP_SIMULATOR_WINDOW_H__

#include <gtk/gtk.h>

#include "ptp-simulator-ui-manager.h"

typedef struct _PtpSimulatorWindow              PtpSimulatorWindow;
typedef struct _PtpSimulatorWindowClass         PtpSimulatorWindowClass;

#define PTP_SIMULATOR_TYPE_WINDOW               (ptp_simulator_window_get_type())
#define PTP_SIMULATOR_WINDOW(obj)               (G_TYPE_CHECK_INSTANCE_CAST((obj), PTP_SIMULATOR_TYPE_WINDOW, PtpSimulatorWindow))
#define PTP_SIMULATOR_IS_WINDOW(obj)            (G_TYPE_CHECK_INSTANCE_TYPE((obj), PTP_SIMULATOR_TYPE_WINDOW))
#define PTP_SIMULATOR_WINDOW_CLASS(klass)       (G_TYPE_CHECK_CLASS_CAST((klass),  PTP_SIMULATOR_TYPE_WINDOW, PtpSimulatorWindowClass))
#define PTP_SIMULATOR_IS_WINDOW_CLASS(klass)    (G_TYPE_CHECK_CLASS_TYPE((klass),  PTP_SIMULATOR_TYPE_WINDOW))
#define PTP_SIMULATOR_WINDOW_GET_CLASS(obj)     (G_TYPE_INSTANCE_GET_CLASS((obj),  PTP_SIMULATOR_TYPE_WINDOW, PtpSimulatorWindowClass))

struct _PtpSimulatorWindow {
    GtkWindow                    parent_instance;
    
    PtpSimulatorUIManager       *ui_manager;
    
    GtkWidget                   *vbox;
    GtkWidget                   *menubar;
    GtkWidget                   *toolbar;
    GtkWidget                   *paned_one;
    GtkWidget                   *paned_two;
    GtkWidget                   *packet_list_win;
    GtkWidget                   *packet_list_viewport;
    GtkWidget                   *packet_list;
    GtkWidget                   *packet_detail_win;
    GtkWidget                   *packet_detail_viewport;
    GtkWidget                   *packet_detail;
    GtkWidget                   *packet_dump_win;
    GtkWidget                   *packet_dump_viewport;
    GtkWidget                   *packet_dump;
    GtkWidget                   *statusbar;
};

struct _PtpSimulatorWindowClass {
    GtkWindowClass  parent_class;
};

GtkWidget *ptp_simulator_window_new(void);

#endif
