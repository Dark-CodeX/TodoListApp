#ifndef TODO_TAKS_H
#define TODO_TAKS_H

#include "../date/date.hh"
#include <openutils/sstring/sstring.hh>
#include "../heap-pair/heap-pair.hh"

namespace todo
{
	class task
	{
	private:
		heap_pair<openutils::sstring, date> __task;
		bool expired = false;
		bool completed = false;

	public:
		task();
		task(const openutils::sstring &desc, const date &dt, const bool &compt);
		task(const openutils::sstring &desc, const date &dt);
		task(openutils::sstring &&desc, date &&dt);
		task(const task &t);
		task(task &&t);

		void mark_expired();
		bool is_expired() const;

		void mark_completed(bool compt);
		bool is_completed() const;

		const openutils::sstring &get_description() const;
		const date &get_date() const;

		void operator=(const task &t);
		void operator=(task &&t);
		~task();
	};

	task::task() = default;

	task::task(const openutils::sstring &desc, const date &dt, const bool &compt)
	{
		this->__task = heap_pair(desc, dt);
		this->completed = compt;
	}

	task::task(const openutils::sstring &desc, const date &dt)
	{
		this->__task = heap_pair(desc, dt);
	}

	task::task(openutils::sstring &&desc, date &&dt)
	{
		this->__task = heap_pair(desc, dt);
	}

	task::task(const task &t)
	{
		this->__task = t.__task;
		this->expired = t.expired;
		this->completed = t.completed;
	}

	task::task(task &&t)
	{
		this->__task = t.__task;
		this->expired = t.expired;
		this->completed = t.completed;
	}

	void task::mark_expired()
	{
		if (this->__task.second() > date())
			this->expired = false;
		else
			this->expired = true;
	}

	bool task::is_expired() const
	{
		return this->expired;
	}

	void task::mark_completed(bool compt)
	{
		this->completed = compt;
	}

	bool task::is_completed() const
	{
		return this->completed;
	}

	const openutils::sstring &task::get_description() const
	{
		return this->__task.first();
	}

	const date &task::get_date() const
	{
		return this->__task.second();
	}

	void task::operator=(const task &t)
	{
		this->__task = t.__task;
		this->expired = t.expired;
		this->completed = t.completed;
	}

	void task::operator=(task &&t)
	{
		this->__task = t.__task;
		this->expired = t.expired;
		this->completed = t.completed;
	}

	task::~task() = default;
};

#endif