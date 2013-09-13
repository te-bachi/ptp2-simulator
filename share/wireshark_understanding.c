

Stacktrace

g_signal_connect(byte_view, "button_press_event", G_CALLBACK(byte_view_button_press_cb), [...] ));
[...]
byte_view_button_press_cb(GtkWidget *widget, GdkEvent *event, gpointer data);
byte_view_select(GtkWidget *widget, GdkEventButton *event);
highlight_field(tvbuff_t *tvb, gint byte, GtkTreeView *tree_view, proto_tree *tree);

/****************************************************************************
 * wireshark/ui/gtk/main.c
 * Menu routines
 ***************************************************************************/

static void create_main_window (gint pl_size, gint tv_size, gint bv_size, e_prefs *prefs_p)
{
    
    [...]
    
    /* Main Toolbar */
    main_tb = toolbar_new();
    gtk_widget_show (main_tb);
    
    /* Filter toolbar */
    filter_tb = filter_toolbar_new();
    
    /* Packet list */
    pkt_scrollw = packet_list_create();
    gtk_widget_set_size_request(pkt_scrollw, -1, pl_size);
    gtk_widget_show_all(pkt_scrollw);
    
    /* Tree view */
    tv_scrollw = proto_tree_view_new(&tree_view_gbl);
    gtk_widget_set_size_request(tv_scrollw, -1, tv_size);
    gtk_widget_show(tv_scrollw);
    
    g_signal_connect(gtk_tree_view_get_selection(GTK_TREE_VIEW(tree_view_gbl)),
                   "changed", G_CALLBACK(tree_view_selection_changed_cb), NULL);
    g_signal_connect(tree_view_gbl, "button_press_event", G_CALLBACK(popup_menu_handler),
                   g_object_get_data(G_OBJECT(popup_menu_object), PM_TREE_VIEW_KEY));
    gtk_widget_show(tree_view_gbl);
    
    /* Byte view. */
    byte_nb_ptr_gbl = byte_view_new();
    gtk_widget_set_size_request(byte_nb_ptr_gbl, -1, bv_size);
    gtk_widget_show(byte_nb_ptr_gbl);
    
    g_signal_connect(byte_nb_ptr_gbl, "button_press_event", G_CALLBACK(popup_menu_handler),
                   g_object_get_data(G_OBJECT(popup_menu_object), PM_BYTES_VIEW_KEY));
    
    [...]
    
}




/****************************************************************************
 * wireshark/ui/gtk/main_menubar.c
 * Menu routines
 ***************************************************************************/

static GtkUIManager *ui_manager_bytes_menu = NULL;

static const char *ui_desc_bytes_menu_popup =
"<ui>\n"
"  <popup name='BytesMenuPopup' action='PopupAction'>\n"
"     <menuitem name='HexView' action='/HexView'/>\n"
"     <menuitem name='BitsView' action='/BitsView'/>\n"
"  </popup>\n"
"</ui>\n";


static const GtkRadioActionEntry bytes_menu_radio_action_entries [] =
{
    /* name,    stock id,        label,      accel,  tooltip,  value */
    { "/HexView",   NULL,       "Hex View",   NULL,   NULL,     BYTES_HEX },
    { "/BitsView",  NULL,       "Bits View",  NULL,   NULL,     BYTES_BITS },
};

GtkWidget *
main_menu_new(GtkAccelGroup ** table)
{
    
    [...]
    
    if (initialize)
        menus_init();
    
    [...]
    
}

static void
menus_init(void)
{
    
    [...]
    
        /*
         * Hex dump pop-up menu.
         * We provide our own empty menu to suppress the default pop-up menu
         * for text widgets.
         */
        packet_list_byte_menu_action_group = gtk_action_group_new ("PacketListByteMenuPopUpActionGroup");


        gtk_action_group_add_radio_actions  (packet_list_byte_menu_action_group,            /* the action group */
                                    (GtkRadioActionEntry *)bytes_menu_radio_action_entries, /* an array of radio action descriptions  */
                                    G_N_ELEMENTS(bytes_menu_radio_action_entries),          /* the number of entries */
                                    recent.gui_bytes_view,                                  /* the value of the action to activate initially, or -1 if no action should be activated  */
                                    G_CALLBACK(select_bytes_view_cb),                       /* the callback to connect to the changed signal  */
                                    popup_menu_object);                                     /* data to pass to the action callbacks  */

        ui_manager_bytes_menu = gtk_ui_manager_new ();

        gtk_ui_manager_insert_action_group (ui_manager_bytes_menu,
            packet_list_byte_menu_action_group,
            0); /* the position at which the group will be inserted.  */
        gtk_ui_manager_add_ui_from_string (ui_manager_bytes_menu, ui_desc_bytes_menu_popup, -1, &error);
        
}

/****************************************************************************
 * wireshark/ui/gtk/packet_panes.c
 * Routines for GTK+ packet display (packet details and hex dump panes)
 ***************************************************************************/

/* Calls functions for different mouse-button presses. */
static gboolean
byte_view_button_press_cb(GtkWidget *widget, GdkEvent *event, gpointer data)
{
    [...]
    
    if (event->type == GDK_BUTTON_PRESS) {
        event_button = (GdkEventButton *) event;
        
        /* To qoute the "Gdk Event Structures" doc:
         * "Normally button 1 is the left mouse button, 2 is the middle button, and 3 is the right button" */
        switch (event_button->button) {
            case 1: return byte_view_select(widget, event_button);
            case 3: return popup_menu_handler(widget, event, data);
            [...]
        }
    }
    
    [...]
}


/* If the user selected a certain byte in the byte view, try to find
 * the item in the GUI proto_tree that corresponds to that byte, and:
 *
 *    if we succeed, select it, and return TRUE;
 *    if we fail, return FALSE. */
gboolean
byte_view_select(GtkWidget *widget, GdkEventButton *event)
{
    [...]
    
    return highlight_field(tvb, byte, tree_view, tree);
}

/* This highlights the field in the proto tree that is at position byte */
gboolean
highlight_field(tvbuff_t *tvb, gint byte, GtkTreeView *tree_view, proto_tree *tree)
{
    
}

GtkWidget *
byte_view_new(void)
{
    GtkWidget *byte_nb;
    
    byte_nb = gtk_notebook_new();
    
    /* Add a placeholder byte view so that there's at least something
       displayed in the byte view notebook. */
    add_byte_tab(byte_nb, "", NULL, NULL, NULL);

    return byte_nb;
    
}

GtkWidget *
add_byte_tab(GtkWidget *byte_nb, const char *name, tvbuff_t *tvb,
             proto_tree *tree, GtkWidget *tree_view)
{
    
}


/****************************************************************************
 * wireshark/ui/gtk/packet_win.c
 * Routines for popping a window to display current packet
 ***************************************************************************/

GtkWidget *toolbar_new(void)
{
    
    [...]
    
    /* toolbar will be horizontal, with both icons and text (as default here) */
    /* (this will usually be overwritten by the preferences setting) */
    main_tb = gtk_toolbar_new();
    gtk_orientable_set_orientation(GTK_ORIENTABLE(main_tb),
                                GTK_ORIENTATION_HORIZONTAL);
    
    [...]
    
    toolbar_item(open_button, main_tb, GTK_STOCK_OPEN, "Open a capture file...", file_open_cmd_cb, NULL);
    
    toolbar_item(save_button, main_tb, WIRESHARK_STOCK_SAVE, "Save this capture file", file_save_cmd_cb, NULL);
    
    toolbar_item(close_button, main_tb, GTK_STOCK_CLOSE, "Close this capture file", file_close_cmd_cb, NULL);
    
    [...]
}

/****************************************************************************
 * wireshark/ui/gtk/main_toolbar.c
 * 
 ***************************************************************************/


/****************************************************************************
 * wireshark/ui/gtk/bytes_view.c
 * 
 ***************************************************************************/

static void
bytes_view_init(BytesView *bv) {
    
}

static void
bytes_view_class_init(BytesViewClass *klass) {
    
}


/****************************************************************************
 * wireshark/ui/gtk/packet_list.c
 * 
 ***************************************************************************/

GtkWidget *packet_list_create(void)
static GtkWidget *create_view_and_model(void)

static void
show_cell_data_func(GtkTreeViewColumn *col _U_, GtkCellRenderer *renderer,
                    GtkTreeModel *model, GtkTreeIter *iter, gpointer data _U_)
{
    frame_data *fdata = packet_list_get_record(model, iter);

    gboolean color_on;
    GdkColor fg_gdk;
    GdkColor bg_gdk;

    if (fdata->flags.ignored) {
        color_t_to_gdkcolor(&fg_gdk, &prefs.gui_ignored_fg);
        color_t_to_gdkcolor(&bg_gdk, &prefs.gui_ignored_bg);
        color_on = TRUE;
    } else if (fdata->flags.marked) {
        color_t_to_gdkcolor(&fg_gdk, &prefs.gui_marked_fg);
        color_t_to_gdkcolor(&bg_gdk, &prefs.gui_marked_bg);
        color_on = TRUE;
    } else if (fdata->color_filter) {
        const color_filter_t *color_filter = (const color_filter_t *)fdata->color_filter;
        
        color_t_to_gdkcolor(&fg_gdk, &color_filter->fg_color);
        color_t_to_gdkcolor(&bg_gdk, &color_filter->bg_color);
        color_on = enable_color;
    } else
        color_on = FALSE;

    if (color_on) {
        g_object_set(renderer,
             "foreground-gdk", &fg_gdk,
             "foreground-set", TRUE,
             "background-gdk", &bg_gdk,
             "background-set", TRUE,
             NULL);
    } else {
        g_object_set(renderer,
             "foreground-set", FALSE,
             "background-set", FALSE,
             NULL);
    }
}
