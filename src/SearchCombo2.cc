#include "SearchCombo2.h"
#include <gtkmm/liststore.h>
#include <cassert>
#include <gtk/gtkmain.h>
#include <gtk/gtkmenu.h>
#include <gtkmm/togglebutton.h>

#include <iostream>

#if 1
#include <stdio.h>
#define DEBUG(x) x
#else
#define DEBUG(x)
#endif

#define MAYBE(x) 
// x

struct Gtk::SearchCombo2::Model : Gtk::ListStore
//virtual Glib::Object, Gtk::TreeModel
{ 
private:
  Gtk::ComboBoxEntry *combo;
  Model(const TreeModelColumnRecord& columns, Gtk::ComboBoxEntry *e);
//  std::vector<std::string> results;

  bool fill_idle();
  bool close_search();
  void clear_list();
  void fill_list();
public:
  sigc::signal2<void,gboolean *,GtkSCContext> search;
  
  static Glib::RefPtr<Model> create(const TreeModelColumnRecord& columns, Gtk::ComboBoxEntry *e);
  
  void entry_changed();
  void stop_if_running();
  void fill_list_if_necessary();

  bool start_idle:1;	/** start search at idle time not in focus_in */

private:
  /* internal state variables */
  sigc::connection idle_conn;
  
  bool backspace:1;	/** last key was backspace -> do not autocomplete */
  bool search_in_progress:1;	/** whether a search is in progress */
  bool already_started:1;	/** if not true we have to start at idle time */
  bool search_finished:1;	/** search is finished, simply display */
  bool value_selected:1;	/** a value has been selected, do not search without explicit request */
  bool reopen:1;		/** next open should be reopen */

/*
   typedef const TreeModel::iterator& vfunc_constiter_t;
   typedef TreeModel::iterator& vfunc_iter_t;
// vfunc overrides for my tree model
   virtual bool row_draggable_vfunc(const Gtk::TreeModel::Path& path) const;
   virtual bool drag_data_get_vfunc(const Gtk::TreeModel::Path& path, Gtk::SelectionData& selection_data) const;
   virtual bool drag_data_delete_vfunc(const Gtk::TreeModel::Path& path);
   virtual bool drag_data_received_vfunc(const Gtk::TreeModel::Path& dest, const Gtk::SelectionData& selection_data);
   virtual bool row_drop_possible_vfunc(const Gtk::TreeModel::Path& dest, const Gtk::SelectionData& selection_data) const;

   virtual Gtk::TreeModelFlags get_flags_vfunc() const;
   virtual int get_n_columns_vfunc() const;
   virtual GType get_column_type_vfunc(int index) const;
   virtual void get_value_vfunc(vfunc_constiter_t iter, int column, Glib::ValueBase& value) const;
   bool iter_next_vfunc(vfunc_constiter_t iter, vfunc_iter_t iter_next) const;
   virtual bool iter_children_vfunc(vfunc_constiter_t parent, vfunc_iter_t iter) const;
   virtual bool iter_has_child_vfunc(vfunc_constiter_t iter) const;
   virtual int iter_n_children_vfunc(vfunc_constiter_t iter) const;
   virtual int iter_n_root_children_vfunc() const;
   virtual bool iter_nth_child_vfunc(vfunc_constiter_t parent, int n, vfunc_iter_t iter) const;
   virtual bool iter_nth_root_child_vfunc(int n, vfunc_iter_t iter) const;
   virtual bool iter_parent_vfunc(vfunc_constiter_t child, vfunc_iter_t iter) const;
   virtual bool get_iter_vfunc(const Path& path, vfunc_iter_t iter) const;
   virtual Path get_path_vfunc(const TreeModel::iterator& iter) const; */
};

Gtk::SearchCombo2::Model::Model(const TreeModelColumnRecord& columns, Gtk::ComboBoxEntry *e)
  : ListStore(columns), combo(e),
    start_idle(true), backspace(), search_in_progress(), already_started(),
    search_finished(), value_selected(), reopen()
//  : Glib::ObjectBase( typeid(Model) ), //register a custom GType.
//    Glib::Object() //The custom GType is actually registered here.
{
}

void Gtk::SearchCombo2::Model::clear_list()
{ stop_if_running();
  Gtk::ListStore::clear();
//  combo->popdown();
  search_finished=false;
  value_selected=false;
}

void Gtk::SearchCombo2::Model::fill_list_if_necessary()
{ if (!search_in_progress && !search_finished)
    fill_list();
}

void Gtk::SearchCombo2::Model::fill_list()
{ gboolean continue_=false;
  reopen=value_selected;
  clear_list();
  assert(!search_in_progress);
  search_in_progress=true;
  already_started=false;
  value_selected=false;
  DEBUG(printf("SCB fl: value_selected=%d si=%d\n",value_selected,start_idle));
   
/*  if (!start_idle)
  {
  } else */
    continue_=true;
  if (continue_)
  { idle_conn=Glib::signal_idle().connect(sigc::mem_fun(*this,&Model::fill_idle));
    DEBUG(printf("SCB fl: idle_handler @%p\n",this));
  }
  else close_search();
//  combo->popup();
}

void Gtk::SearchCombo2::Model::entry_changed()
{ // narrow optimization (gtksearchcombo.c:712)
  fill_list();
//  combo->get_entry()->grab_focus();
}

bool Gtk::SearchCombo2::Model::close_search()
{ search_in_progress=false;
  search_finished=true;
  idle_conn.disconnect();
  search(0, GTK_SEARCH_CLOSE);
  /* if (autoexpand && !backspace)
  { 
  } */
  return false;
}

bool Gtk::SearchCombo2::Model::fill_idle()
{ gboolean continue_=false;
  DEBUG(printf("SCB: fill_idle\n"));
  // THREADS_ENTER?
  assert(search_in_progress && !search_finished);
  DEBUG(printf("fill idle: already_started=%d\n",already_started));
  search(&continue_, already_started?GTK_SEARCH_FETCH:
    (reopen?GTK_SEARCH_REOPEN:GTK_SEARCH_OPEN));
  already_started=true;
  if (!continue_)
  { DEBUG(printf("SCB fi: idle stopped\n"));
    close_search();
  }
  DEBUG(printf("SCB: fill_idle ended\n"));
  return continue_;
}

void Gtk::SearchCombo2::Model::stop_if_running()
{ if (search_in_progress) 
  { idle_conn.disconnect();
    search_in_progress=false;
    if (already_started)
      search(0, GTK_SEARCH_CLOSE);
  }
}

Glib::RefPtr<Gtk::SearchCombo2::Model> Gtk::SearchCombo2::Model::create(const TreeModelColumnRecord& columns, Gtk::ComboBoxEntry *e)
{ return Glib::RefPtr<Model>(new Model(columns,e));
}

// HACK !!!!
#include <gtk/gtkcombobox.h>
#include <gtk/gtktogglebutton.h>
#include <gtk/gtkwindow.h>
#include <gtkmm/window.h>

struct _GtkComboBoxPrivate
{
  GtkTreeModel *model;

  gint col_column;
  gint row_column;

  gint wrap_width;

  GtkTreeRowReference *active_row;

  GtkWidget *tree_view;
  GtkTreeViewColumn *column;

  GtkWidget *cell_view;
  GtkWidget *cell_view_frame;

  GtkWidget *button;
  GtkWidget *box;
  GtkWidget *arrow;
  GtkWidget *separator;

  GtkWidget *popup_widget;
  GtkWidget *popup_window;
  GtkWidget *popup_frame;
  GtkWidget *scrolled_window;

  guint inserted_id;
  guint deleted_id;
  guint reordered_id;
  guint changed_id;
  guint popup_idle_id;
  guint scroll_timer;
  guint resize_idle_id;

  gint width;
  gint height;
  GSList *cells;

  guint popup_in_progress : 1;
  guint popup_shown : 1;
  guint add_tearoffs : 1;
  guint has_frame : 1;
  guint is_cell_renderer : 1;
  guint editing_canceled : 1;
  guint auto_scroll : 1;
  guint focus_on_click : 1;

  GtkTreeViewRowSeparatorFunc row_separator_func;
  gpointer                    row_separator_data;
  GtkDestroyNotify            row_separator_destroy;

  gchar *tearoff_title;
};
// ENDHACK

void Gtk::SearchCombo2::on_entry_changed()
{ mymodel->entry_changed();
  // popup();
  Glib::wrap(GTK_TOGGLE_BUTTON(GTK_COMBO_BOX(gobj())->priv->button))
    ->set_active(true);
  // reget the focus ...
  if (GTK_IS_MENU (GTK_COMBO_BOX(gobj())->priv->popup_widget))
    {
      gtk_menu_popdown (GTK_MENU (GTK_COMBO_BOX(gobj())->priv->popup_widget));
      return;
    }
  if (GTK_COMBO_BOX(gobj())->priv->popup_idle_id > 0)
    {
      g_source_remove (GTK_COMBO_BOX(gobj())->priv->popup_idle_id);
      GTK_COMBO_BOX(gobj())->priv->popup_idle_id = 0;
    }
  gtk_grab_remove(GTK_COMBO_BOX(gobj())->priv->popup_window);
  get_entry()->grab_focus();
}

bool Gtk::SearchCombo2::popup_key_pr(GdkEventKey* k)
{ return on_key_press_event(k);
}

bool Gtk::SearchCombo2::popup_key_rel(GdkEventKey* k)
{ return on_key_release_event(k);
}

void Gtk::SearchCombo2::init()
{ mymodel=Model::create(m_text_columns,this);
  set_model(mymodel);
  set_text_column(m_text_columns.m_column);
  get_entry()->signal_changed().connect(sigc::mem_fun(*this,&SearchCombo2::on_entry_changed));
  signal_changed().connect(signal_activate().make_slot());
  get_entry()->signal_activate().connect(signal_activate().make_slot());
//  sigc::mem_fun(*this,&SearchCombo2::on_changed));
  Gtk::CellRendererText *crt=Gtk::manage(new Gtk::CellRendererText());
  pack_start(*crt);
//  crt->property_foreground()="red";
  MAYBE(crt->property_xalign()=0);
//  crt->set_xalign(0);
  MAYBE(crt->property_alignment()=Pango::ALIGN_LEFT);
//  ->priv->column
//  ->priv->popup_window
//  ->priv->button
  MAYBE(add_attribute(crt->property_text(), m_text_columns.m_column));
  set_focus_on_click(false);
  // gtk+ 2.10
  // Glib::PropertyProxy<bool>(this,"popup-shown").signal_changed()
  //      .connect(sigc::mem_fun(*this,&SearchCombo2::popupdown));
  // HACK
  MAYBE(Glib::wrap(GTK_COMBO_BOX(gobj())->priv->column)->set_alignment(0));
  assert(GTK_IS_TOGGLE_BUTTON(GTK_COMBO_BOX(gobj())->priv->button));
  Glib::wrap(GTK_TOGGLE_BUTTON(GTK_COMBO_BOX(gobj())->priv->button))
    ->signal_toggled().connect(sigc::mem_fun(*this,&SearchCombo2::popupdown));
//  Glib::PropertyProxy<bool>(this,"appears-as-list").set_value(true);
//  std::cerr << "appears-as-list " << Glib::PropertyProxy<bool>(this,"appears-as-list").get_value() << '\n';
#if 0    
  Glib::wrap(GTK_WINDOW(GTK_COMBO_BOX(gobj())->priv->popup_window))->signal_key_press_event()
    .connect(sigc::mem_fun(*this,&SearchCombo2::popup_key_pr));
  Glib::wrap(GTK_WINDOW(GTK_COMBO_BOX(gobj())->priv->popup_window))->signal_key_release_event()
    .connect(sigc::mem_fun(*this,&SearchCombo2::popup_key_rel));
#endif
  // ENDHACK
}

Gtk::SearchCombo2::SearchCombo2(bool always_fill, bool autoexpand)
{ init();
}

#if 0
Gtk::SearchCombo2::SearchCombo2(TextModelColumns const& col)
  : m_text_columns(col)
{ init();
}
#endif

void Gtk::SearchCombo2::popupdown()
{ if (Glib::wrap(GTK_TOGGLE_BUTTON(GTK_COMBO_BOX(gobj())->priv->button))
      ->get_active())
  { MAYBE(Glib::wrap(GTK_COMBO_BOX(gobj())->priv->column)->set_alignment(0));
    mymodel->fill_list_if_necessary();
//    get_entry()->grab_focus();
#if 0    
    Glib::wrap(GTK_WINDOW(GTK_COMBO_BOX(gobj())->priv->popup_window))->signal_key_press_event()
      .connect(sigc::mem_fun(*this,&SearchCombo2::popup_key_pr));
    Glib::wrap(GTK_WINDOW(GTK_COMBO_BOX(gobj())->priv->popup_window))->signal_key_release_event()
      .connect(sigc::mem_fun(*this,&SearchCombo2::popup_key_rel));
#endif
  }
  else
    mymodel->stop_if_running();
}

Gtk::SearchCombo2::~SearchCombo2()
{
}

sigc::signal0<void> &Gtk::SearchCombo2::signal_activate()
{ return activate;
}

sigc::signal2<void,gboolean *,GtkSCContext> &Gtk::SearchCombo2::signal_search()
{ return mymodel->search;
}

Glib::ustring Gtk::SearchCombo2::get_text() const
{ Glib::ustring res=get_entry()->get_text();
  DEBUG(printf("get_text(%s)\n",res.c_str()));
  return res;
}

Gtk::TreeModel::iterator Gtk::SearchCombo2::add_item(const Glib::ustring &text)
{ TreeModel::iterator i=mymodel->append();
  (*i)[m_text_columns.m_column]=text;
  DEBUG(printf("'%s' added\n",text.c_str()));
  return i;
}
