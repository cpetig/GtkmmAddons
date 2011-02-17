// Code to work aroung gtk bug 141834

#include <gtk/gtkexpander.h>

extern "C" {
gulong
gtk_expander_hook_size_to_parent(GtkExpander *expander);
}
