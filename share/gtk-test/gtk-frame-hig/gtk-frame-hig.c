#include <gtk/gtk.h>

static GtkWidget* frame_hig_title_create (const char *title)
{
  GtkWidget *label;
  char *markup_title;
  
  markup_title = g_strdup_printf ("<span weight=\"bold\">%s</span>", title);
  label = gtk_label_new (markup_title);
  g_free (markup_title);
  
  gtk_misc_set_alignment (GTK_MISC (label), 0.0, 0.5);
  gtk_label_set_use_markup (GTK_LABEL (label), TRUE);
  
  return label;
}

GtkWidget* gtk_frame_hig_new (const char *title,
                              gboolean horizontal_expand)
{
  GtkWidget *vbox_frame;
  GtkWidget *myframe;
  GtkWidget *label;
  GtkWidget *hbox;
  GtkWidget *space4;
  GtkSizeGroup *size_goup;
  
  /* Vbox around my frame */
  vbox_frame = gtk_vbox_new (FALSE, 6);
  
  /* Line 1 */
  label = frame_hig_title_create (title);
  gtk_box_pack_start (GTK_BOX (vbox_frame), label, FALSE, FALSE, 0);
  
  /* Line 2 */
  hbox = gtk_hbox_new (FALSE, 6);
  gtk_box_pack_start (GTK_BOX (vbox_frame), hbox, TRUE, TRUE, 0);
  
  /* Column 1 (line 2) */
  space4 = gtk_label_new ("    ");
  gtk_box_pack_start (GTK_BOX (hbox), space4, FALSE, FALSE, 0);
  
  /* Column 2 (line 2) */
  myframe = gtk_vbox_new (FALSE, 6);
  gtk_box_pack_start (GTK_BOX (hbox), myframe,
                      horizontal_expand, horizontal_expand, 0);
  
  /* Save ref to vbox to add item with frame_hig_add */
  g_object_set_data (G_OBJECT (myframe), "vbox_frame", vbox_frame);
  
  size_goup = gtk_size_group_new (GTK_SIZE_GROUP_HORIZONTAL);
  g_object_set_data (G_OBJECT (myframe), "size_group", size_goup);
  
  /* It's not a frame but a vbox! */
  return myframe;
}

void gtk_frame_hig_add (GtkWidget *box, GtkWidget *myframe, gboolean vertical_expand)
{
  GtkWidget *vbox_frame;

  /* Box properties */
  gtk_container_set_border_width (GTK_CONTAINER (box), 12);
  gtk_box_set_spacing (GTK_BOX (box), 18);

  /* Add the frame's vbox (mother) to the vbox in argument */
  vbox_frame = g_object_get_data (G_OBJECT (myframe), "vbox_frame");
  gtk_box_pack_start (GTK_BOX (box), vbox_frame,
                      vertical_expand, vertical_expand, 0);
}

/* For check boxes and radio buttons */
void gtk_frame_hig_add_item (GtkWidget *myframe, GtkWidget *item, gboolean horizontal_expand)
{
  gtk_box_pack_start (GTK_BOX (myframe), item,
                      horizontal_expand, horizontal_expand, 0);
}

/* For text boxes, options menus, etc */
void gtk_frame_hig_add_two_item (GtkWidget *myframe,
                                 GtkWidget *item_left,
                                 GtkWidget *item_right,
                                 gboolean to_left)
{
  GtkWidget *hbox_item;
  GtkSizeGroup *size_goup;

  size_goup = g_object_get_data (G_OBJECT(myframe), "size_group");
  gtk_size_group_add_widget (GTK_SIZE_GROUP (size_goup), item_left);

  hbox_item = gtk_hbox_new (FALSE, 6);
  gtk_box_pack_start (GTK_BOX (myframe), hbox_item,
                      FALSE, FALSE, 0);
        
  if (to_left)
    /* Align on left */
    gtk_misc_set_alignment (GTK_MISC (item_left), 0.0, 0.5);
  else
    /* Align on right */
    gtk_misc_set_alignment (GTK_MISC (item_left), 1.0, 0.5);

  gtk_box_pack_start (GTK_BOX (hbox_item), item_left, 
                      FALSE, FALSE, 0);

  if (GTK_IS_LABEL (item_right))
    gtk_misc_set_alignment (GTK_MISC(item_right), 0.0, 0.0);

  gtk_box_pack_start (GTK_BOX(hbox_item), item_right, TRUE, TRUE, 0);
}
