#ifndef __GTK_FRAME_HIG_H__
#define __GTK_FRAME_HIG_H__

#include <gtk/gtk.h>

GtkWidget* gtk_frame_hig_new (const char *title,
			      gboolean horizontal_expand);

void gtk_frame_hig_add (GtkWidget *vbox, 
			GtkWidget *frame_hig,
			gboolean vertical_expand);

void gtk_frame_hig_add_item (GtkWidget *frame_hig,
			     GtkWidget *item,
			     gboolean horizontal_expand);

void gtk_frame_hig_add_two_item (GtkWidget *frame_hig,
				 GtkWidget *left_item,
				 GtkWidget *right_item,
				 gboolean left);

#endif /* __GTK_FRAME_HIG_H__ */
