#ifndef TODO_GUI_VARIABLES
#define TODO_GUI_VARIABLES

#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/entry.h>
#include <gtkmm/calendar.h>
#include <gtkmm/builder.h>
#include <gtkmm/textview.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/filechooserbutton.h>
#include <gtkmm/searchentry.h>

#include "../../io/io.hh"
#include "../../date/date.hh"
#include "../../database/database.hh"

#pragma region VAR

Gtk::Window *main_window = nullptr;

Gtk::TextView *main_table = nullptr;

Gtk::Button *add_btn = nullptr;
Gtk::Entry *add_desc = nullptr;
Gtk::Calendar *add_date = nullptr;

Gtk::Entry *remove_ind = nullptr;
Gtk::CheckButton *remove_all = nullptr;
Gtk::Button *remove_btn = nullptr;

Gtk::Calendar *edit_date = nullptr;
Gtk::Button *edit_btn = nullptr;
Gtk::Entry *edit_id = nullptr;
Gtk::Entry *edit_desc = nullptr;

Gtk::Button *compt_btn = nullptr;
Gtk::Entry *compt_id = nullptr;

Gtk::Button *normal_btn = nullptr;

Gtk::Button *sort_btn = nullptr;
Gtk::ComboBoxText *sort_select_col= nullptr;
Gtk::CheckButton *sort_order = nullptr;

Gtk::FileChooserButton *import_open = nullptr;
Gtk::Button *import_btn = nullptr;

Gtk::FileChooserButton *export_open = nullptr;
Gtk::Button *export_btn = nullptr;

Gtk::SearchEntry *search_key = nullptr;
Gtk::TextView *search_table = nullptr;

todo::io IO;
todo::database base_db;

class Glib::RefPtr<Gtk::Builder> builder;

#pragma endregion VAR

#endif