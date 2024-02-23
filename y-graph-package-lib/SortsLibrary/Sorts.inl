#ifndef Y_SORTS_LIB_INL
#define Y_SORTS_LIB_INL

#include <algorithm>
#include <functional>
#include <thread>

/*
 * Header only namespace containing all the sorts used for comparison exercise,
 * also includes std::sort for comparison enclosed in a functor.
 */
namespace yasuzume::sorts
{
#pragma region Defaults

	inline auto standard_determinant{ [] <typename T>(const T & x, const T & y) { return x < y; } };

#pragma endregion

#pragma region Bases

	template<typename C> // Needs to be iterable
	class Sort
	{
	public:
		Sort() = default;
		// Copy constructor
		Sort(Sort&) = default;
		// Move constructor
		Sort(Sort&&) = default;
		// Copy assignment operator
		Sort& operator=(const Sort&) = default;
		// Move assignment operator
		Sort& operator=(Sort&&) = default;
		// Destructor
		virtual ~Sort() = default;

		/**
		 * \brief Sort in given range
		 */
		virtual void operator()(typename C::iterator, typename C::iterator) = 0;

		/**
		 * \brief Sort given container
		 */
		virtual void operator()(C&) = 0;

#ifdef _DEBUG

		/**
		 * \brief Print the current state of the sorted range, useful in exploring behaviour
		 * \param begin beginning of the range
		 * \param end end of the range
		 */
		void print(typename C::iterator begin, typename C::iterator end)
		{
			for (auto i{ begin }; i != end; ++i) std::cout << *i << " ";
			std::cout << "\n";
		}

#endif

	};

	template<typename C> // Needs to be iterable
	class Comparison : public Sort<C>
	{
	public:

		/**
		 * \brief Change determinant to a custom one
		 * \param determinant determinant lambda, condition for the sort
		 */
		virtual void set_determinant(std::function<bool(const typename C::value_type&, const typename C::value_type&)> determinant)
		{
			determinant_ = std::move(determinant);
		}
	protected:
		std::function<bool(const typename C::value_type&, const typename C::value_type&)> determinant_{ standard_determinant };
	};

	template<typename C> // Needs to be iterable
	class Key : Sort<C>
	{
	public:
		virtual void set_key(const C& key)
		{
			key_ = key;
		}
	protected:
		C key_{};
	};

#pragma endregion

#pragma region Standard_Sorts

#pragma region Comparison_Sorts

	/**
	 * \brief Bubble sort, comparison sort checking positions next to each other and swapping them if
	 * determinant is met, if at least one swap occurred during iteration, recursive call is made
	 * \tparam C iterable container
	 */
	template<typename C> // Needs to be iterable
	class BubbleSort final : public Comparison<C>
	{
	public:
		/**
		 * \brief Iterates over provided range, arguments must be of iterator to previously provided type
		 * \param begin beginning of the range
		 * \param end end of the range
		 */
		void operator()(typename C::iterator begin, typename C::iterator end) override
		{
			was_sorted_ = false; // Checks if container was sorted in this iteration
			for (auto i{ begin }; i != end - 1; ++i)
			{
				// Compare container position i with container position i + 1, swap if position i has greater value
				// Mark as sorted this iteration
				if (Comparison<C>::determinant_(*std::next(i), *i))
				{
					std::swap(*std::next(i), *i);
					was_sorted_ = true;
				}
			}
#ifdef _DEBUG

			Sort<C>::print(begin, end);

#endif

			if (was_sorted_) operator()(begin, end);
		}

		/**
		 * \brief Iterates over whole container
		 * \param container iterable container
		 */
		void operator()(C& container) override
		{
			operator()(std::begin(container), std::end(container));
		}

		void sort(typename C::iterator begin, typename C::iterator end)
		{
			operator()(begin, end);
		}

	private:
		bool was_sorted_{ false };
	};

	/**
	 * \brief Bubble sort, comparison sort checking positions next to each other and swapping them if
	 * determinant is met, if at least one swap occurred during iteration, the loop repeats
	 * \tparam C iterable container
	 */
	template<typename C> // Needs to be iterable
	class BubbleSortNonRecursive final : public Comparison<C>
	{
	public:
		/**
		 * \brief Iterates over provided range, arguments must be of iterator to previously provided type
		 * \param begin beginning of the range
		 * \param end end of the range
		 */
		void operator()(typename C::iterator begin, typename C::iterator end) override
		{
			do {
				was_sorted_ = false;
				for (auto i{ begin }; i != end - 1; ++i)
				{
					// Compare container position i with container position i + 1, swap if position i has greater value
					// Mark as sorted this iteration
					if (Comparison<C>::determinant_(*std::next(i), *i))
					{
						std::swap(*std::next(i), *i);
						was_sorted_ = true;
					}
				}
#ifdef _DEBUG

				Sort<C>::print(begin, end);

#endif

			} while (was_sorted_);
		}

		/**
		 * \brief Iterates over whole container
		 * \param container iterable container
		 */
		void operator()(C& container) override
		{
			operator()(std::begin(container), std::end(container));
		}

	private:
		bool was_sorted_{ false };
	};

	/**
	 * \brief Insertion sort, comparison sort comparing ith and i-1 th positions in the container, if determinant is met for i and i-1 position,
	 * starts comparing ith position with i-2 and so on until i == 0 or until determinant is no longer met, swapping this element step by step
	 * \tparam C iterable container
	 */
	template<typename C> // Needs to be iterable
	class InsertionSort final : public Comparison<C>
	{
	public:

		/**
		 * \brief Sorts elements of a given range using insertion sort and given determinant
		 * \param begin beginning of the range
		 * \param end end of the range
		 */
		void operator()(typename C::iterator begin, typename C::iterator end) override
		{
			auto j{ begin };
			for (auto i{ begin }; i != end; ++i)
			{
				j = i;
				// Start comparing container at position j with previous positions,
				// as long as the determinant is met
				while (j != begin && Comparison<C>::determinant_(*j, *std::prev(j)))
				{
					std::swap(*std::prev(j), *j);
					--j;
				}

#ifdef _DEBUG

				Sort<C>::print(begin, end);

#endif

			}
		}

		/**
		 * \brief sorts over entire container using insertion sort
		 * \param container container to be sorted
		 */
		void operator()(C& container) override
		{
			operator()(std::begin(container), std::end(container));
		}
	};

	/**
	 * \brief Selection sort, comparison sort selecting a single item and then comparing it with all next items by some determinant, then it swaps
	 * the positions of selected item and the item the determinant was met for the last time
	 * \tparam C iterable container
	 */
	template <typename C> // Must be iterable
	class SelectionSort final : public Comparison<C>
	{
	public:

		/**
		 * \brief Sorts elements of a given range using selection sort and given determinant
		 * \param begin beginning of the range
		 * \param end end of the range
		 */
		void operator()(typename C::iterator begin, typename C::iterator end) override
		{
			auto k{ begin };
			for (auto i{ begin }; i != end; ++i)
			{
				// Look for determinant match in next positioned elements and note the last position determinant matched
				for (auto j{ std::next(i) }; j != end; ++j)
				{
					if (Comparison<C>::determinant_(*j, *k)) k = j;
				}
				// Swap position compared with the position determinant matched last time
				if (k != i) std::swap(*i, *k);
				k = std::next(i);
#ifdef _DEBUG

				Sort<C>::print(begin, end);

#endif
			}
		}

		/**
		 * \brief sorts over entire container using selection sort
		 * \param container container to be sorted
		 */
		void operator()(C& container) override
		{
			operator()(std::begin(container), std::end(container));
		}
	};

	/**
	 * \brief Quick sort, partitioning sort that swaps elements around the chosen pivot, it repeats it on each side of the pivot and so on,
	 * until the pivot is sorted. Sort is multi-thread safe, but this is its single-thread implementation.
	 * \tparam C iterable container
	 */
	template <typename C> // Needs to be iterable
	class QuickSort final : public Comparison<C>
	{
	public:
		/**
		 * \brief sorts over a given range using quick sort
		 * \param begin beginning of the range
		 * \param end end of the range
		 */
		void operator()(typename C::iterator begin, typename C::iterator end) override
		{
			if (begin == end) return; // When low and high are equal end execution

#ifdef _DEBUG

			Sort<C>::print(begin, end);

#endif

			auto pivot = *std::next(begin, std::distance(begin, end) / 2);
			// Select pivot of the first division
			auto first_pivot_loc{
				std::partition(begin, end, [&pivot, this](const auto& x)
				{
					return Comparison<C>::determinant_(x, pivot);
				}
			) };

			// Select pivot of the second division
			auto second_pivot_loc{
				std::partition(first_pivot_loc, end, [&pivot, this](const auto& x)
				{
					return !Comparison<C>::determinant_(pivot, x);
				}
			) };
			operator()(begin, first_pivot_loc); // Divide container based on partition pivot
			operator()(second_pivot_loc, end);
		}

		/**
		 * \brief sorts over a container using quick sort
		 * \param container container to be sorted
		 */
		void operator()(C& container) override
		{
			operator()(std::begin(container), std::end(container));
		}
	};

	/**
	 * \brief Merge Sort is a sort of type divide and conquer, where all items in a list are halved until the size of each part is 1, then
	 * these items are compared and merged together until the array is fully sorted.
	 * \tparam C iterable container
	 */
	template<typename C> // Needs to be iterable
	class MergeSort final : public Comparison<C>
	{
	public:
		/**
		 * \brief sorts over a range using merge sort
		 * \param begin beginning of a range
		 * \param end end of a range
		 */
		void operator()(typename C::iterator begin, typename C::iterator end) override
		{
			//temporary_list_ = C(std::distance(begin, end));
			merge_sort(begin, end);
		}

		/**
		 * \brief sorts over a container using merge sort
		 * \param container sorted container
		 */
		void operator()(C& container) override
		{
			operator()(std::begin(container), std::end(container));
		}


		/**
		 * \brief divide step of the merge sort, divides the ranges recursively until they are atomic
		 * \param begin beginning of the range
		 * \param end ending of the range
		 */
		void merge_sort(typename C::iterator begin, typename C::iterator end)
		{
			auto dist = std::distance(begin, end); // Calculate range
			if (dist < 2) return; // If range is less than 2, skip

			// Measure midpoint
			auto mid = std::next(begin, dist / 2);

			// Divide into 2 halves
			merge_sort(begin, mid);
			merge_sort(mid, end);

			// Merge and sort halves
			merge(begin, end, C(std::distance(begin, end)));

#ifdef _DEBUG

			Sort<C>::print(begin, end);

#endif
		}

		void sort(typename C::iterator begin, typename C::iterator end)
		{
			operator()(begin, end);
		}

	private:
		/**
		 * \brief Merging and sorting step, implemented on iterators for cleaner code and better performance
		 * \param begin beginning of the range
		 * \param end end of the range
		 * \param temporary_list empty array of size of the range
		 */
		void merge(typename C::iterator begin, typename C::iterator end, C temporary_list)
		{
			// Get all extra iterators - for the middle, for beginning of the range, for middle again and for temporary list
			auto mid = std::next(begin, std::distance(begin, end) / 2);
			auto i{ begin }, j{ mid };
			auto z{ std::begin(temporary_list) };

			// Sorting step - takes ranges from the beginning to half and from half to end. Compare both
			// iterator values and append to temporary list one chosen by determinant, advance chosen one
			while (i != mid && j != end)
			{
				if (Comparison<C>::determinant_(*i, *j))
				{
					*z = *i;
					std::advance(i, 1);
				}
				else
				{
					*z = *j;
					std::advance(j, 1);
				}
				std::advance(z, 1);
			}

			// Copy remaining of the range that was not fully explored
			if (i != mid) std::ranges::copy(i, mid, z);
			if (j != end) std::ranges::copy(j, end, z);

			// Copy temporary array in place of original array
			std::ranges::copy(std::begin(temporary_list), std::end(temporary_list), begin);
		}
	};

#pragma endregion

	// TODO
	template<typename C> // Iterable container
	class CountingSort final : Key<C>
	{
	public:
		void operator()(typename C::iterator begin, typename C::iterator end) override
		{

		}

		void operator()(C& container) override
		{
			operator()(std::begin(container), std::end(container));
		}
	};

	// TODO
	template <typename C> // Iterable container
	class RadixSort final : Key<C>
	{
	public:
		void operator()(typename C::iterator begin, typename C::iterator end) override
		{

		}

		void operator()(C& container) override
		{
			operator()(std::begin(container), std::end(container));
		}
	private:
	};

#pragma endregion

#pragma region Multithreaded_Sorts

	template <typename C>
	class QuickSortAtomic final : Comparison<C>
	{
	public:
		/**
		 * \brief sorts over a given range using quick sort
		 * \param begin beginning of the range
		 * \param end end of the range
		 */
		void operator()(typename C::iterator begin, typename C::iterator end) override
		{
			if (begin == end) return; // When low and high are equal end execution

#ifdef _DEBUG

			Sort<C>::print(begin, end);

#endif
			auto pivot = *std::next(begin, std::distance(begin, end) / 2);
			// Select pivot of the first division
			auto first_pivot_loc{
				std::partition(begin, end, [&pivot, this](const auto& x)
				{
					return Comparison<C>::determinant_(x, pivot);
				}
			) };

			// Select pivot of the second division
			auto second_pivot_loc{
				std::partition(first_pivot_loc, end, [&pivot, this](const auto& x)
				{
					return !Comparison<C>::determinant_(pivot, x);
				}
			) };
			std::thread begin_to_pivot_thread(&QuickSortAtomic::sort, this, begin, first_pivot_loc); // Divide container based on partition pivot
			std::thread pivot_to_end_thread(&QuickSortAtomic::sort, this, second_pivot_loc, end);

			begin_to_pivot_thread.join();
			pivot_to_end_thread.join();
		}

		/**
		 * \brief sorts over a container using quick sort
		 * \param container container to be sorted
		 */
		void operator()(C& container) override
		{
			operator()(std::begin(container), std::end(container));
		}

		void sort(typename C::iterator begin, typename C::iterator end) 
		{
			operator()(begin, end);
		}
	};

	class MergeSortAtomic
	{

	};

	class RadixSortAtomic
	{

	};

#pragma endregion

#pragma region Library_Sorts

	/**
	 * \brief Standard library sort, usually implemented as intro sort, provides fast execution times. Here wrapped as functor.
	 * \tparam C container to iterate over
	 */
	template<typename C> // Iterable container
	class StandardLibrarySort final : Comparison<C>
	{
	public:
		void operator()(typename C::iterator begin, typename C::iterator end) override
		{
			std::sort(begin, end, Comparison<C>::determinant_);
		}

		void operator()(C& container) override
		{
			operator()(std::begin(container), std::end(container));
		}
	};

	/**
	 * \brief Stable Sort ensures that equal items after sorting have the same order as before. Tool of standard library, here wrapped as functor.
	 * \tparam C container to iterate over
	 */
	template <typename C> // Iterable
	class StableStandardSort final : Comparison<C>
	{
	public:
		void operator()(typename C::iterator begin, typename C::iterator end) override
		{
			std::stable_sort(begin, end, Comparison<C>::determinant_);
		}

		void operator()(C& container) override
		{
			operator()(std::begin(container), std::end(container));
		}
	};

#pragma endregion

}

#endif // Y_SORTS_LIB_INL