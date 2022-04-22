#pragma once

#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <openutils/sstring/sstring.hh>

namespace todo
{
	class date
	{
	private:
		unsigned int year, month, day;
		bool is_leap(const unsigned int &y) const;
		const unsigned int month_day_cnt[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	public:
		date();
		date(const date &dt);
		date(date &&dt);
		date(const unsigned int &day_, const unsigned int &month_, const unsigned int &year_);
		date(const openutils::sstring &str);
		signed long long int days_between(const date &dt) const;
		unsigned int days_beginning(void) const;
		void add(const date &dt);
		void add(const signed long long int &skip_days);
		void substract(const date &dt);
		void substract(const signed long long int &skip_days);
		bool is_leap(void) const;
		date get_ctime(void) const;
		openutils::sstring to_string() const;
		date operator+(const date &dt);
		date operator+(const signed long long int &skip_days);
		date operator-(const date &dt);
		date operator-(const signed long long int &skip_days);
		void operator+=(const date &dt);
		void operator+=(const signed long long int &skip_days);
		void operator-=(const date &dt);
		void operator-=(const signed long long int &skip_days);
		void operator=(const date &dt);
		void operator=(date &&dt);
		bool operator>(const date &dt) const;
		bool operator<(const date &dt) const;
		bool operator>=(const date &dt) const;
		bool operator<=(const date &dt) const;
		bool operator==(const date &dt) const;
		bool operator!=(const date &dt) const;
		~date();
	};

	bool date::is_leap(const unsigned int &y) const
	{
		if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)
			return true;
		return false;
	}

	date::date()
	{
		std::time_t t = std::time(nullptr);
		struct std::tm *ct = std::localtime(&t);

		this->year = ct->tm_year + 1900;
		this->month = ct->tm_mon + 1;
		this->day = ct->tm_mday;
	}

	date::date(const date &dt)
	{
		this->year = dt.year;
		this->month = dt.month;
		this->day = dt.day;
	}

	date::date(date &&dt)
	{
		this->year = dt.year;
		this->month = dt.month;
		this->day = dt.day;
	}

	date::date(const unsigned int &day_, const unsigned int &month_, const unsigned int &year_)
	{
		if (!this->is_leap(year_) && month_ == 2)
		{
			if (day_ >= 29)
			{
				std::fprintf(stderr, "err: %i is greater than or equal to 29 in the February month of a non-leap year (%i).\n", day_, year_);
				std::exit(EXIT_FAILURE);
			}
		}
		if (day_ > 31)
		{
			std::fprintf(stderr, "err: %i is a day and should not be greater than 31.\n", day_);
			std::exit(EXIT_FAILURE);
		}
		this->day = day_;
		if (month_ > 12)
		{
			std::fprintf(stderr, "err: %i is a month and should not be greater than 12.\n", month_);
			std::exit(EXIT_FAILURE);
		}
		this->month = month_;
		if (year_ < 1000 || year_ > 9999)
		{
			std::fprintf(stderr, "err: %i is a year and should be in-between 1000 and 9999.\n", year_);
			std::exit(EXIT_FAILURE);
		}
		this->year = year_;
	}

	date::date(const openutils::sstring &str)
	{
		unsigned int m = 0, d = 0, y = 0;
		openutils::parse_t parse = str.parse();
		std::size_t n = 0;
		while (parse.get_type(n) != openutils::parse_token::NULL_END)
		{
			if (parse.get_type(n) == openutils::parse_token::INTEGER && n == 0)
			{
				d = std::strtoull(parse[n].c_str(), nullptr, 10);
				n++;
			}
			else
			{
				std::fprintf(stderr, "err: `%s` in `%s` should be a day (integer).\n", parse[n].c_str(), str.c_str());
				std::exit(EXIT_FAILURE);
			}
			if (parse.get_type(n) != openutils::parse_token::SPECIAL_CHAR && n == 1)
			{
				std::fprintf(stderr, "err: `%s` in `%s` should be a separator between day and month.\n", parse[n].c_str(), str.c_str());
				std::exit(EXIT_FAILURE);
			}
			else
				n++;
			if (parse.get_type(n) == openutils::parse_token::INTEGER && n == 2)
			{
				m = std::strtoull(parse[n].c_str(), nullptr, 10);
				n++;
			}
			else
			{
				std::fprintf(stderr, "err: `%s` in `%s` should be a month (integer).\n", parse[n].c_str(), str.c_str());
				std::exit(EXIT_FAILURE);
			}
			if (parse.get_type(n) != openutils::parse_token::SPECIAL_CHAR && n == 3)
			{
				std::fprintf(stderr, "err: `%s` in `%s` should be a separator between month and year.\n", parse[n].c_str(), str.c_str());
				std::exit(EXIT_FAILURE);
			}
			else
				n++;
			if (parse.get_type(n) == openutils::parse_token::INTEGER && n == 4)
			{
				y = std::strtoull(parse[n].c_str(), nullptr, 10);
				n++;
			}
			else
			{
				std::fprintf(stderr, "err: `%s` in `%s` should be a year (integer).\n", parse[n].c_str(), str.c_str());
				std::exit(EXIT_FAILURE);
			}
			if (parse.length() != n + 1)
			{
				std::fprintf(stderr, "err: `%s` in `%s` is exceeding the date format (DD/MM/YYYY).\n", parse[n].c_str(), str.c_str());
				std::exit(EXIT_FAILURE);
			}
		}
		*this = date(d, m, y);
	}

	signed long long int date::days_between(const date &dt) const
	{
		signed long long int n1 = this->year * 365 + this->day;
		for (unsigned int i = 0; i < this->month - 1; i++)
			n1 += this->month_day_cnt[i];

		unsigned int yrs = this->year;
		if (this->month <= 2)
			yrs--;
		n1 += (yrs / 4) - (yrs / 100) + (yrs / 400);

		signed long long int n2 = dt.year * 365 + dt.day;
		for (unsigned int i = 0; i < dt.month - 1; i++)
			n2 += dt.month_day_cnt[i];

		unsigned int yrs2 = dt.year;
		if (dt.month <= 2)
			yrs2--;
		n2 += (yrs2 / 4) - (yrs2 / 100) + (yrs2 / 400);

		return (n1 - n2);
	}

	unsigned int date::days_beginning(void) const
	{
		unsigned int os = this->day;
		switch (this->month - 1)
		{
		case 11:
			os += 30;
			break;
		case 10:
			os += 31;
			break;
		case 9:
			os += 30;
			break;
		case 8:
			os += 31;
			break;
		case 7:
			os += 31;
			break;
		case 6:
			os += 30;
			break;
		case 5:
			os += 31;
			break;
		case 4:
			os += 30;
			break;
		case 3:
			os += 31;
			break;
		case 2:
			os += 28;
			break;
		case 1:
			os += 31;
			break;
		}
		if (this->is_leap(this->year) && this->month > 2)
			os += 1;
		return os;
	}

	void date::add(const date &dt)
	{
		unsigned long long int days_bw = this->days_between(dt);
		std::tm ti = {};
		ti.tm_year = this->year - 1900;
		ti.tm_mon = this->month - 1;
		ti.tm_mday = this->day;
		ti.tm_mday += days_bw;
		std::mktime(&ti);

		this->year = ti.tm_year + 1900;
		this->month = ti.tm_mon + 1;
		this->day = ti.tm_mday;
	}

	void date::add(const signed long long int &skip_days)
	{
		std::tm ti = {};
		ti.tm_year = this->year - 1900;
		ti.tm_mon = this->month - 1;
		ti.tm_mday = this->day;
		ti.tm_mday += skip_days;
		std::mktime(&ti);

		this->year = ti.tm_year + 1900;
		this->month = ti.tm_mon + 1;
		this->day = ti.tm_mday;
	}

	void date::substract(const date &dt)
	{
		unsigned long long int days_bw = this->days_between(dt);
		std::tm ti = {};
		ti.tm_year = this->year - 1900;
		ti.tm_mon = this->month - 1;
		ti.tm_mday = this->day;
		ti.tm_mday -= days_bw;
		std::mktime(&ti);

		this->year = ti.tm_year + 1900;
		this->month = ti.tm_mon + 1;
		this->day = ti.tm_mday;
	}

	void date::substract(const signed long long int &skip_days)
	{
		std::tm ti = {};
		ti.tm_year = this->year - 1900;
		ti.tm_mon = this->month - 1;
		ti.tm_mday = this->day;
		ti.tm_mday -= skip_days;
		std::mktime(&ti);

		this->year = ti.tm_year + 1900;
		this->month = ti.tm_mon + 1;
		this->day = ti.tm_mday;
	}

	bool date::is_leap(void) const
	{
		return this->is_leap(this->year);
	}

	date date::get_ctime(void) const
	{
		date x = date();
		return x;
	}

	openutils::sstring date::to_string() const
	{
		openutils::sstring x;
		x.set_formatted(1024, "%i/%i/%i", this->day, this->month, this->year);
		return x;
	}

	date date::operator+(const date &dt)
	{
		date d = date(*this);
		d.add(dt);
		return d;
	}

	date date::operator+(const signed long long int &skip_days)
	{
		date d = date(*this);
		d.add(skip_days);
		return d;
	}

	date date::operator-(const date &dt)
	{
		date d = date(*this);
		d.substract(dt);
		return d;
	}

	date date::operator-(const signed long long int &skip_days)
	{
		date d = date(*this);
		d.substract(skip_days);
		return d;
	}

	void date::operator+=(const date &dt)
	{
		this->add(dt);
	}

	void date::operator+=(const signed long long int &skip_days)
	{
		this->add(skip_days);
	}

	void date::operator-=(const date &dt)
	{
		this->substract(dt);
	}

	void date::operator-=(const signed long long int &skip_days)
	{
		this->substract(skip_days);
	}

	void date::operator=(const date &dt)
	{
		this->year = dt.year;
		this->month = dt.month;
		this->day = dt.day;
	}

	void date::operator=(date &&dt)
	{
		this->year = dt.year;
		this->month = dt.month;
		this->day = dt.day;
	}

	bool date::operator>(const date &dt) const
	{
		if (this->year > dt.year)
			return true;
		else if (this->year < dt.year)
			return false;
		else
		{
			if (this->month > dt.month)
				return true;
			else if (this->month < dt.month)
				return false;
			else
			{
				if (this->day > dt.day)
					return true;
				else if (this->day < dt.day)
					return false;
				else
					return false;
			}
		}
	}

	bool date::operator<(const date &dt) const
	{
		if (this->year > dt.year)
			return false;
		else if (this->year < dt.year)
			return true;
		else
		{
			if (this->month > dt.month)
				return false;
			else if (this->month < dt.month)
				return true;
			else
			{
				if (this->day > dt.day)
					return false;
				else if (this->day < dt.day)
					return true;
				else
					return false;
			}
		}
	}

	bool date::operator>=(const date &dt) const
	{
		if (this->year > dt.year)
			return true;
		else if (this->year < dt.year)
			return false;
		else
		{
			if (this->month > dt.month)
				return true;
			else if (this->month < dt.month)
				return false;
			else
			{
				if (this->day > dt.day)
					return true;
				else if (this->day < dt.day)
					return false;
				else
					return true;
			}
		}
	}
	bool date::operator<=(const date &dt) const
	{
		if (this->year > dt.year)
			return false;
		else if (this->year < dt.year)
			return true;
		else
		{
			if (this->month > dt.month)
				return false;
			else if (this->month < dt.month)
				return true;
			else
			{
				if (this->day > dt.day)
					return false;
				else if (this->day < dt.day)
					return true;
				else
					return true;
			}
		}
	}

	bool date::operator==(const date &dt) const
	{
		return ((this->year == dt.year) && (this->month == dt.month) && (this->day == dt.day));
	}

	bool date::operator!=(const date &dt) const
	{
		return ((this->year != dt.year) && (this->month != dt.month) && (this->day != dt.day));
	}

	date::~date() = default;
};