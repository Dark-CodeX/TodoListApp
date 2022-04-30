#include "./gui.hh"

int main(int argc, char **argv)
{
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
	builder = Gtk::Builder::create_from_string(ui_design_xml);

	init_variables();
	init_database();
	main_window->set_default_size(800, 600);
	app->run(*main_window);

	remove_variables();

	return EXIT_SUCCESS;
}