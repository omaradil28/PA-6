#pragma once
#include"PA7.hpp"

class Stack {
public:
	Stack();
	~Stack();

	void push(std::string);
	std::string pop();
	std::string peek();
	bool isEmpty();

private:
	std::vector<std::string> dates;
};


Stack::Stack() {};
Stack::~Stack() {};

//Pushes the string into the stack for storing
void Stack::push(std::string dateAdd) {
	dates.push_back(dateAdd);
}

//removes info from the stack
std::string Stack::pop() {
	if (!isEmpty()) {
		std::string popped = dates.back();
		dates.pop_back();
		return popped;
	}
}

//SHows the top of the stack
std::string Stack::peek() {
	if (dates.size() > 0) {
		return dates.back();
	}
	return "No Absence";
}

//Checks if stack is empty
bool Stack::isEmpty() {
	if (dates.empty()) {
		return true;
	}
	else {
		return false;
	}
}
