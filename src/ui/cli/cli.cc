#include "./entry.hh"

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		std::cerr << "err: no argument, use `--help` flag to see help." << std::endl;
		return EXIT_FAILURE;
	}
	else if (openutils::sstring::to_sstring(argv[1]) == "--init")
	{
		openutils::sstring command;
		while (true)
		{
			std::printf("/> ");
			std::fflush(stdout);
			command.in().remove_extra_char(' ').append_start(openutils::sstring(argv[0]) + " ");
			openutils::vector_t<openutils::sstring> tokens = command.to_argv();
			if (entry_sstr(tokens.length(), tokens.raw_data()) == -1)
				return EXIT_SUCCESS;
		}
	}
	else if (openutils::sstring::to_sstring(argv[1]) == "--open")
	{
		if (argc < 3)
		{
			std::cerr << "err: not enough arguments" << std::endl;
			return EXIT_FAILURE;
		}
		openutils::sstring cfile;
		if (!cfile.open(argv[2]))
		{
			std::cerr << "err: file `" << argv[2] << "` could not be opened." << std::endl;
			return EXIT_FAILURE;
		}
		openutils::vector_t<openutils::sstring> spt = cfile.split("\n");
		for (std::size_t i = 0; i < spt.length(); i++)
		{
			std::cout << "/> " << spt[i] << openutils::sstring::end_line();
			openutils::vector_t<openutils::sstring> vec = spt[i].append_start(openutils::sstring(argv[0]) + " ").to_argv();
			if (entry_sstr(vec.length(), vec.raw_data()) == -1)
				return EXIT_SUCCESS;
		}
		return EXIT_SUCCESS;
	}
	else
		return entry(argc, argv);
	return EXIT_FAILURE;
}
