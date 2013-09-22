#ifndef __PTP_SIMULATOR_MENUBAR_H__
#define __PTP_SIMULATOR_MENUBAR_H__

#include "ptp-simulator-actions.h"

static const GtkActionEntry menubar_action_entries[] = {
    /* Top level */
    { "/File",                    NULL,                              "_File",              NULL,                   NULL,           NULL },
    { "/Edit",                    NULL,                              "_Edit",              NULL,                   NULL,           NULL },
    { "/View",                    NULL,                              "_View",              NULL,                   NULL,           NULL },
    { "/Help",                    NULL,                              "_Help",              NULL,                   NULL,           NULL },
    
    { "/File/Open",               GTK_STOCK_OPEN,                    "_Open...",           "<control>O",           "Open a file",  G_CALLBACK(ptp_simulation_action_open) },
    { "/File/Save",               GTK_STOCK_SAVE,                    "_Save",              "<control>S",           NULL,           G_CALLBACK(ptp_simulation_action_save) },
    { "/File/SaveAs",             GTK_STOCK_SAVE_AS,                 "Save _As...",        "<shift><control>S",    NULL,           G_CALLBACK(ptp_simulation_action_save_as) },
    { "/File/Quit",               GTK_STOCK_QUIT,                    "_Quit",              "<control>Q",           NULL,           G_CALLBACK(ptp_simulation_action_quit) },
};

static const char *menubar_definition =
"<ui>\n"
"  <menubar name='Menubar'>\n"
"    <menu name='FileMenu' action='/File'>\n"
"      <menuitem name='Open' action='/File/Open'/>\n"
"      <menuitem name='Save' action='/File/Save'/>\n"
"      <menuitem name='SaveAs' action='/File/SaveAs'/>\n"
"      <separator/>\n"
"        <menuitem name='Quit' action='/File/Quit'/>\n"
"    </menu>\n"
"    <menu name='EditMenu' action='/Edit'>\n"
"    </menu>\n"
"    <menu name='ViewMenu' action='/View'>\n"
"    </menu>\n"
"    <menu name='HelpMenu' action='/Help'>\n"
"    </menu>\n"
"  </menubar>\n"
"</ui>\n";

#endif

