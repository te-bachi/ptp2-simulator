

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
    /* Main window */
    top_level = window_new(GTK_WINDOW_TOPLEVEL, "");
    set_titlebar_for_capture_file(NULL);

    gtk_widget_set_name(top_level, "main window");
    g_signal_connect(top_level, "delete_event", G_CALLBACK(main_window_delete_event_cb), NULL);
    g_signal_connect(G_OBJECT(top_level), "window_state_event", G_CALLBACK(window_state_event_cb), NULL);
    g_signal_connect(G_OBJECT(top_level), "key-press-event", G_CALLBACK(top_level_key_pressed_cb), NULL );

    /* Vertical container for menu bar, toolbar(s), paned windows and progress/info box */
    main_vbox = ws_gtk_box_new(GTK_ORIENTATION_VERTICAL, 1, FALSE);

	gtk_container_set_border_width(GTK_CONTAINER(main_vbox), 0);
    gtk_container_add(GTK_CONTAINER(top_level), main_vbox);
    gtk_widget_show(main_vbox);

    /* Menu bar */
    menubar = main_menu_new(&accel);
    gtk_window_add_accel_group(GTK_WINDOW(top_level), accel);
    gtk_widget_show(menubar);

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
    
    g_signal_connect(gtk_tree_view_get_selection(GTK_TREE_VIEW(tree_view_gbl)), "changed", G_CALLBACK(tree_view_selection_changed_cb), NULL);
    g_signal_connect(tree_view_gbl, "button_press_event", G_CALLBACK(popup_menu_handler), g_object_get_data(G_OBJECT(popup_menu_object), PM_TREE_VIEW_KEY));
    gtk_widget_show(tree_view_gbl);
    
    /* Byte view. */
    byte_nb_ptr_gbl = byte_view_new();
    gtk_widget_set_size_request(byte_nb_ptr_gbl, -1, bv_size);
    gtk_widget_show(byte_nb_ptr_gbl);
    
    g_signal_connect(byte_nb_ptr_gbl, "button_press_event", G_CALLBACK(popup_menu_handler), g_object_get_data(G_OBJECT(popup_menu_object), PM_BYTES_VIEW_KEY));
    
    /* Panes for the packet list, tree, and byte view */
    main_pane_v1 = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
    gtk_widget_show(main_pane_v1);
    main_pane_v2 = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
    gtk_widget_show(main_pane_v2);
    main_pane_h1 = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_widget_show(main_pane_h1);
    main_pane_h2 = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_widget_show(main_pane_h2);
    
    [...]
    
}

/*
 * Rearrange the main window widgets
 */
void main_widgets_rearrange(void) {
    
    [...]
    
    /* fill the main layout panes */
    switch(prefs.gui_layout_type) {
        case(layout_type_5):
            main_first_pane  = main_pane_v1;
            main_second_pane = main_pane_v2;
            split_top_left = FALSE;
            break;
        case(layout_type_2):
            main_first_pane  = main_pane_v1;
            main_second_pane = main_pane_h1;
            split_top_left = FALSE;
            break;
        case(layout_type_1):
            main_first_pane  = main_pane_v1;
            main_second_pane = main_pane_h1;
            split_top_left = TRUE;
            break;
        case(layout_type_4):
            main_first_pane  = main_pane_h1;
            main_second_pane = main_pane_v1;
            split_top_left = FALSE;
            break;
        case(layout_type_3):
            main_first_pane  = main_pane_h1;
            main_second_pane = main_pane_v1;
            split_top_left = TRUE;
            break;
        case(layout_type_6):
            main_first_pane  = main_pane_h1;
            main_second_pane = main_pane_h2;
            split_top_left = FALSE;
            break;
        default:
            main_first_pane = NULL;
            main_second_pane = NULL;
            g_assert_not_reached();
    }
    
    if (split_top_left) {
        first_pane_widget1 = main_second_pane;
        second_pane_widget1 = main_widget_layout(prefs.gui_layout_content_1);
        second_pane_widget2 = main_widget_layout(prefs.gui_layout_content_2);
        first_pane_widget2 = main_widget_layout(prefs.gui_layout_content_3);
    } else {
        first_pane_widget1 = main_widget_layout(prefs.gui_layout_content_1);
        first_pane_widget2 = main_second_pane;
        second_pane_widget1 = main_widget_layout(prefs.gui_layout_content_2);
        second_pane_widget2 = main_widget_layout(prefs.gui_layout_content_3);
    }
    if (first_pane_widget1 != NULL)
        gtk_paned_add1(GTK_PANED(main_first_pane), first_pane_widget1);
    if (first_pane_widget2 != NULL)
        gtk_paned_add2(GTK_PANED(main_first_pane), first_pane_widget2);
    if (second_pane_widget1 != NULL)
        gtk_paned_pack1(GTK_PANED(main_second_pane), second_pane_widget1, TRUE, TRUE);
    if (second_pane_widget2 != NULL)
        gtk_paned_pack2(GTK_PANED(main_second_pane), second_pane_widget2, FALSE, FALSE);
    
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

static const char *ui_desc_menubar =
"<ui>\n"
"  <menubar name ='Menubar'>\n"
"    <menu name= 'FileMenu' action='/File'>\n"
"      <menuitem name='Open' action='/File/Open'/>\n"
"      <menu name='OpenRecent' action='/File/OpenRecent'>\n"

       [...]
       
"      <separator/>\n"
"      <menuitem name='AboutWireshark' action='/Help/AboutWireshark'/>\n"
"    </menu>\n"
"  </menubar>\n"
"</ui>\n";

static const GtkActionEntry main_menu_bar_entries[] = {
  /* Top level */
  { "/File",                    NULL,                              "_File",              NULL,                   NULL,           NULL },
  { "/Edit",                    NULL,                              "_Edit",              NULL,                   NULL,           NULL },
  
  [...]
  
  { "/View/TimeDisplayFormat/FileFormatPrecision-Nanoseconds",    NULL, "Nanoseconds:   0.123456789",         NULL, NULL, TS_PREC_FIXED_NSEC },
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
