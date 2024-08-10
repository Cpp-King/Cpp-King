/*
PhirgOS
Copyright (C) 2024 Bintree Development Team
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/
// https://zh.forvo.com/search/%CF%80%CF%8D%CF%81%CE%B3%CE%BF%CF%82/
#include <cmath>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>

const std::string kCmds[6] = {
	"alias", 
    "calc", 
	"clear",
	"exit",
	"manual",  
    "ori"
};

const double kZero = 1e-14; 

std::map<std::string, std::string> alias;

double dblcalcpre(std::string expr, bool& exce) {
	expr = " " + expr;
	std::stack<double> nums;
	int ending;
	double x, y;
	char op;
	for (int i = expr.length() - 1; i >= 0; i = ending - 1) {
		ending = i;
		if (expr[i] == ' ') continue;
		if (expr[ending - 1] == '.' || (expr[ending - 1] >= '0' && expr[ending - 1] <= '9')) {
			while (expr[ending - 1] == '.' || (expr[ending - 1] >= '0' && expr[ending - 1] <= '9'))
			    ending--;
			try {
				x = std::stod(expr.substr(ending, i - ending + 1)); 
			} catch (const std::exception& e) {
				exce = true;
				std::cerr << "\033[31m[Error] Decimales incorrectos.\n\033[0m";
				std::cout << expr << '\n';
				for (int j = 0; j < ending; j++) std::cout << ' ';
				std::cerr << "\033[31m^\033[0m";
				for (int j = ending; j < i; j++)
				    std::cerr << "\033[31m~\033[0m";
				std::cout << '\n'; 
				return 1.0 / 0.0;
			}
			nums.push(x);
		} else {
			op = expr[i];
			if (nums.size() < 2) {
				exce = true;
				std::cerr << "\033[31m[Error] too few arguments to operation\n\033[0m";
				std::cout << expr << '\n';
				for (int j = 0; j < i; j++) std::cout << ' ';
				std::cerr << "\033[31m^\033[0m";
				std::cout << '\n';
				return 1.0 / 0.0;
			}
			x = nums.top(); nums.pop();
			y = nums.top(); nums.pop();
			switch (op) {
				case '+': {
					nums.push(x + y);
					break;
				}
				case '-': {
					nums.push(x - y);
					break;
				}
				case '*': {
					nums.push(x * y);
					break;
				}
				case '/': {
					if (abs(y) <= kZero) 
						std::cerr << "\033[33m[Warning] divide by kZero\n\033[0m";
					nums.push(x / y);
					break;
				}
				case '^': {
					if (abs(x) <= kZero && abs(y) <= kZero) {
						exce = true;
						std::cerr << "\033[31m[Error] kZero to the kZero power\n\033[0m";
						return 1.0 / 0.0;
					}
					nums.push(pow(x, y));
					break;
				}
				default : {
					exce = true;
					std::cerr << "\033[31m[Error] unsupport operator\033[0m\n";
					std::cout << expr << '\n';
					for (int j = 0; j < i; j++) std::cout << ' ';
					std::cerr << "\033[31m^\033[0m";
					std::cout << '\n';
					return 1.0 / 0.0;
				}
			}
		}
	}
	if (nums.size() > 1) {
	    exce = true;
		std::cerr << "\033[31m[Error] too many arguments to operation\n\033[0m";
		return 1.0 / 0.0;
	}
	exce = false;
	return nums.top(); 
}

double dblcalcsuff(std::string expr, bool& exce) {
	expr = expr + " ";
	std::stack<double> nums;
	int ending;
	double x, y;
	char op;
	for (int i = 0; i < expr.length(); i = ending + 1) {
		ending = i;
		if (expr[i] == ' ') continue;
		if (expr[ending + 1] == '.' || (expr[ending + 1] >= '0' && expr[ending + 1] <= '9')) {
			while (expr[ending + 1] == '.' || (expr[ending + 1] >= '0' && expr[ending + 1] <= '9'))
			    ending++;
			try {
				x = std::stod(expr.substr(i, ending - i + 1)); 
			} catch (const std::exception& e) {
				exce = true;
				std::cerr << "\033[31m[Error] Decimales incorrectos.\n\033[0m";
				std::cout << expr << '\n';
				for (int j = 0; j < i; i++) std::cout << ' ';
				std::cerr << "\033[31m^\033[0m";
				for (int j = i; j < ending; j++)
				    std::cerr << "\033[31m~\033[0m";
				std::cout << '\n'; 
				return 1.0 / 0.0;
			}
			nums.push(x);
		} else {
			op = expr[i];
			if (nums.size() < 2) {
				exce = true;
				std::cerr << "\033[31m[Error] too few arguments to operation\n\033[0m";
				std::cout << expr << '\n';
				for (int j = 0; j < i; j++) std::cout << ' ';
				std::cerr << "\033[31m^\033[0m";
				std::cout << '\n';
				return 1.0 / 0.0;
			}
			y = nums.top(); nums.pop();
			x = nums.top(); nums.pop();
			switch (op) {
				case '+': {
					nums.push(x + y);
					break;
				}
				case '-': {
					nums.push(x - y);
					break;
				}
				case '*': {
					nums.push(x * y);
					break;
				}
				case '/': {
					if (abs(y) <= kZero) 
						std::cerr << "\033[33m[Warning] divide by zero\n\033[0m";
					nums.push(x / y);
					break;
				}
				case '^': {
					if (abs(x) <= kZero && abs(y) <= kZero) {
						exce = true;
						std::cerr << "\033[31m[Error] zero to the zero power\n\033[0m";
						return 1.0 / 0.0;
					}
					nums.push(pow(x, y));
					break;
				}
				default : {
					exce = true;
					std::cerr << "\033[31m[Error] unsupport operator\033[0m\n";
					std::cout << expr << '\n';
					for (int j = 0; j < i; j++) std::cout << ' ';
					std::cerr << "\033[31m^\033[0m";
					std::cout << '\n';
					return 1.0 / 0.0;
				}
			}
		}
	}
	if (nums.size() > 1) {
	    exce = true;
		std::cerr << "\033[31m[Error] too many arguments to operation\n\033[0m";
		return 1.0 / 0.0;
	}
	exce = false;
	return nums.top(); 
}

long long intcalcpre(std::string expr, bool& exce) {
	expr = " " + expr;
	std::stack<double> nums;
	int ending;
	double x, y;
	char op;
	for (int i = expr.length() - 1; i >= 0; i = ending - 1) {
		ending = i;
		if (expr[i] == ' ') continue;
		if (expr[ending - 1] == '.' || (expr[ending - 1] >= '0' && expr[ending - 1] <= '9')) {
			while (expr[ending - 1] == '.' || (expr[ending - 1] >= '0' && expr[ending - 1] <= '9'))
			    ending--;
			try {
				x = std::stod(expr.substr(ending, i - ending + 1)); 
			} catch (const std::exception& e) {
				exce = true;
				std::cerr << "\033[31m[Error] Decimales incorrectos.\n\033[0m";
				std::cout << expr << '\n';
				for (int j = 0; j < ending; j++) std::cout << ' ';
				std::cerr << "\033[31m^\033[0m";
				for (int j = ending; j < i; j++)
				    std::cerr << "\033[31m~\033[0m";
				std::cout << '\n'; 
				return 1.0 / 0.0;
			}
			nums.push(x);
		} else {
			op = expr[i];
			if (nums.size() < 2) {
				exce = true;
				std::cerr << "\033[31m[Error] too few arguments to operation\n\033[0m";
				std::cout << expr << '\n';
				for (int j = 0; j < i; j++) std::cout << ' ';
				std::cerr << "\033[31m^\033[0m";
				std::cout << '\n';
				return 1.0 / 0.0;
			}
			x = nums.top(); nums.pop();
			y = nums.top(); nums.pop();
			switch (op) {
				case '+': {
					nums.push(x + y);
					break;
				}
				case '-': {
					nums.push(x - y);
					break;
				}
				case '*': {
					nums.push(x * y);
					break;
				}
				case '/': {
					if (abs(y) <= kZero) 
						std::cerr << "\033[33m[Warning] divide by kZero\n\033[0m";
					nums.push(x / y);
					break;
				}
				case '^': {
					if (abs(x) <= kZero && abs(y) <= kZero) {
						exce = true;
						std::cerr << "\033[31m[Error] kZero to the kZero power\n\033[0m";
						return 1.0 / 0.0;
					}
					nums.push(pow(x, y));
					break;
				}
				default : {
					exce = true;
					std::cerr << "\033[31m[Error] unsupport operator\033[0m\n";
					std::cout << expr << '\n';
					for (int j = 0; j < i; j++) std::cout << ' ';
					std::cerr << "\033[31m^\033[0m";
					std::cout << '\n';
					return 1.0 / 0.0;
				}
			}
		}
	}
	if (nums.size() > 1) {
	    exce = true;
		std::cerr << "\033[31m[Error] too many arguments to operation\n\033[0m";
		return 1.0 / 0.0;
	}
	exce = false;
	return nums.top(); 
}

long long intcalcsuff(std::string expr, bool& exce) {
	expr = expr + " ";
	std::stack<long long> nums;
	int ending;
	long long x, y;
	char op;
	for (int i = 0; i < expr.length(); i = ending + 1) {
		ending = i;
		if (expr[i] == ' ') continue;
		if (expr[ending + 1] >= '0' && expr[ending + 1] <= '9') {
			while (expr[ending + 1] >= '0' && expr[ending + 1] <= '9')
			    ending++;
			try {
				x = std::stoll(expr.substr(i, ending - i + 1)); 
			} catch (const std::exception& e) {
				exce = true;
				std::cerr << "\033[31m[Error] Decimales incorrectos.\n\033[0m";
				std::cout << expr << '\n';
				for (int j = 0; j < i; i++) std::cout << ' ';
				std::cerr << "\033[31m^\033[0m";
				for (int j = i; j < ending; j++)
				    std::cerr << "\033[31m~\033[0m";
				std::cout << '\n'; 
				return 0x7fffffff;
			}
			nums.push(x);
		} else {
			op = expr[i];
			if (nums.size() < 2) {
				exce = true;
				std::cerr << "\033[31m[Error] too few arguments to operation\n\033[0m";
				std::cout << expr << '\n';
				for (int j = 0; j < i; j++) std::cout << ' ';
				std::cerr << "\033[31m^\033[0m";
				std::cout << '\n';
				return 1.0 / 0.0;
			}
			y = nums.top(); nums.pop();
			switch (op) {
				case '+': {
					x = nums.top(); nums.pop();
					nums.push(x + y);
					break;
				}
				case '-': {
					x = nums.top(); nums.pop();
					nums.push(x - y);
					break;
				}
				case '*': {
					x = nums.top(); nums.pop();
					nums.push(x * y);
					break;
				}
				case '/': {
					x = nums.top(); nums.pop();
					if (!y) {
			            exce = true;
						std::cerr << "\033[31m[Error] divide by zero\n\033[0m";
						std::cout << expr << '\n';
					    for (int j = 0; j < i; j++) std::cout << ' ';
					    std::cerr << "\033[31m^\033[0m";
					    std::cout << '\n';
					    return 0x7fffffffffffffff;
					}
					nums.push(x / y);
					break;
				}
				case '^': {
					x = nums.top(); nums.pop();
					if (!x && !y) {
						exce = true;
						std::cerr << "\033[31m[Error] zero to the zero power\n\033[0m";
						std::cout << expr << '\n';
					    for (int j = 0; j < i; j++) std::cout << ' ';
					    std::cerr << "\033[31m^\033[0m";
					    std::cout << '\n';
						return 0x7fffffffffffffff;
					}
					nums.push(pow(x, y));
					break;
				}
				case '!': {
					if (y < 0) {
						exce = true;
						std::cerr << "\033[31m[Error] Factorial of a negative number\n]\033[0m";
					    std::cout << expr << '\n';
					    for (int j = 0; j < i; j++) std::cout << ' ';
					    std::cerr << "\033[31m^\033[0m";
					    std::cout << '\n';
					    return 0x7fffffffffffffff;
					}
					break;
				}
				default : {
					exce = true;
					std::cerr << "\033[31m[Error] unsupport operator\033[0m\n";
					std::cout << expr << '\n';
					for (int j = 0; j < i; j++) std::cout << ' ';
					std::cerr << "\033[31m^\033[0m";
					std::cout << '\n';
					return 0x7fffffffffffffff;
				}
			}
		}
	}
	if (nums.size() > 1) {
	    exce = true;
		std::cerr << "\033[31m[Error] too many arguments to operation\n\033[0m";
		return 0x7fffffff;
	}
	exce = false;
	return nums.top(); 
}

int priority(char op) {
	if (op == '+' || op == '-') return 1;
	if (op == '*' || op == '/') return 2;
	if (op == '^') return 3;
	return 4;
}

std::string intosuff(std::string expr) {
	std::stringstream ss;
	std::stack<char> ops;
	for (int i = 0; i < expr.length(); i++) {
		if (expr[i] == ' ') continue;
		if (expr[i] == '.' || (expr[i] >= '0' && expr[i] <= '9')) {
		    ss << expr[i];
		    while (i < expr.length() && expr[i + 1] == '.' || (expr[i + 1] >= '0' && expr[i + 1] <= '9'))
		        ss << expr[++i];
		    ss << ' ';
		} else if (expr[i] == '(')
		    ops.push(expr[i]);
		else if (expr[i] == ')') {
			while (ops.top() != '(') {
				ss << ops.top() << ' ';
				ops.pop();
			}
			ops.pop();
		} else {
			while (!ops.empty() && ops.top() != '(' && priority(expr[i]) <= priority(ops.top())) {
				ss << ops.top() << ' ';
				ops.pop();
			}
			ops.push(expr[i]);
		}
	}
	while (!ops.empty()) {
		ss << ops.top() << ' ';
		ops.pop();
	}
	return ss.str();
}

void calc(std::string param) {
    char f = 'i';
    bool d = false;
    int estart = -1;
    int eend = -1;
	for (int i = 0; i < param.length(); i++)
	    if ((estart == -1 || eend != -1) && param[i] == '-') {
	    	for (int j = i + 1; j < param.length() && param[j] != ' '; j++)
		        if (param[j] == 'p')
		            f = 'p';
		        else if (param[j] == 'i')
		            f = 'i';
		        else if (param[j] == 's')
		            f = 's';
		        else if (param[j] == 'd')
		            d = true;
		        else {
		    	    std::cerr << "\033[31m[Error] unknown option: -" << param[j] << "\n\033[0m";
		    	    return;
			    }
	    } else if (param[i] == '\"') {
	    	std::cout << i << ' ' << estart << ' ' << eend << '\n';
	        if (estart == -1)
	            estart = i;
	        else if (eend == -1) 
	            eend = i;
	        else {
	        	std::cerr << "\033[31m[Error] too many arguments to command \"calc\"\n\033[0m";
	        	std::cout << param.substr(estart, i - estart + 1);
	        	for (int j = estart; j <= eend; j++)
	        	    std::cout << ' ';
	        	std::cerr << "\033[31m^\033[0m";
	        	for (int j = eend; j < i; j++)
	        	    std::cerr << "\033[31m~\033[0m";
	        	std::cerr << '\n';
	        	return;
			}
		}
	std::cout << estart << ' ' << eend << '\n'; 
	if (eend == -1) {
		std::cerr << "\033[31m[Error] no expression\n\033[0m";
	    return;
	}
	bool exce;
	if (d) {
		double ans;
		if (f == 'p') ans = dblcalcpre(param.substr(estart + 1, eend - estart - 1), exce);
		else if (f == 'i') ans = dblcalcsuff(intosuff(param.substr(estart + 1, eend - estart - 1)), exce);
		else ans = dblcalcsuff(param.substr(estart + 1, eend - estart - 1), exce);
		if (!exce)
		    std::cout << ans << '\n';
	} /*else {
		long long ans;
		if (f == 'p') ans = intcalcpre(ss.str(), exce);
		e
		lse if (f == 'i') ans = intcalcsuff(intosuff(ss.str()), exce);
		else ans = intcalcsuff(ss.str(), exce);
		if (!exce)
		    cout << ans << '\n';
	}*/
}

void exec(std::string command) {
	calc(command);
}

int main() {
	std::cout << "PhirgOS [V0.1.0.20240731_Alpha]\nCopyright (C) blue-peace2013.\n";
	std::string s;
	while (true) {
		getline(std::cin, s);
		exec(s);
	}
	return 0;
}
