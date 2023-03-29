#include <iostream>
#include <string>

#include "RPN.hpp"

RPN::RPN() : _result(0), _left(0), _right(0) {
	return ;
}

RPN::~RPN() {
	return ;
}

int	RPN::getResult() const {
	return (_result);
}

int	RPN::checkStack() const {
	if (_stack.size() != 1) {
		return (-1);
	}
	return (0);
}

void	RPN::digitProcessing(std::string nb) {
	_stack.push(std::stoi(nb));
}

void	RPN::signProcessing(std::string sign) {
	if (_stack.size() < 2) {
		std::cerr << "Error" << std::endl;
		exit(EXIT_FAILURE);
	}
	_right = _stack.top();
	_stack.pop();
	_left = _stack.top();
	_stack.pop();

	if (sign == "+") {
		_stack.push(_left + _right);
	} else if (sign == "-") {
		_stack.push(_left - _right);
	} else if (sign == "/") {
		_stack.push(_left / _right);
	} else if (sign == "*") {
		_stack.push(_left * _right);
	}
	_result = _stack.top();
}
