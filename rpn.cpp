#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool is_operator(const string& s)
{
        char c = s[0];
        return (c == '+' || c == '-' ||
                c == '*' || c == '/');
}

int eval(int lhs, int rhs, string op)
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

int rpn(vector<string> &suffix_exp)
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
