#include "SearchCombo3.h"
//#include <cassert>
#include <gtkmm/liststore.h>

static bool match(const Glib::ustring& s, const Gtk::TreeIter& iter)
{
  return true;
}

Gtk::SearchCombo3::~SearchCombo3()
{
  stop_search();
}

Glib::ustring Gtk::SearchCombo3::get_text() const
{
  return e.get_text();
}

Gtk::TreeModel::iterator Gtk::SearchCombo3::add_item(Glib::ustring const& t)
{
  Gtk::TreeModel::iterator i=completion_model->append();
  (*i)[mc.text]= t;
  return i;
}

void Gtk::SearchCombo3::popupdown()
{
//  if (e.get_child_visible())
  do_restart= true;
  e.grab_focus();
// trick around the fact that we need to open it by faking a key press but with different search mode
  block_change=true;
  g_signal_emit_by_name(e.gobj(), "changed");
  block_change=false;
  start_search();
}

bool Gtk::SearchCombo3::match_selected(const Gtk::TreeModel::iterator&it)
{
  // default handling:
  block_change=true;
  e.set_text((*it)[mc.text]);
  e.set_position(-1);
  block_change=false;
  do_restart=true;
  sig_activate();
  return true;
}

Gtk::SearchCombo3::SearchCombo3(bool _always_fill, bool _autoexpand, mycols *cols)
 : a(Gtk::ARROW_DOWN, Gtk::SHADOW_ETCHED_IN), ok_if_empty(), value_in_list(),
   always_fill(_always_fill), autoexpand(_autoexpand), autoexpand_on_activate(), auto_narrow(),
   search_in_progress(), do_restart(true), block_change()
{
  if (!cols) cols=&mc;
  ec= Gtk::EntryCompletion::create();
  e.set_completion(ec);
  ec->set_minimum_key_length(0);
  ec->set_match_func(sigc::ptr_fun(&match));
  completion_model = Gtk::ListStore::create(*cols);
  ec->set_model(completion_model);
  ec->set_text_column(0);
  pack_start(e);
  e.show();
  b.add(a);
  a.show();
  pack_start(b, Gtk::PackOptions(0));
  b.show();
  show();
  e.signal_changed().connect(sigc::mem_fun(*this,&SearchCombo3::on_entry_changed),false);
  e.signal_activate().connect(sigc::mem_fun(*this,&SearchCombo3::on_entry_activate),false);
  b.signal_clicked().connect(sigc::mem_fun(*this,&SearchCombo3::popupdown));
  ec->signal_match_selected().connect(sigc::mem_fun(*this,&SearchCombo3::match_selected),false);
  if (always_fill) g_signal_emit_by_name(e.gobj(), "changed");
}


void Gtk::SearchCombo3::set_always_fill(bool val)
{
 always_fill=val;
}


void Gtk::SearchCombo3::stop_search()
{

}

void Gtk::SearchCombo3::start_search()
{
  stop_search();
  completion_model->clear();
  gboolean cont=false;
  sig_search(&cont, do_restart ? GTK_SEARCH_REOPEN : GTK_SEARCH_OPEN);
  do_restart=false;
  while (cont)
  { cont=false;
    sig_search(&cont, GTK_SEARCH_FETCH);
  }
  sig_search(&cont, GTK_SEARCH_CLOSE);
}

void Gtk::SearchCombo3::on_entry_changed()
{
  if (block_change) return;
  do_restart=false;
  start_search();
  if(autoexpand && completion_model->children().size()==1)
    match_selected(completion_model->children().begin());
}

void Gtk::SearchCombo3::set_autoexpand(bool b) { autoexpand=b; }
guint Gtk::SearchCombo3::get_size() const { return completion_model->children().size(); }
void Gtk::SearchCombo3::set_text(Glib::ustring const& t) { block_change=true; e.set_text(t); block_change=false; }
void Gtk::SearchCombo3::reset() { do_restart=true; e.set_text(Glib::ustring()); }
void Gtk::SearchCombo3::set_start_on_idle(bool) { }
void Gtk::SearchCombo3::set_value_in_list(bool, bool) { }

void Gtk::SearchCombo3::on_entry_activate()
{
  if (completion_model->children().size()==1)
  {
    match_selected(completion_model->children().begin());
  }
  else
  {
    Glib::ustring text= e.get_text();
    for (Gtk::TreeModel::iterator i=completion_model->children().begin(); i!=completion_model->children().end(); ++i)
      if ((*i)[mc.text]==text)
      {
	match_selected(i);
	break;
      }
  }
}

Gtk::ListStore::const_iterator Gtk::SearchCombo3::begin() const { return completion_model->children().begin(); }
Gtk::ListStore::const_iterator Gtk::SearchCombo3::end() const { return completion_model->children().end(); }
