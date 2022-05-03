#include "./entry.hh"

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		if (openutils::sstring::to_sstring(argv[1]) == "--init")
		{
			openutils::sstring command;
			while (true)
			{
				printf("/> ");
				command.in();
				command.remove_extra_char(' ');
				if (command.compare("exit") || command.compare("quit"))
					return EXIT_SUCCESS;
				openutils::split_t spt = command.split(" ");
				openutils::vector_t<openutils::sstring> tokens = {argv[0]};
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
				entry_sstr(tokens.length(), tokens.raw_data());
			}
		}
	}
	return entry(argc, argv);
}
