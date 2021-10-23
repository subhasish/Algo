/*
 * 02.EvalReversePolish.cpp
 *
 * Problem: Given a reverse polish expression, i.e., post order expression, evaluate it.
 *
 * 			Each input is separated by a ',' comma
 *
 *  Created on: Jan 1, 2018
 *      Author: subha
 */


#include <bits/stdc++.h>

using namespace std;

// Solution: Keep the numbers and intermediate results in a stack. When an operator is encountered pop last two and compute.

int EvalulateReversePolishNotation(string exp)
{
	stack<int> operands;
	stringstream ss(exp);
	string token;
	char delimeter = ',';

	while(getline(ss,token,delimeter)) {
		cout << token << endl;
		if(token == "*" || token == "/" || token == "-" || token == "+") {
			cout << "operator" << endl;
			int op1 = operands.top();
			operands.pop();
			int op2 = operands.top();
			operands.pop();
			int result = op1;
			if(token == "+") {
				result = op1 + op2;
			} else if(token == "-") {
				result = op2 - op1;
			} else if(token == "*") {
				result = op2 * op1;
			} else if(token == "/") {
				result = op2 / op1;
			}

			operands.push(result);
		} else {
			int val = stoi(token);
			cout << "operand: " << val << endl;
			operands.push(val);
		}
	}
	return operands.top();
}

int main()
{
	cout << "Final result = " << EvalulateReversePolishNotation("2,3,*,5,-3,+,-") << endl;
}

