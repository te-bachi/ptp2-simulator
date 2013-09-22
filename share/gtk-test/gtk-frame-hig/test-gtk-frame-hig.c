#include <gtk/gtk.h>

#include "gtk-frame-hig.h"

int main(void)
{
  GtkWidget *window;
  GtkWidget *vbox_win;
  GtkWidget *frame;
  GtkWidget *vbox;
  GtkWidget *radio;
  GtkWidget *label;
  GtkWidget *entry;

  gtk_init (NULL, NULL);
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "GTK+ Frame HIG");
  g_signal_connect (window,
                    "destroy",
                    G_CALLBACK (gtk_main_quit),
                    NULL);

  vbox_win = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (window), vbox_win);


  /* GTK+ Frame */
  frame = gtk_frame_new ("Vanilla GTK+ Frame");
  gtk_box_pack_start_defaults (GTK_BOX (vbox_win), frame);

  vbox = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (frame), vbox);

  /* Radio */
  radio = gtk_radio_button_new_with_label (NULL, "First radio button");
  gtk_box_pack_start (GTK_BOX (vbox), radio, FALSE, FALSE, 0);

  radio = gtk_radio_button_new_with_label_from_widget (
    GTK_RADIO_BUTTON(radio), "Second radio button");
  gtk_box_pack_start (GTK_BOX (vbox), radio, FALSE, FALSE, 0);


  /* GTK+ HIG Frame */
  frame = gtk_frame_hig_new ("HIG Frame", FALSE);
  gtk_frame_hig_add (vbox_win, frame, FALSE);

  /* Radio */
  radio = gtk_radio_button_new_with_label (NULL, "First radio button");
  gtk_frame_hig_add_item (frame, radio, FALSE);

  radio = gtk_radio_button_new_with_label_from_widget (
    GTK_RADIO_BUTTON (radio), "Second radio button");
  gtk_frame_hig_add_item (frame, radio, FALSE);


  /* Label + entry */
  label = gtk_label_new("Says me something here:");
  entry = gtk_entry_new();
  /* Last arg to align on left */
  gtk_frame_hig_add_two_item (frame, label, entry, FALSE);

  label = gtk_label_new("Once again:");
  entry = gtk_entry_new();
  gtk_frame_hig_add_two_item (frame, label, entry, FALSE);

  gtk_widget_show_all (window);

  gtk_main ();
	
  return 0;
}
