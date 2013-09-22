#ifndef __PTP_SIMULATOR_ACTIONS_H__
#define __PTP_SIMULATOR_ACTIONS_H__

#include <gtk/gtk.h>

void ptp_simulation_action_new(GtkWidget *widget, gpointer data);
void ptp_simulation_action_open(GtkWidget *widget, gpointer data);
void ptp_simulation_action_save(GtkWidget *widget, gpointer data);
void ptp_simulation_action_save_as(GtkWidget *widget, gpointer data);
void ptp_simulation_action_quit(GtkWidget *widget, gpointer data);

void ptp_simulation_action_add(GtkWidget *widget, gpointer data);
void ptp_simulation_action_remove(GtkWidget *widget, gpointer data);

void ptp_simulation_action_play(GtkWidget *widget, gpointer data);
void ptp_simulation_action_pause(GtkWidget *widget, gpointer data);
void ptp_simulation_action_stop(GtkWidget *widget, gpointer data);

#endif
