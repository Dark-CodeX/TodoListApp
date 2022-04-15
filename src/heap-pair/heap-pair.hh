#pragma once

namespace todo
{
	template <typename FIRST, typename SECOND>
	struct heap_pair
	{
	private:
		FIRST *t1;
		SECOND *t2;
		bool is_alloc;

	public:
		heap_pair() : is_alloc(false) {}

		heap_pair(const heap_pair<FIRST, SECOND> &obj)
		{
			this->is_alloc = obj.is_alloc;
			if (this->is_alloc)
			{
				this->t1 = new FIRST[1];
				this->t2 = new SECOND[1];
				this->t1[0] = obj.t1[0];
				this->t2[0] = obj.t2[0];
			}
		}

		heap_pair(heap_pair<FIRST, SECOND> &&obj)
		{
			this->is_alloc = obj.is_alloc;
			this->t1 = obj.t1;
			this->t2 = obj.t2;

			obj.is_alloc = false;
			obj.t1 = nullptr;
			obj.t2 = nullptr;
		}

		heap_pair(const FIRST &T1, const SECOND &T2)
		{
			this->t1 = new FIRST[1];
			this->t2 = new SECOND[1];
			this->t1[0] = T1;
			this->t2[0] = T2;
			this->is_alloc = true;
		}

		heap_pair(FIRST &&T1, SECOND &&T2)
		{
			this->t1 = new FIRST[1];
			this->t2 = new SECOND[1];
			this->t1[0] = T1;
			this->t2[0] = T2;
			this->is_alloc = true;
		}

		heap_pair(std::pair<FIRST, SECOND> pair)
		{
			this->t1 = new FIRST[1];
			this->t2 = new SECOND[1];
			this->t1[0] = pair.first;
			this->t2[0] = pair.second;
			this->is_alloc = true;
		}

		const FIRST &first() const
		{
			if (this->is_alloc)
				return this->t1[0];
			std::fprintf(stderr, "invalid access\n");
			std::exit(EXIT_FAILURE);
		}

		const SECOND &second() const
		{
			if (this->is_alloc)
				return this->t2[0];
			std::fprintf(stderr, "invalid access\n");
			std::exit(EXIT_FAILURE);
		}

		void operator=(const heap_pair<FIRST, SECOND> &obj)
		{
			if (this->is_alloc)
			{
				delete[] this->t1;
				delete[] this->t2;
			}
			this->is_alloc = obj.is_alloc;
			if (this->is_alloc)
			{
				this->t1 = new FIRST[1];
				this->t2 = new SECOND[1];
				this->t1[0] = obj.t1[0];
				this->t2[0] = obj.t2[0];
			}
		}

		heap_pair<FIRST, SECOND> &operator=(heap_pair<FIRST, SECOND> &&obj)
		{
			if (this != &obj)
			{
				if (this->is_alloc)
				{
					delete[] this->t1;
					delete[] this->t2;
				}
				this->is_alloc = obj.is_alloc;
				this->t1 = obj.t1;
				this->t2 = obj.t2;

				obj.is_alloc = false;
				obj.t1 = nullptr;
				obj.t2 = nullptr;
			}
			return *this;
		}

		~heap_pair()
		{
			if (this->is_alloc)
			{
				delete[] this->t1;
				delete[] this->t2;
			}
		}
	};
};