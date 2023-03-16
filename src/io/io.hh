#ifndef TODO_IO_H
#define TODO_IO_H

#include <openutils/sstring/sstring.hh>
#include <openutils/map/map.hh>
#include <openutils/returns/optional.hh>
#include "../date/date.hh"
#include "../heap-pair/heap-pair.hh"
#include "../task/task.hh"
#include "../database/database.hh"

namespace todo
{
	class io
	{

	public:
		io();
		openutils::optional_t<openutils::sstring> open(const openutils::sstring &location) const;
		bool save(const openutils::map_t<openutils::sstring, task> &content, const openutils::sstring &location) const;
		const openutils::sstring get_home_dir() const;
		bool import_file(const openutils::sstring &loc_old, const openutils::sstring &loc_new) const;
		~io();
	};

	io::io() = default;

	openutils::optional_t<openutils::sstring> io::open(const openutils::sstring &location) const
	{
		std::FILE *f = std::fopen(location.c_str(), "rb");
		if (!f)
		{
			std::FILE *fp = std::fopen(location.c_str(), "wb+");
			if (!fp)
			{
				std::fprintf(stderr, "err: could not create file `%s`\n", location.c_str());
				std::exit(EXIT_FAILURE);
			}
			else
				std::fclose(fp);
		}
		else
			std::fclose(f);
		openutils::sstring x;
		if (!x.open(location.c_str()))
			return openutils::optnull;
		return x;
	}

	bool io::save(const openutils::map_t<openutils::sstring, task> &content, const openutils::sstring &location) const
	{
		openutils::sstring x;
		for (openutils::iter_map_t i = content.iterator(); i.c_loop(); i.next())
		{
			x.append("[");
			x.append(i->key.c_str());
			x.append("]:\n\t");
			x.append(i->value.get_description().c_str());
			x.append("\n\t\tDATE: ");
			x.append(i->value.get_date().to_string().c_str());
			x.append("\n\t\t\t");
			x.append(openutils::sstring::to_sstring(i->value.is_completed()).c_str());
			x.append("\n");
		}
		return x.save(location.c_str());
	}

	const openutils::sstring io::get_home_dir() const
	{
		openutils::sstring x;
#if defined _WIN32 || defined _WIN64 || defined __CYGWIN__
		x = std::getenv("HOME");
		if(x.empty())
		x = std::getenv("USERPROFILE");
#else
		x = std::getenv("HOME");
#endif
		if (x.empty())
		{
			std::fprintf(stderr, "err: could not obtain home path.\n");
			std::exit(EXIT_FAILURE);
		}
		return x;
	}

	bool io::import_file(const openutils::sstring &loc_old, const openutils::sstring &loc_new) const
	{
		openutils::sstring cont_n = openutils::sstring::open_file(loc_new);
		if (cont_n.empty())
		{
			std::fprintf(stderr, "err: given file is either binary or empty.\n");
			std::exit(EXIT_FAILURE);
		}
		database a;
		a.lexer(cont_n);
		return this->save(a.get(), loc_old);
	}

	io::~io() = default;
};

#endif