#ifndef TODO_DATABASE_H
#define TODO_DATABASE_H

#include "../io/io.hh"
#include "../date/date.hh"
#include "../heap-pair/heap-pair.hh"
#include "../task/task.hh"
#include <openutils/map/map.hh>
#include <openutils/vector/vector.hh>

namespace todo
{
	static const openutils::sstring center(const openutils::sstring &str, const std::size_t &width, const char &padding = ' ')
	{
		openutils::sstring x;
		if (str.end() == 0)
		{
			for (std::size_t i = 0; i < width; i++)
				x += padding;
			return x;
		}
		if (str.end() > width)
		{
			for (std::size_t i = 0; i < width - 3; i++)
				x += str[i];
			x += "...";
			return x;
		}
		bool start_appending = false;
		for (std::size_t i = 0, a = 0; i < width; i++)
		{
			if (((width / 2) - (str.end() / 2) == i) || start_appending == true)
			{
				x += str[a++];
				start_appending = true;
				if (str.end() == a)
					start_appending = false;
			}
			else
				x += padding;
		}
		return x;
	}
	class database
	{
	private:
		openutils::map_t<openutils::sstring, task> delta;
		std::size_t last_index;
		bool is_db_changed;

	public:
		database();
		void lexer(const openutils::sstring &txt);
		const openutils::map_t<openutils::sstring, task> &get() const;

		void mark_active();
		bool add(const task &tsk);
		std::size_t get_last_index() const;

		bool remove(const openutils::sstring &ind);
		bool edit(const openutils::sstring &ind, const task &new_);
		bool contains(const openutils::sstring &ind) const;
		bool completed(const openutils::sstring &ind);

		openutils::optional_t<openutils::vector_t<heap_pair<todo::heap_pair<openutils::sstring, todo::task>, double>>> search(const openutils::sstring &keyword) const;
		bool sort(const openutils::sstring &col, const openutils::sstring &order);
		void normalize();
		void clear();
		bool is_changed() const;
		void log() const;
		~database();
	};

	database::database() = default;

	void database::lexer(const openutils::sstring &txt)
	{
		openutils::vector_t<openutils::sstring> inds, dates, descs;
		openutils::vector_t<bool> compts;
		openutils::split_t st = txt.split("\n");
		for (std::size_t i = 0; i < st.length(); i += 4)
		{
			openutils::parse_t pt = st[i].parse();
			std::size_t n = 0;
			while (pt.get_type(n) != openutils::parse_token::NULL_END)
			{
				if (pt.get_type(n) == openutils::parse_token::SPECIAL_CHAR && n == 0)
				{
					if (pt[n] != "[")
					{
						std::fprintf(stderr, "err: `%s` in `%s` should be `[`.\n", pt[n].c_str(), st[i].c_str());
						std::exit(EXIT_FAILURE);
					}
					n++;
					if (pt.get_type(n) == openutils::parse_token::INTEGER)
					{
						inds.add(pt[n]);
					}
					else
					{
						std::fprintf(stderr, "err: `%s` in `%s` should be an integer.\n", pt[n].c_str(), st[i].c_str());
						std::exit(EXIT_FAILURE);
					}
					n++;
					if (pt.get_type(n) != openutils::parse_token::SPECIAL_CHAR && n == 2)
					{
						std::fprintf(stderr, "err: `%s` in `%s` should be `]`.\n", pt[n].c_str(), st[i].c_str());
						std::exit(EXIT_FAILURE);
					}
					n++;
					if (pt.get_type(n) != openutils::parse_token::SPECIAL_CHAR && n == 3)
					{
						std::fprintf(stderr, "err: `%s` in `%s` should be `:`.\n", pt[n].c_str(), st[i].c_str());
						std::exit(EXIT_FAILURE);
					}
					n++;
				}
				else
				{
					std::fprintf(stderr, "err: `%s` in `%s` should be `[`.\n", pt[n].c_str(), st[i].c_str());
					std::exit(EXIT_FAILURE);
				}
			}
		}
		if (inds.length() != 0)
			this->last_index = std::strtoull(inds[inds.length() - 1].c_str(), nullptr, 10);
		else
			this->last_index = 0;

		for (std::size_t i = 1; i < st.length(); i += 4)
		{
			openutils::parse_t pt = st[i].parse();
			std::size_t n = 0;
			while (pt.get_type(n) != openutils::parse_token::NULL_END)
			{
				if (pt.get_type(n) == openutils::parse_token::ESC_SEQ && n == 0)
				{
					if (pt[n] != "\t")
					{
						std::fprintf(stderr, "err: `%s` in `%s` should be a `TAB`.\n", pt[n].c_str(), st[i].c_str());
						std::exit(EXIT_FAILURE);
					}
					openutils::sstring temp_desc;
					n++;
					while (pt.get_type(n) != openutils::parse_token::NULL_END)
					{
						temp_desc.append(pt[n].c_str());
						n++;
					}
					descs.add(temp_desc);
				}
				else
				{
					std::fprintf(stderr, "err: `%s` in `%s` should be a `TAB`.\n", pt[n].c_str(), st[i].c_str());
					std::exit(EXIT_FAILURE);
				}
			}
		}

		for (std::size_t i = 2; i < st.length(); i += 4)
		{
			openutils::parse_t pt = st[i].parse();
			std::size_t n = 0;
			while (pt.get_type(n) != openutils::parse_token::NULL_END)
			{
				if (pt.get_type(n) == openutils::parse_token::ESC_SEQ && n == 0)
				{
					if (pt[n] != "\t")
					{
						std::fprintf(stderr, "err: `%s` in `%s` should be a `TAB`.\n", pt[n].c_str(), st[i].c_str());
						std::exit(EXIT_FAILURE);
					}
					openutils::sstring temp_date;
					n++;
					if (pt[n] != "\t")
					{
						std::fprintf(stderr, "err: `%s` in `%s` should be a `TAB`.\n", pt[n].c_str(), st[i].c_str());
						std::exit(EXIT_FAILURE);
					}
					n++;
					if (pt.get_type(n) != openutils::parse_token::WORD || pt[n] != "DATE")
					{
						std::fprintf(stderr, "err: `%s` in `%s` should be a `DATE`.\n", pt[n].c_str(), st[i].c_str());
						std::exit(EXIT_FAILURE);
					}
					n++;
					if (pt.get_type(n) != openutils::parse_token::SPECIAL_CHAR || pt[n] != ":")
					{
						std::fprintf(stderr, "err: `%s` in `%s` should be a `:`.\n", pt[n].c_str(), st[i].c_str());
						std::exit(EXIT_FAILURE);
					}
					n++;
					if (pt.get_type(n) != openutils::parse_token::WHITESPACE || pt[n] != " ")
					{
						std::fprintf(stderr, "err: `%s` in `%s` should be a `WHITESPACE`.\n", pt[n].c_str(), st[i].c_str());
						std::exit(EXIT_FAILURE);
					}
					n++;
					while (pt.get_type(n) != openutils::parse_token::NULL_END)
					{
						temp_date.append(pt[n].c_str());
						n++;
					}
					dates.add(temp_date);
				}
				else
				{
					std::fprintf(stderr, "err: `%s` in `%s` should be a `TAB`.\n", pt[n].c_str(), st[i].c_str());
					std::exit(EXIT_FAILURE);
				}
			}
		}

		for (std::size_t i = 3; i < st.length(); i += 4)
		{
			openutils::parse_t pt = st[i].parse();
			std::size_t n = 0;
			while (pt.get_type(n) != openutils::parse_token::NULL_END)
			{
				if (pt.get_type(n) == openutils::parse_token::ESC_SEQ && n == 0)
				{
					if (pt[n] != "\t")
					{
						std::fprintf(stderr, "err: `%s` in `%s` should be a `TAB`.\n", pt[n].c_str(), st[i].c_str());
						std::exit(EXIT_FAILURE);
					}
					n++;
					if (pt[n] != "\t")
					{
						std::fprintf(stderr, "err: `%s` in `%s` should be a `TAB`.\n", pt[n].c_str(), st[i].c_str());
						std::exit(EXIT_FAILURE);
					}
					n++;
					if (pt[n] != "\t")
					{
						std::fprintf(stderr, "err: `%s` in `%s` should be a `TAB`.\n", pt[n].c_str(), st[i].c_str());
						std::exit(EXIT_FAILURE);
					}
					n++;
					if (pt.get_type(n) != openutils::parse_token::WORD)
					{
						std::fprintf(stderr, "err: `%s` in `%s` should be a `false` or `true`.\n", pt[n].c_str(), st[i].c_str());
						std::exit(EXIT_FAILURE);
					}
					else
					{
						if (pt[n] == "true")
							compts.add(true);
						else if (pt[n] == "false")
							compts.add(false);
						else
						{
							std::fprintf(stderr, "err: `%s` in `%s` should be a `false` or `true`.\n", pt[n].c_str(), st[i].c_str());
							std::exit(EXIT_FAILURE);
						}
						n++;
					}
				}
				else
				{
					std::fprintf(stderr, "err: `%s` in `%s` should be a `TAB`.\n", pt[n].c_str(), st[i].c_str());
					std::exit(EXIT_FAILURE);
				}
			}
		}

		for (openutils::iter_vector_t i = inds.iterator(); i.c_loop(); i.next())
		{
			if (!this->delta.add(inds[i.index()], task(descs[i.index()], date(dates[i.index()]), compts[i.index()])))
			{
				std::fprintf(stderr, "err: could not add the data [`%s`, `%s`, `%s`] at index `%s`.\n", descs[i.index()].c_str(), dates[i.index()].c_str(), openutils::sstring::to_sstring(compts[i.index()]).c_str(), inds[i.index()].c_str());
				std::exit(EXIT_FAILURE);
			}
		}
		this->is_db_changed = false;
	}

	const openutils::map_t<openutils::sstring, task> &database::get() const
	{
		return this->delta;
	}

	std::size_t database::get_last_index() const
	{
		return this->last_index;
	}

	void database::mark_active()
	{
		for (openutils::iter_map_t i = this->delta.iterator(); i.c_loop(); i.next())
			i->value.mark_expired();
	}

	bool database::add(const task &tsk)
	{
		if (this->delta.add(openutils::sstring::to_sstring(this->last_index + 1), tsk))
		{
			this->is_db_changed = true;
			this->last_index++;
			this->mark_active();
			return true;
		}
		return false;
	}

	bool database::remove(const openutils::sstring &ind)
	{
		if (this->delta.remove(ind))
		{
			this->is_db_changed = true;
			this->mark_active();
			return true;
		}
		return false;
	}

	bool database::edit(const openutils::sstring &ind, const task &new_)
	{
		if (!this->delta.contains(ind))
			return false;
		this->delta[ind] = new_;
		this->mark_active();
		this->is_db_changed = true;
		return true;
	}

	bool database::contains(const openutils::sstring &ind) const
	{
		return this->delta.contains(ind);
	}

	bool database::completed(const openutils::sstring &ind)
	{
		if (!this->delta.contains(ind))
			return false;
		this->delta[ind].mark_completed(true);
		this->is_db_changed = true;
		return true;
	}

	void database::clear()
	{
		this->delta.erase();
		this->is_db_changed = true;
	}

	openutils::optional_t<openutils::vector_t<heap_pair<todo::heap_pair<openutils::sstring, todo::task>, double>>> database::search(const openutils::sstring &kword) const
	{
		openutils::vector_t<heap_pair<todo::heap_pair<openutils::sstring, todo::task>, double>> val;
		openutils::sstring key_ = kword;
		key_.to_lower();
		const char *keyword = key_.c_str();
		for (openutils::map_t<openutils::sstring, task>::iter i = this->delta.iterator(); i.c_loop(); i.next())
		{
			openutils::sstring temp_date = i->value.get_date().to_string(), temp_desc = i->value.get_description();
			temp_desc.to_lower();
			if ((temp_date.soundex() == key_.soundex() || temp_date.contains(keyword) || temp_date.starts_with(keyword) || temp_date.ends_with(keyword)) && (temp_desc.soundex() == key_.soundex() || temp_desc.contains(keyword) || temp_desc.starts_with(keyword) || temp_desc.ends_with(keyword)))
				val.add({{i->key, i->value},
						 2 * ((temp_desc.percentage_matched(keyword) +
							   temp_desc.edit_distance(keyword)) /
							  2.0) +
							 ((temp_date.percentage_matched(keyword) +
							   temp_date.edit_distance(keyword)) /
							  2.0)});
			else if (temp_desc.soundex() == key_.soundex() || temp_desc.contains(keyword) || temp_desc.starts_with(keyword) || temp_desc.ends_with(keyword))
				val.add({{i->key, i->value},
						 ((temp_desc.percentage_matched(keyword) +
						   temp_desc.edit_distance(keyword)))});
			else if (temp_date.soundex() == key_.soundex() || temp_date.contains(keyword) || temp_date.starts_with(keyword) || temp_date.ends_with(keyword))
				val.add({{i->key, i->value},
						 ((temp_date.percentage_matched(keyword) +
						   temp_date.edit_distance(keyword)))});
			else
				continue;
		}
		val.sort([](heap_pair<todo::heap_pair<openutils::sstring, todo::task>, double> a, heap_pair<todo::heap_pair<openutils::sstring, todo::task>, double> b)
				 { return a.second() > b.second(); });
		return val;
	}

	bool database::sort(const openutils::sstring &col, const openutils::sstring &order)
	{
		if (col == "id")
		{
			if (order == "-a")
				this->delta.sort_keys([](openutils::sstring a, openutils::sstring b)
									  {std::size_t x = std::strtoul(a.c_str(), nullptr, 10); std::size_t y = std::strtoul(b.c_str(), nullptr, 10); return x<y; });
			else
				this->delta.sort_keys([](openutils::sstring a, openutils::sstring b)
									  {std::size_t x = std::strtoul(a.c_str(), nullptr, 10); std::size_t y = std::strtoul(b.c_str(), nullptr, 10); return x>y; });
			this->is_db_changed = true;
			return true;
		}
		if (col == "desc")
		{
			if (order == "-a")
				this->delta.sort_values([](openutils::node_t<openutils::sstring, task> a, openutils::node_t<openutils::sstring, task> b)
										{ return a.value.get_description() < b.value.get_description(); });
			else
				this->delta.sort_values([](openutils::node_t<openutils::sstring, task> a, openutils::node_t<openutils::sstring, task> b)
										{ return a.value.get_description() > b.value.get_description(); });
			this->is_db_changed = true;
			return true;
		}
		if (col == "date")
		{
			if (order == "-a")
				this->delta.sort_values([](openutils::node_t<openutils::sstring, task> a, openutils::node_t<openutils::sstring, task> b)
										{ return a.value.get_date() < b.value.get_date(); });
			else
				this->delta.sort_values([](openutils::node_t<openutils::sstring, task> a, openutils::node_t<openutils::sstring, task> b)
										{ return a.value.get_date() > b.value.get_date(); });
			this->is_db_changed = true;
			return true;
		}
		if (col == "expired")
		{
			if (order == "-a")
				this->delta.sort_values([](openutils::node_t<openutils::sstring, task> a, openutils::node_t<openutils::sstring, task> b)
										{ return a.value.is_expired() < b.value.is_expired(); });
			else
				this->delta.sort_values([](openutils::node_t<openutils::sstring, task> a, openutils::node_t<openutils::sstring, task> b)
										{ return a.value.is_expired() > b.value.is_expired(); });
			this->is_db_changed = true;
			return true;
		}
		if (col == "completed")
		{
			if (order == "-a")
				this->delta.sort_values([](openutils::node_t<openutils::sstring, task> a, openutils::node_t<openutils::sstring, task> b)
										{ return a.value.is_completed() < b.value.is_completed(); });
			else
				this->delta.sort_values([](openutils::node_t<openutils::sstring, task> a, openutils::node_t<openutils::sstring, task> b)
										{ return a.value.is_completed() > b.value.is_completed(); });
			this->is_db_changed = true;
			return true;
		}
		else
			return false;
	}

	void database::normalize()
	{
		openutils::vector_t<heap_pair<openutils::sstring, task>> temp;
		for (openutils::iter_map_t i = this->delta.iterator(); i.c_loop(); i.next())
			temp.add({i->key, i->value});
		this->delta.erase();
		std::size_t nos = 1;
		for (openutils::vector_t<heap_pair<openutils::sstring, task>>::iter i = temp.iterator(); i.c_loop(); i.next())
			this->delta.add(openutils::sstring::to_sstring(nos++), (*i).second());
		this->is_db_changed = true;
	}

	bool database::is_changed() const
	{
		return this->is_db_changed;
	}

	void database::log() const
	{
		std::printf("%s\n", center("Tasks", 131, '-').c_str());
		std::printf("| \u001b[34;1m%s\u001b[0m | \u001b[34;1m%s\u001b[0m | \u001b[34;1m%s\u001b[0m | \u001b[34;1m%s\u001b[0m | \u001b[34;1m%s\u001b[0m |\n", center("ID", 9).c_str(), center("Description", 51).c_str(), center("Valid Till", 21).c_str(), center("Is Expired", 17).c_str(), center("Is Completed", 17).c_str());
		std::printf("-----------------------------------------------------------------------------------------------------------------------------------\n");
		for (openutils::iter_map_t i = this->delta.iterator(); i.c_loop(); i.next())
		{
			if (i->value.is_completed() == false && i->value.is_expired() == true)
				std::printf("| \u001b[31;1m%s\u001b[0m | \u001b[31;1m%s\u001b[0m | \u001b[31;1m%s\u001b[0m | \u001b[31;1m%s\u001b[0m | \u001b[31;1m%s\u001b[0m |\n",
							center(i->key, 9).c_str(),
							center(i->value.get_description(), 51).c_str(),
							center(i->value.get_date().to_string() + " (" + openutils::sstring::to_sstring(i->value.get_date().days_between(date())) + " DAYS)", 21).c_str(),
							center(openutils::sstring::to_sstring(i->value.is_expired()), 17).c_str(),
							center(openutils::sstring::to_sstring(i->value.is_completed()), 17).c_str());
			else if (i->value.is_completed() == false && i->value.is_expired() == false)
				std::printf("| \u001b[33;1m%s\u001b[0m | \u001b[33;1m%s\u001b[0m | \u001b[33;1m%s\u001b[0m | \u001b[33;1m%s\u001b[0m | \u001b[33;1m%s\u001b[0m |\n",
							center(i->key, 9).c_str(),
							center(i->value.get_description(), 51).c_str(),
							center(i->value.get_date().to_string() + " (" + openutils::sstring::to_sstring(i->value.get_date().days_between(date())) + " DAYS)", 21).c_str(),
							center(openutils::sstring::to_sstring(i->value.is_expired()), 17).c_str(),
							center(openutils::sstring::to_sstring(i->value.is_completed()), 17).c_str());
			else if (i->value.is_completed() == true && i->value.is_expired() == false)
				std::printf("| \u001b[32;1m%s\u001b[0m | \u001b[32;1m%s\u001b[0m | \u001b[32;1m%s\u001b[0m | \u001b[32;1m%s\u001b[0m | \u001b[32;1m%s\u001b[0m |\n",
							center(i->key, 9).c_str(),
							center(i->value.get_description(), 51).c_str(),
							center(i->value.get_date().to_string() + " (" + openutils::sstring::to_sstring(i->value.get_date().days_between(date())) + " DAYS)", 21).c_str(),
							center(openutils::sstring::to_sstring(i->value.is_expired()), 17).c_str(),
							center(openutils::sstring::to_sstring(i->value.is_completed()), 17).c_str());
			else if (i->value.is_completed() == true && i->value.is_expired() == true)
				std::printf("| %s | %s | %s | %s | %s |\n", center(i->key, 9).c_str(),
							center(i->value.get_description(), 51).c_str(),
							center(i->value.get_date().to_string() + " (" + openutils::sstring::to_sstring(i->value.get_date().days_between(date())) + " DAYS)", 21).c_str(),
							center(openutils::sstring::to_sstring(i->value.is_expired()), 17).c_str(),
							center(openutils::sstring::to_sstring(i->value.is_completed()), 17).c_str());
			std::printf("-----------------------------------------------------------------------------------------------------------------------------------\n");
		}
	}

	database::~database() = default;
};

#endif