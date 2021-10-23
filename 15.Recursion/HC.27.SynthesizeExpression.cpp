/*
 * HC.27.SynthesizeExpression.cpp
 *
 * Problem: Write a program that takes an array of digits and a target value, and returns true
 * 			if it is possible intersperse to intersperse multiplies (*) and adds (+) with digits
 * 			of the array such that the resulting expression evaluates to the target value.
 *
 * 			For example, if the array is <1,2,3,2,5,3,7,8,5,9> and the target value is 995, then
 * 			the target value can be realized by the expression 123 + 2 + 5 * 3 * 7 + 85 * 9.
 *
 *  Created on: Dec 27, 2018
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

// Solution:
//			For each position between two digits there are three possibilities: *, +, and no operator.
//			So there are 3^(n-1) possibilities.
//
//			Due to the complexity how long is the last number and how it operates with its previous
//			number, it is not possible to extend the set of all possible numbers up to index i to
//			index (i+1). So any kind of memoization is not going to help.
//
//			So we are left with exponential enumeration.
//
//			We need to try each of 3 possibilities for each of (n-1) positions.
//			Q. Does is possible to do it in two loops one over n and another over 3?
//			No, as that will give us the possible combinations of 2 positions where first position
//			has n possibilities and second position has 3 possibilities.
//			To enumerate for n positions, we need n loops, each with 3 possibilities.
//			It is not possible to write a program (which is static) that has n (dynamic) loops.
//			So we need to do it recursively.
//
//			But like similar problems we can prune the search space and back track. One thing to note
//			that all 3 operators only increase the result. So if some point result is greater than
//			the target then we can stop.
//
//			Another heuristic is putting no operator is going to generate the largest number.
//			That is because 99 is greater than 9*9=81. So if largest of the remaining numbers is not
//			going to help current expression then there is no need to expand the current expression.
//
//			One thing about implementing the evaluate is that we need to process the multiplications
//			first. So need to keep the numbers in a stack and if the operator is a multiplication then
//			we do the product and keep the result on the top of the stack.

int next_number(const vector<int>& operands, const vector<char>& operators, int* next_operand_idx, int* next_operator_idx);
int IntFromRemainingDigits(const vector<int>& operands, size_t offset);
int Evaluate(const vector<int>& operands, const vector<char>& operators);
bool ExpressionSynthesisHelper(const vector<int>& digits, int target, vector<char>& operators, size_t& position_to_fill);

bool ExpressionSynthesis(const vector<int>& digits, int target) {
	vector<char> operators;
	size_t position_to_fill = 0;
	return ExpressionSynthesisHelper(digits, target, operators, position_to_fill);
}

bool ExpressionSynthesisHelper(const vector<int>& digits, int target, vector<char>& operators, size_t& position_to_fill){

	if(position_to_fill == digits.size()-1) {		// Have one full set. Now compute and check
		if(target == Evaluate(digits, operators)) {
			return true;
		} else {
			return false;
		}
	}

	if(target < Evaluate(digits, operators)) { // prune if already exceeded target
		return false;
	}

	++position_to_fill;		// Need to decrement properly before returning false. False cases do not mess True ones.

	operators.emplace_back(' ');
	bool res = ExpressionSynthesisHelper(digits, target, operators, position_to_fill);
	if(res) {
		return true;
	}
	operators.pop_back();

	operators.emplace_back('*');
	res = ExpressionSynthesisHelper(digits, target, operators, position_to_fill);
	if(res) {
		return true;
	}
	operators.pop_back();

	if(Evaluate(digits, operators) + IntFromRemainingDigits(digits, position_to_fill) < target) {
		// prune: plus will not reach the target even for maximum from the rest
		--position_to_fill;
		return false;
	}

	operators.emplace_back('+');
	res = ExpressionSynthesisHelper(digits, target, operators, position_to_fill);
	if(res) {
		return true;
	}
	operators.pop_back();

	--position_to_fill;
	return false;
}

// Consider all the ' ' operators to find the next number
int next_number(const vector<int>& operands, const vector<char>& operators, int* next_operand_idx, int* next_operator_idx) {
	int result = operands[(*next_operand_idx)++];
	while((*next_operator_idx) < (int)operators.size() && operators[*next_operator_idx] == ' ') {
		++(*next_operator_idx);
		result = result*10 + operands[(*next_operand_idx)++];
	}
	return result;
}

int Evaluate(const vector<int>& operands, const vector<char>& operators) {
	stack<int> intermediate_operands;	// Will hold all the numbers we will do addition afterwards

	int next_operand_idx = 0, next_operator_idx = 0;
	int first_operand = next_number(operands, operators, &next_operand_idx, &next_operator_idx);

	intermediate_operands.push(first_operand);

	while(next_operator_idx < (int)operators.size()) {		// consider operator instead of operand to do partial evaluation
		char op = operators[next_operator_idx++];	// function next_number ensures this operator is either * or +
		int next_operand = next_number(operands, operators, &next_operand_idx, &next_operator_idx);
		if(op == '*') {
			// do the multiplication and push
			int top = intermediate_operands.top();
			intermediate_operands.pop();
			intermediate_operands.push(next_operand * top);
		} else {
			// only push for pluses
			intermediate_operands.push(next_operand);
		}
	}

	int result = 0;
	while(!intermediate_operands.empty()) {
		result += intermediate_operands.top();
		intermediate_operands.pop();
	}
	return result;
}


int IntFromRemainingDigits(const vector<int>& operands, size_t offset) {
	int result = 0;
	while(offset < operands.size()) {
		result = result*10 + operands[offset++];
	}
	return result;
}

int main() {
	vector<int> opnd = {1,2,3,2,5,3,7,8,5,9};

	cout << "Unit testing: Evaluate" << endl;

	vector<char> opr1 = {' ', ' ', '+', '+', '*', '*', '+', ' ', '*'};
	cout << "Evaluated result = " << Evaluate(opnd, opr1) << endl;

	vector<char> opr2 = {' ', ' ', '+', '+', '*', '*', '+', ' '};
	cout << "Partial Evaluated result = " << Evaluate(opnd, opr2) << endl;

	cout << endl << "Actual testing is starting." << endl;

	cout << "Possible 995? " << ExpressionSynthesis(opnd, 995) << endl;

	cout << "Possible 99999999? " << ExpressionSynthesis(opnd, 99999999) << endl;
}
