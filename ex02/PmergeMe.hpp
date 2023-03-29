#pragma once

# include <vector>
# include <list>

class PmergeMe {
	private:
		PmergeMe();
		PmergeMe(PmergeMe const &rhs);
		PmergeMe	&operator=(PmergeMe const &rhs);

		int const			_limit;
		double				_time_arr;
		double				_time_lst;
		std::vector<int>	_arr;
		std::list<int>		_lst;
	public:
		PmergeMe(int argc, char **argv);
		~PmergeMe();

		void	getArray();
		void	getList();
		void	getTimeArray();
		void	getTimeList();

		void	arraySort();
		void	arrayMergeInsertion(int l, int r);
		void	arrayInsertionSort(int l, int r);
		void	arrayMerge(int l, int m, int r);

		void	listSort();
		void	listMergeInsertion(std::list<int>::iterator l, std::list<int>::iterator r);
		void	listInsertionSort(std::list<int>::iterator l, std::list<int>::iterator r);
		void	listMerge(std::list<int>::iterator l, std::list<int>::iterator m, std::list<int>::iterator r);
};
