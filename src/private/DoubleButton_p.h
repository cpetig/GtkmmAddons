// -*- c++ -*-
// Generated by gtkmmproc -- DO NOT MODIFY!
#ifndef _GTKMM_DOUBLEBUTTON_P_H
#define _GTKMM_DOUBLEBUTTON_P_H
#include <gtkmm/private/button_p.h>

#include <glibmm/class.h>

namespace ManuProC
{

class DoubleButton_Class : public Glib::Class
{
public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef DoubleButton CppObjectType;
  typedef doublebutton BaseObjectType;
  typedef doublebuttonClass BaseClassType;
  typedef Gtk::Button_Class CppClassParent;
  typedef GtkButtonClass BaseClassParent;

  friend class DoubleButton;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  const Glib::Class& init();

  static void class_init_function(void* g_class, void* class_data);

  static Glib::ObjectBase* wrap_new(GObject*);

protected:

  //Callbacks (default signal handlers):
  //These will call the *_impl member methods, which will then call the existing default signal callbacks, if any.
  //You could prevent the original default signal handlers being called by overriding the *_impl method.
  static void secondpressed_callback(doublebutton* self, int button);

  //Callbacks (virtual functions):
};


} // namespace ManuProC

#endif /* _GTKMM_DOUBLEBUTTON_P_H */

