#ifndef TODO_GUI_H
#define TODO_GUI_H

#include "./variables.hh"
#include "./database_handler.hh"

void init_variables()
{
	builder->get_widget("main_window", main_window);
	openutils::exit_heap_fail(main_window);

	builder->get_widget("main_table", main_table);
	openutils::exit_heap_fail(main_table);

	builder->get_widget("add_date", add_date);
	openutils::exit_heap_fail(add_date);

	builder->get_widget("add_desc", add_desc);
	openutils::exit_heap_fail(add_desc);

	builder->get_widget("remove_ind", remove_ind);
	openutils::exit_heap_fail(remove_ind);

	builder->get_widget("remove_all", remove_all);
	openutils::exit_heap_fail(remove_all);

	builder->get_widget("edit_id", edit_id);
	openutils::exit_heap_fail(edit_id);

	builder->get_widget("edit_desc", edit_desc);
	openutils::exit_heap_fail(edit_desc);

	builder->get_widget("edit_date", edit_date);
	openutils::exit_heap_fail(edit_date);

	builder->get_widget("compt_id", compt_id);
	openutils::exit_heap_fail(compt_id);

	builder->get_widget("sort_order", sort_order);
	openutils::exit_heap_fail(sort_order);

	builder->get_widget("import_open", import_open);
	openutils::exit_heap_fail(import_open);

	builder->get_widget("export_open", export_open);
	openutils::exit_heap_fail(export_open);

	builder->get_widget("search_key", search_key);
	openutils::exit_heap_fail(search_key);

	builder->get_widget("search_table", search_table);
	openutils::exit_heap_fail(search_table);

	builder->get_widget("sort_select_col", sort_select_col);
	openutils::exit_heap_fail(sort_select_col);
	{
		sort_select_col->append("ID");
		sort_select_col->append("Description");
		sort_select_col->append("Valid Till");
		sort_select_col->append("Is Expired");
		sort_select_col->append("Is Completed");
		sort_select_col->set_active_text("ID");
	}

	builder->get_widget("remove_btn", remove_btn);
	openutils::exit_heap_fail(remove_btn);
	remove_btn->signal_clicked().connect([]()
										 { remove_task(); });

	builder->get_widget("add_btn", add_btn);
	openutils::exit_heap_fail(add_btn);
	add_btn->signal_clicked().connect([]()
									  { add_task(); });

	builder->get_widget("edit_btn", edit_btn);
	openutils::exit_heap_fail(edit_btn);
	edit_btn->signal_clicked().connect([]()
									   { edit_task(); });

	builder->get_widget("compt_btn", compt_btn);
	openutils::exit_heap_fail(compt_btn);
	compt_btn->signal_clicked().connect([]()
										{ complete_task(); });

	builder->get_widget("normal_btn", normal_btn);
	openutils::exit_heap_fail(normal_btn);
	normal_btn->signal_clicked().connect([]()
										 { normalize_task(); });

	builder->get_widget("sort_btn", sort_btn);
	openutils::exit_heap_fail(sort_btn);
	sort_btn->signal_clicked().connect([]()
									   { sort_task(); });

	builder->get_widget("export_btn", export_btn);
	openutils::exit_heap_fail(export_btn);
	export_btn->signal_clicked().connect([]()
										 { export_task(); });

	builder->get_widget("import_btn", import_btn);
	openutils::exit_heap_fail(import_btn);
	import_btn->signal_clicked().connect([]()
										 { import_task(); });

	search_key->signal_search_changed().connect([]()
											 { search_task(); });
}

void remove_variables()
{
	delete add_btn;
	delete add_desc;
	delete add_date;

	delete remove_ind;
	delete remove_all;
	delete remove_btn;

	delete edit_date;
	delete edit_btn;
	delete edit_id;
	delete edit_desc;

	delete compt_btn;
	delete compt_id;

	delete normal_btn;

	delete sort_btn;
	delete sort_order;
	delete sort_select_col;

	delete import_open;
	delete import_btn;

	delete export_open;
	delete export_btn;

	delete search_key;
	delete search_table;

	delete main_window;
}

#endif