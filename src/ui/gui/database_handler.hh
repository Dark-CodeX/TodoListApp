#ifndef TODO_GUI_DATABASE_HANDLER
#define TODO_GUI_DATABASE_HANDLER

#include "./variables.hh"
#include <iostream>

int msgbox(const Glib::ustring &message, const Glib::ustring &title)
{
	Gtk::MessageDialog dialog(message);
	dialog.set_title(title);
	dialog.set_default_response(Gtk::RESPONSE_YES);
	return dialog.run();
}

void refresh_main_table()
{
	openutils::sstring str = "";
	str.append_formatted(512, "%s\n", todo::center("Tasks", 131, '-').c_str());
	str.append_formatted(512, "| %s | %s | %s | %s | %s |\n", todo::center("ID", 9).c_str(), todo::center("Description", 51).c_str(), todo::center("Valid Till", 21).c_str(), todo::center("Is Expired", 17).c_str(), todo::center("Is Completed", 17).c_str());
	str.append_formatted(512, "-----------------------------------------------------------------------------------------------------------------------------------\n");
	for (openutils::iter_map_t i = base_db.get().iterator(); i.c_loop(); i.next())
	{
		if (i->value.is_completed() == false && i->value.is_expired() == true)
			str.append_formatted(512, "| %s | %s | %s | %s | %s |\n",
								 todo::center(i->key, 9).c_str(),
								 todo::center(i->value.get_description(), 51).c_str(),
								 todo::center(i->value.get_date().to_string() + " (" + openutils::sstring::to_sstring(i->value.get_date().days_between(todo::date())) + " DAYS)", 21).c_str(),
								 todo::center(openutils::sstring::to_sstring(i->value.is_expired()), 17).c_str(),
								 todo::center(openutils::sstring::to_sstring(i->value.is_completed()), 17).c_str());
		else if (i->value.is_completed() == false && i->value.is_expired() == false)
			str.append_formatted(512, "| %s | %s | %s | %s | %s |\n",
								 todo::center(i->key, 9).c_str(),
								 todo::center(i->value.get_description(), 51).c_str(),
								 todo::center(i->value.get_date().to_string() + " (" + openutils::sstring::to_sstring(i->value.get_date().days_between(todo::date())) + " DAYS)", 21).c_str(),
								 todo::center(openutils::sstring::to_sstring(i->value.is_expired()), 17).c_str(),
								 todo::center(openutils::sstring::to_sstring(i->value.is_completed()), 17).c_str());
		else if (i->value.is_completed() == true && i->value.is_expired() == false)
			str.append_formatted(512, "| %s | %s | %s | %s | %s |\n",
								 todo::center(i->key, 9).c_str(),
								 todo::center(i->value.get_description(), 51).c_str(),
								 todo::center(i->value.get_date().to_string() + " (" + openutils::sstring::to_sstring(i->value.get_date().days_between(todo::date())) + " DAYS)", 21).c_str(),
								 todo::center(openutils::sstring::to_sstring(i->value.is_expired()), 17).c_str(),
								 todo::center(openutils::sstring::to_sstring(i->value.is_completed()), 17).c_str());
		else if (i->value.is_completed() == true && i->value.is_expired() == true)
			str.append_formatted(512, "| %s | %s | %s | %s | %s |\n", todo::center(i->key, 9).c_str(),
								 todo::center(i->value.get_description(), 51).c_str(),
								 todo::center(i->value.get_date().to_string() + " (" + openutils::sstring::to_sstring(i->value.get_date().days_between(todo::date())) + " DAYS)", 21).c_str(),
								 todo::center(openutils::sstring::to_sstring(i->value.is_expired()), 17).c_str(),
								 todo::center(openutils::sstring::to_sstring(i->value.is_completed()), 17).c_str());
		str.append_formatted(512, "-----------------------------------------------------------------------------------------------------------------------------------\n");
	}
	ref->set_text(str.c_str());
	main_table->set_buffer(ref);
}

void init_database()
{
	openutils::optional_t<openutils::sstring> data = IO.open(IO.get_home_dir() + "/todo_data.dat");
	if (data.is_null())
	{
		std::cerr << "err: bad data" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	base_db.lexer(data.get());
	base_db.mark_active();

	refresh_main_table();
}

void save_database()
{
	if (base_db.is_changed())
		if (!IO.save(base_db.get(), IO.get_home_dir() + "/todo_data.dat"))
			msgbox("Could not save the database file at: `" + Glib::ustring(IO.get_home_dir().c_str()) + "/todo_data.dat`.", "Error: Saving File");
}

void remove_task()
{
	if (remove_all->get_active())
	{
		Gtk::MessageDialog dialog("Do you really want to remove all the tasks?", false, Gtk::MessageType::MESSAGE_INFO, Gtk::ButtonsType::BUTTONS_YES_NO, false);
		dialog.set_title("Remove Task");
		dialog.set_default_response(Gtk::ResponseType::RESPONSE_NO);
		int res = dialog.run();
		if (res == Gtk::RESPONSE_YES)
		{
			base_db.clear();
			save_database();
			refresh_main_table();
			return;
		}
		else
			return;
	}
	else
	{
		openutils::sstring ind = remove_ind->get_text().c_str();
		if (!ind.is_digit())
		{
			msgbox("Index should be a positive integer.", "Error: NAN");
			return;
		}
		if (!base_db.remove(ind))
		{
			msgbox("Could not remove the task at: `" + Glib::ustring(ind.c_str()) + "`.", "Error: Remove Failed");
			return;
		}
		save_database();
		refresh_main_table();
	}
}

void add_task()
{
	Glib::Date temp_date;
	add_date->get_date(temp_date);
	if (!base_db.add(todo::task(add_desc->get_text().c_str(), todo::date(temp_date.get_day(), temp_date.get_month(), temp_date.get_year()))))
	{
		msgbox("Task could not be added.", "Error: Add Failed");
		return;
	}
	save_database();
	refresh_main_table();
}

void edit_task()
{
	openutils::sstring ind = edit_id->get_text().c_str();
	if (!ind.is_digit())
	{
		msgbox("Index should be a positive integer.", "Error: NAN");
		return;
	}
	Glib::Date temp_date;
	edit_date->get_date(temp_date);
	if (!base_db.edit(ind, todo::task(edit_desc->get_text().c_str(), todo::date(temp_date.get_day(), temp_date.get_month(), temp_date.get_year()))))
	{
		msgbox("Task could not be edited.", "Error: Edit Failed");
		return;
	}
	save_database();
	refresh_main_table();
}

void complete_task()
{
	openutils::sstring ind = edit_id->get_text().c_str();
	if (!ind.is_digit())
	{
		msgbox("Index should be a positive integer.", "Error: NAN");
		return;
	}
	if (!base_db.completed(ind))
	{
		msgbox("Task could not be marked as completed.", "Error: Complete Failed");
		return;
	}
	save_database();
	refresh_main_table();
}

void normalize_task()
{
	base_db.normalize();
	save_database();
	refresh_main_table();
}

void sort_task()
{
	openutils::sstring order = ((sort_order->get_active()) ? "-a" : "-d");
	openutils::map_t<openutils::sstring, openutils::sstring> map = {{"ID", "id"}, {"Description", "desc"}, {"Valid Till", "date"}, {"Is Expired", "expired"}, {"Is Completed", "completed"}};
	base_db.sort(map[sort_select_col->get_active_text().c_str()], order);
	save_database();
	refresh_main_table();
}

void export_task()
{
	if (export_open->get_filename().empty())
	{
		msgbox("No file is selected.", "Error: Export Failed");
		return;
	}
	if (!IO.save(base_db.get(), export_open->get_filename().c_str()))
		msgbox("Could not write the contents to the file `" + export_open->get_filename() + "`.", "Error: Export Failed");
}

void import_task()
{
	if (import_open->get_filename().empty())
	{
		msgbox("No file is selected.", "Error: Import Failed");
		return;
	}
}

#endif