
https://git.gnome.org/browse/nautilus/tree/src

ii  libgtk-3-0:amd64                       3.6.0-0ubuntu3.2                           amd64        GTK+ graphical user interface library
ii  libgtk-3-bin                           3.6.0-0ubuntu3.2                           amd64        programs for the GTK+ graphical user interface library
ii  libgtk-3-common                        3.6.0-0ubuntu3.2                           all          common files for the GTK+ graphical user interface library
ii  libgtk-3-dev                           3.6.0-0ubuntu3.2                           amd64        development files for the GTK+ library
ii  libgtk-3-doc                           3.6.0-0ubuntu3.2                           all          documentation for the GTK+ graphical user interface library
ii  libgtk2-perl                           2:1.244-1                                  amd64        Perl interface to the 2.x series of the Gimp Toolkit library
ii  libgtk2.0-0:amd64                      2.24.13-0ubuntu2                           amd64        GTK+ graphical user interface library
ii  libgtk2.0-0:i386                       2.24.13-0ubuntu2                           i386         GTK+ graphical user interface library
ii  libgtk2.0-bin                          2.24.11-0ubuntu1                           amd64        programs for the GTK+ graphical user interface library
ii  libgtk2.0-common                       2.24.11-0ubuntu1                           all          common files for the GTK+ graphical user interface library
ii  libgtk2.0-dev                          2.24.13-0ubuntu2                           amd64        development files for the GTK+ library


struct GObjectClass {
  GTypeClass   g_type_class;

  /* seldom overidden */
  GObject*   (*constructor)                 (GType                  type,
                                             guint                  n_construct_properties,
                                              GObjectConstructParam *construct_properties);
  /* overridable methods */
  void       (*set_property)                (GObject                *object,
                                             guint                   property_id,
                                             const GValue           *value,
                                             GParamSpec             *pspec);
  
  void       (*get_property)                (GObject                *object,
                                             guint                   property_id,
                                             GValue                 *value,
                                             GParamSpec             *pspec);
  
  void       (*dispose)                     (GObject                *object);
  void       (*finalize)                    (GObject                *object);
  /* seldom overidden */
  void       (*dispatch_properties_changed) (GObject                *object,
                                             guint                   n_pspecs,
                                             GParamSpec             **pspecs);
  /* signals */
  void       (*notify)                      (GObject                *object,
                                             GParamSpec             *pspec);

  /* called when done constructing */
  void       (*constructed)                 (GObject                *object);
};

/****************************************************************************
 * configure.ac
 ***************************************************************************/

m4_define(glib_minver,                 2.35.3)
m4_define(gtk_minver,                  3.9.11)

[...]

PKG_CHECK_MODULES(BASE, [
    gtk+-3.0 >= gtk_minver
    glib-2.0 >= glib_minver
])

/****************************************************************************
 * src/nautilus-main.c
 ***************************************************************************/

int
main (int argc, char *argv[])
{
    
    [···]
    
    application = nautilus_application_new ();
    
    [...]
    
}



/****************************************************************************
 * src/nautilus-application.c
 ***************************************************************************/

G_DEFINE_TYPE (NautilusApplication, nautilus_application, GTK_TYPE_APPLICATION);

static void nautilus_application_init (NautilusApplication *application)
static void nautilus_application_finalize (GObject *object)
static void nautilus_application_startup (GApplication *app)
static void nautilus_application_class_init (NautilusApplicationClass *class)

NautilusApplication *
nautilus_application_new (void)
{
    return g_object_new (NAUTILUS_TYPE_APPLICATION,
                         "application-id", "org.gnome.Nautilus",
                         "flags", G_APPLICATION_HANDLES_OPEN,
                         "inactivity-timeout", 12000,
                         "register-session", TRUE,
                         NULL);
}


/****************************************************************************
 * src/nautilus-window.c
 ***************************************************************************/


static void nautilus_window_constructed (GObject *self)
static void nautilus_window_destroy (GtkWidget *object)
static void nautilus_window_init (NautilusWindow *window)
static void nautilus_window_class_init (NautilusWindowClass *class)





















