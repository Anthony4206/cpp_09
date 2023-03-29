#include <iostream>

#include "PmergeMe.hpp"

int	main(int argc, char **argv) {
	if (argc == 1) {
		std::cerr << "error: there must be at least 1 argument" << std::endl;
		return (-1);
	}

	PmergeMe	sort(argc, argv);

	std::cout << "Before: ";
	sort.getList();
	sort.arraySort();
	sort.listSort();
	std::cout << "After:  ";
	sort.getList();
	sort.getTimeArray();
	sort.getTimeList();
	return (0);
}
