#ifndef TODO_HEAP_PAIR_H
#define TODO_HEAP_PAIR_H

#include <openutils/sstring/sstring.hh>

namespace todo
{
	template <typename FIRST, typename SECOND>
	struct heap_pair
	{
	private:
		FIRST *t1;
		SECOND *t2;

	public:
		heap_pair() : t1(nullptr), t2(nullptr) {}

		heap_pair(const heap_pair<FIRST, SECOND> &obj)
		{
			if (obj.t1 && obj.t2)
			{
				this->t1 = new FIRST(*obj.t1);
				openutils::exit_heap_fail(this->t1);
				this->t2 = new SECOND(*obj.t2);
				openutils::exit_heap_fail(this->t2);
			}
			else
			{
				this->t1 = nullptr;
				this->t2 = nullptr;
			}
		}

		heap_pair(heap_pair<FIRST, SECOND> &&obj)
		{
			this->t1 = obj.t1;
			this->t2 = obj.t2;

			obj.t1 = nullptr;
			obj.t2 = nullptr;
		}

		heap_pair(const FIRST &T1, const SECOND &T2)
		{
			this->t1 = new FIRST(T1);
			openutils::exit_heap_fail(this->t1);
			this->t2 = new SECOND(T2);
			openutils::exit_heap_fail(this->t2);
		}

		heap_pair(FIRST &&T1, SECOND &&T2)
		{
			this->t1 = new FIRST(T1);
			openutils::exit_heap_fail(this->t1);
			this->t2 = new SECOND(T2);
			openutils::exit_heap_fail(this->t2);
		}

		heap_pair(std::pair<FIRST, SECOND> pair)
		{
			this->t1 = new FIRST(pair.first);
			openutils::exit_heap_fail(this->t1);
			this->t2 = new SECOND(pair.second);
			openutils::exit_heap_fail(this->t2);
		}

		const FIRST &first() const
		{
			if (!this->t1)
			{
				std::fprintf(stderr, "err: cannot de-reference a null-pointer\n");
				std::exit(EXIT_FAILURE);
			}
			return *this->t1;
		}

		const SECOND &second() const
		{
			if (!this->t2)
			{
				std::fprintf(stderr, "err: cannot de-reference a null-pointer\n");
				std::exit(EXIT_FAILURE);
			}
			return *this->t2;
		}

		void operator=(const heap_pair<FIRST, SECOND> &obj)
		{
			if (obj.t1 && obj.t2)
			{
				if (this->t1 && this->t2)
				{
					delete this->t1;
					delete this->t2;
				}
				this->t1 = new FIRST(*obj.t1);
				openutils::exit_heap_fail(this->t1);
				this->t2 = new SECOND(*obj.t2);
				openutils::exit_heap_fail(this->t2);
			}
		}

		heap_pair<FIRST, SECOND> &operator=(heap_pair<FIRST, SECOND> &&obj)
		{
			if (this != &obj)
			{
				if (obj.t1 && obj.t2)
				{
					if (this->t1 && this->t2)
					{
						delete this->t1;
						delete this->t2;
					}
					this->t1 = obj.t1;
					this->t2 = obj.t2;

					obj.t1 = nullptr;
					obj.t2 = nullptr;
				}
			}
			return *this;
		}

		~heap_pair()
		{
			if (this->t1 && this->t2)
			{
				delete this->t1;
				delete this->t2;
			}
		}
	};
};

#endif