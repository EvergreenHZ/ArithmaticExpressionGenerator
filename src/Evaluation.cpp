#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include "Evaluation.h"
using namespace std;

/**
 * check space
 */
bool isSpace(char c)
{
        if (c == ' ' || c == '\t')
                return true;
        return false;
}

/**
 * check operator
 */
bool Evaluation::isOperator(char c)
{
        switch(c) {
                case '+':
                case '-':
                case '*':
                case '/':
                case '(':
                case ')':
                        return true;
                default:
                        return false;
        }
}

/**
 * check number
 */
bool Evaluation::isNumber(char c)
{
        if ( (c >= '0') && (c <= '9')) {
                return true;
        }
        return false;
}

/**
 * get priority
 */
int Evaluation::getPriority(char op)
{
        switch(op) {
                case '+':
                case '-':
                        return 1;
                case '*':
                case '/':
                        return 2;
                case '(':
                        return 0;
        }
}

/**
 * compare priority
 */
bool Evaluation::superier(char op1, char op2)
{
        if (op1 == '*' || op1 == '/') {
                if (op2 == '+' || op2 == '-') {
                        return true;
                }
        }

        return false;
}

bool Evaluation::inferier(char op1, char op2)
{
        if (op1 == '+' || op1 == '-') {
                if (op2 == '+' || op2 == '-' ||
                    op2 == '*' || op2 == '/') {
                        return true;
                }
        }

        if (op1 == '*' || op1 == '/') {
                if (op2 == '*' || op2 == '/') {
                        return true;
                }
        }
        return false;
}

/**
 * handle operators
 */
void Evaluation::handleOperator(vector<string> &suffix, char op, vector<string> &stack_operators)
{
        switch(op) {
                case '+':
                case '-':
                case '*':
                case '/':
                        if (stack_operators.size() == 0) {  // empty stack, just push
                                stack_operators.push_back(string(1, op));
                        } else if (superier(op, (stack_operators.back())[0])) {  // push directly
                                stack_operators.push_back(string(1, op));
                        } else {
                                while (stack_operators.size() > 0 && inferier(op, (stack_operators.back())[0])) {
                                        suffix.push_back(stack_operators.back());
                                        stack_operators.pop_back();
                                }
                                stack_operators.push_back(string(1, op));
                        }
                        break;
                case '(':
                        stack_operators.push_back(string(1, op));
                        break;
                case ')':
                        while ( (stack_operators.back())[0] != '(') {
                                suffix.push_back(stack_operators.back());
                                stack_operators.pop_back();
                        }
                        stack_operators.pop_back();  // pop ')' out
                        break;
                default:
                        break;
        }
}

void Evaluation::print_vector_string(vector<string> &s)
{
        for (int i = 0; i < s.size(); i++) {
                cout << s[i] << " ";
        }
        cout << endl;
}
/**
 * infix to suffix
 */
vector<string> Evaluation::infixToSuffix(const string &ori_string)
{
        string infix(ori_string);
        vector<string> stack_operators;
        vector<string> suffix;

        cout << infix << endl;

        for (int i = 0; i < infix.size(); i++) {
                //cout << infix.size() << endl;
                // skip space
                while (isSpace(infix[i])) {
                        i++;
                }

                // collect numbers
                if ( (i < infix.size()) && isNumber(infix[i])) {
                        string num;
                        while (isNumber(infix[i])) {
                                num += infix[i++];
                        }
                        suffix.push_back(num);
                }
                if ( (i < infix.size()) && (isOperator(infix[i]))) {// handle operator
                        // keep skipping
                        while ( (i < infix.size()) && isSpace(infix[i])) {
                                i++;
                        }
                        if (i >= infix.size()) break;

                        handleOperator(suffix, infix[i], stack_operators);
                }
                print_vector_string(suffix);
                print_vector_string(stack_operators);
        }

        while (stack_operators.size() > 0) {
                suffix.push_back(stack_operators.back());
                stack_operators.pop_back();
        }
        print_vector_string(suffix);
        print_vector_string(stack_operators);
        return suffix;
}

bool Evaluation::is_operator(const string& s)
{
        char c = s[0];
        return (c == '+' || c == '-' ||
                c == '*' || c == '/');
}

int Evaluation::eval(int lhs, int rhs, string op)
{
        switch (op[0]) {
                case '+':
                        return lhs + rhs;
                case '-':
                        return lhs - rhs;
                case '*':
                        return lhs * rhs;
                case '/':
                        return lhs / rhs;
                default:
                        return 0;
        }
}

int Evaluation::rpn(vector<string> &suffix_exp)
{
        vector<int> stack;

        int i;
        for (i = 0; i < suffix_exp.size(); i++) {
                string token = suffix_exp[i];
                if (is_operator(token)) {
                        if (stack.size() < 2) {
                                break;
                        }

                        int rhs = stack.back();
                        stack.pop_back();
                        int lhs = stack.back();
                        stack.pop_back();
                        stack.push_back(eval(lhs, rhs, token));
                } else {
                        stack.push_back(stoi(token));
                }
        }

        int result = 0;
        if (i == suffix_exp.size() && stack.size() == 1) {
                result = stack.back();
        } else {
                cout << "wrong exp" << endl;
        }
        return result;
}

int Evaluation::solution(string infix_expression)
{
        vector<string> suffix;
        suffix = infixToSuffix(infix_expression);
        return rpn(suffix);
}
