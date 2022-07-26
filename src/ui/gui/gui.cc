#include "./gui.hh"

int main(int argc, char **argv)
{
	app_location = *argv;
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "com.tusharchaurasia.todogui");
	builder = Gtk::Builder::create_from_string(ui_design_xml);

	init_variables();
	init_database();
	main_window->set_default_size(1024, 800);
	main_window->maximize();

#if defined _WIN32 || defined _WIN64 || defined __CYGWIN__
	Glib::RefPtr<Gtk::Settings> settings = Gtk::Settings::get_default();
	settings->property_gtk_application_prefer_dark_theme().set_value(true);
	settings->property_gtk_font_name().set_value("JetBrains Mono SemiBold 12");
#endif

	app->run(*main_window);

	remove_variables();

	return EXIT_SUCCESS;
}