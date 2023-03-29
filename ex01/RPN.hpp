#pragma once

# include <string>
# include <stack>

class RPN {
	private:
		RPN(RPN const &rhs);
		RPN		&operator=(RPN const &rhs);

		int				_result;
		int				_left;
		int				_right;
		std::stack<int>	_stack;
	public:
		RPN();
		~RPN();

		int		getResult() const;

		int		checkStack() const;

		void	digitProcessing(std::string nb);
		void	signProcessing(std::string sign);
};
