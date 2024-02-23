#include "y-graph-package-lib.hpp"

template<typename T>
void print_container(const T&);

typedef std::vector<int>::iterator veci;

int main()
{
	std::vector<int> test_container{ 0, 1, 23, 31, 1, 2, 3, 45, 656, 123, 234, 12, 423, 0, 54, 32, 12, 12, 11, 21, 564, 223, 445, 999, 42, 420, 69, 71, 821, 2, 12, 34, 24, 25, 26, 30, 40, 49, 87, 99, 70, 21 };
	std::vector<int> test_container2(test_container.size());
	std::vector<int> test_container3(test_container.size());
	std::vector<int> test_container4(test_container.size());
	std::vector<int> test_container5(test_container.size());
	std::vector<int> test_container6(test_container.size());
	std::vector<int> test_container7(test_container.size());
	std::vector<int> test_container8(test_container.size());
	std::ranges::copy(test_container.begin(), test_container.end(), test_container2.begin());
	std::ranges::copy(test_container.begin(), test_container.end(), test_container3.begin());
	std::ranges::copy(test_container.begin(), test_container.end(), test_container4.begin());
	std::ranges::copy(test_container.begin(), test_container.end(), test_container5.begin());
	std::ranges::copy(test_container.begin(), test_container.end(), test_container6.begin());
	std::ranges::copy(test_container.begin(), test_container.end(), test_container7.begin());
	std::ranges::copy(test_container.begin(), test_container.end(), test_container8.begin());

	yasuzume::sorts::BubbleSort<std::vector<int>> bubble_sort{};
	yasuzume::sorts::InsertionSort<std::vector<int>> insertion_sort{};
	yasuzume::sorts::SelectionSort<std::vector<int>> selection_sort{};
	yasuzume::sorts::QuickSort<std::vector<int>> quick_sort{};
	yasuzume::sorts::MergeSort<std::vector<int>> merge_sort{};
	yasuzume::sorts::StandardLibrarySort<std::vector<int>> std_sort{};
	yasuzume::sorts::StableStandardSort<std::vector<int>> std_stable{};
	yasuzume::sorts::QuickSortAtomic<std::vector<int>> quick_sort_atomic{};

	yasuzume::utils::Stopwatch stopwatch{};

	std::cout << "BUBBLE SORT\n\n";
	print_container(test_container);
	stopwatch.start();
	bubble_sort(std::begin(test_container), std::end(test_container));
	std::cout << "\n" << stopwatch.end() << " time\n\n";
	print_container(test_container);
	std::cout << "\n";

	std::cout << "INSERTION SORT\n\n";
	print_container(test_container2);
	stopwatch.start();
	insertion_sort(std::begin(test_container2), std::end(test_container2));
	std::cout << "\n" << stopwatch.end() << " time\n\n";
	print_container(test_container2);
	std::cout << "\n";

	std::cout << "SELECTION SORT\n\n";
	print_container(test_container3);
	stopwatch.start();
	selection_sort(std::begin(test_container3), std::end(test_container3));
	std::cout << "\n" << stopwatch.end() << " time\n\n";
	print_container(test_container3);
	std::cout << "\n";

	std::cout << "QUICK SORT\n\n";
	print_container(test_container4);
	stopwatch.start();
	quick_sort(std::begin(test_container4), std::end(test_container4));
	std::cout << "\n" << stopwatch.end() << " time\n\n";
	print_container(test_container4);
	std::cout << "\n";

	std::cout << "MERGE SORT\n\n";
	print_container(test_container5);
	stopwatch.start();
	merge_sort(std::begin(test_container5), std::end(test_container5));
	std::cout << "\n" << stopwatch.end() << " time\n\n";
	print_container(test_container5);
	std::cout << "\n";

	std::cout << "STD::SORT\n\n";
	print_container(test_container6);
	stopwatch.start();
	std_sort(std::begin(test_container6), std::end(test_container6));
	std::cout << "\n" << stopwatch.end() << " time\n\n";
	print_container(test_container6);
	std::cout << "\n";

	std::cout << "STD::STABLE SORT\n\n";
	print_container(test_container7);
	stopwatch.start();
	std_stable(std::begin(test_container7), std::end(test_container7));
	std::cout << "\n" << stopwatch.end() << " time\n\n";
	print_container(test_container7);
	std::cout << "\n";

	
	std::cout << "QUICK SORT ATOMIC\n\n";
	print_container(test_container8);
	stopwatch.start();
	quick_sort_atomic(std::begin(test_container8), std::end(test_container8));
	std::cout << "\n" << stopwatch.end() << " time\n\n";
	print_container(test_container8);
	std::cout << "\n";
	
	return 0;
}

template <typename T>
void print_container(const T& container)
{
	std::cout << "[ ";
	for (size_t i{ 0 }; i < container.size(); i++) std::cout << container.at(i) << (i != container.size() - 1 ? ", " : " ]");
	std::cout << "\n";
}

