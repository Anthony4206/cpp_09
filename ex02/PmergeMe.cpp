#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <exception>
#include <ctime>
#include <algorithm>
#include <vector>
#include <list>

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int argc, char **argv) : _limit(32) {
	for (int i(1); i < argc; ++i) {
		try {
			int	nb = std::stoi(argv[i]);
			if (nb >= 0) {
				_arr.push_back(nb);
				_lst.push_back(nb);
			} else {
				std::cerr << "error: there must be no negative integer" << std::endl;
				exit(EXIT_FAILURE);
			}
		} catch (std::exception const &e) {
			std::cerr << "error: values must be integers" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
}

PmergeMe::~PmergeMe() {
	return ;
}

void	PmergeMe::getArray() {
	std::vector<int>::iterator	it;

	for (it = _arr.begin(); it != _arr.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void	PmergeMe::getList() {
	std::list<int>::iterator	it;

	for (it = _lst.begin(); it != _lst.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void	PmergeMe::getTimeArray() {
	std::cout << "Time to process a range of " << std::setw(4) << _arr.size()
		<< " elements with std::vector : " << std::fixed << std::setprecision(5)
		<< _time_arr << " ms" << std::endl;
}

void	PmergeMe::getTimeList() {
	std::cout << "Time to process a range of " << std::setw(4) << _lst.size()
		<< " elements with std::list   : " << std::fixed << std::setprecision(5)
		<< _time_lst << " ms" << std::endl;
}

void	PmergeMe::arrayMerge(int l, int m, int r) {
	std::inplace_merge(_arr.begin() + l, _arr.begin() + m + 1, _arr.begin() + r + 1);
}

void	PmergeMe::arrayInsertionSort(int l, int r) {
	for (int i(l + 1); i <= r; ++i) {
		int	key = _arr[i];
		int	j = i - 1;

		while (j >= l && _arr[j] > key) {
			_arr[j + 1] = _arr[j];
			j--;
		}
		_arr[j + 1] = key;
	}
}

void	PmergeMe::arrayMergeInsertion(int l, int r) {
	if (r - l <= _limit) {
		arrayInsertionSort(l, r);
		return ;
	}

	int	m = l + (r - l) / 2;

	arrayMergeInsertion(l, m);
	arrayMergeInsertion(m + 1, r);
	arrayMerge(l, m, r);
}

void	PmergeMe::arraySort() {
	int	n = _arr.size();
	clock_t	start = std::clock();

	arrayMergeInsertion(0, n - 1);

	clock_t	end = std::clock();
	
	_time_arr = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
}

void	PmergeMe::listMerge(std::list<int>::iterator l, std::list<int>::iterator m, std::list<int>::iterator r) {
	std::list<int>	tmp;

    std::merge(l, m, m, r, std::back_inserter(tmp));
	std::copy(tmp.begin(), tmp.end(), l);
}

void	PmergeMe::listInsertionSort(std::list<int>::iterator l, std::list<int>::iterator r) {
	for (std::list<int>::iterator i(next(l)); i != r; ++i) {
		int							key = *i;
		std::list<int>::iterator	j = i;

		while (j != l && *std::prev(j) > key) {
			*j = *std::prev(j);
			j--;
		}
		*j = key;
	}
}

void	PmergeMe::listMergeInsertion(std::list<int>::iterator l, std::list<int>::iterator r) {
	if (std::distance(l, r) <= _limit) {
		listInsertionSort(l, r);
		return ;
	}

	std::list<int>::iterator	m = std::next(l, std::distance(l, r) / 2);

	listMergeInsertion(l, m);
	listMergeInsertion(m, r);
	listMerge(l, m, r);
}

void	PmergeMe::listSort() {
	std::list<int>	tmp;

	tmp.splice(tmp.begin(), _lst);

	clock_t	start = std::clock();

	listMergeInsertion(tmp.begin(), tmp.end());
	_lst.splice(_lst.begin(), tmp);

	clock_t	end = std::clock();

	_time_lst = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
}
