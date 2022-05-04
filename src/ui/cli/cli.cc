#include "./entry.hh"

static inline openutils::vector_t<openutils::sstring> command_to_vector_t(const openutils::sstring &command, char *argv0)
{
	openutils::split_t spt = command.split(" ");
	openutils::vector_t<openutils::sstring> tokens = {argv0};
	for (std::size_t i = 0; i < spt.length();)
	{
		if (spt[i][0] == '\"')
		{
			openutils::sstring f1 = spt[i++] + " ";
			f1.remove_range(0, 1);
			while (i < spt.length() && spt[i][spt[i].end() - 1] != '\"')
				f1 += spt[i++] + " ";
			f1 += spt[i++];
			f1.remove_range(f1.end() - 1, f1.end());
			tokens.add(f1);
		}
		else
			tokens.add(spt[i++]);
	}
	return tokens;
}

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
			printf("/> ");
			command.in();
			command.remove_extra_char(' ');
			if (command.compare("exit") || command.compare("quit"))
				return EXIT_SUCCESS;
			openutils::vector_t<openutils::sstring> tokens = command_to_vector_t(command, argv[0]);
			entry_sstr(tokens.length(), tokens.raw_data());
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
		openutils::split_t spt= cfile.split("\n");
		for (std::size_t i = 0; i < spt.length(); i++)
		{
			std::cout << "/> " << spt[i] << openutils::sstring::end_line();
			openutils::vector_t<openutils::sstring> vec = command_to_vector_t(spt[i], argv[0]);
			entry_sstr(vec.length(), vec.raw_data());
		}
		return EXIT_SUCCESS;
	}
	else
		return entry(argc, argv);
	return EXIT_FAILURE;
}
