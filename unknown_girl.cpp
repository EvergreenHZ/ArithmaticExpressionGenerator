#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include "unknown_girl.h"
using namespace std;


bool ArithmaticExpression::cast_coin()
{
        if (rand() % 2 == 0) {
                return false;
        } else {
                return true;
        }
}

ArithmaticExpression::ArithmaticExpression(int module):
        MODULE(module) { 
                srand(time(NULL));
        }

int ArithmaticExpression::gen_random()
{
        int x;
        while ( (x = rand() % MODULE) == 0) {  // bad number
                ;
        }
        return x;
}

int ArithmaticExpression::get_random(int module)
{
        int x;
        while ( (x = rand() % module) == 0) {
                ;
        }
        return x;
}

char ArithmaticExpression::gen_operator()
{
        int coin = rand() % 4;
        switch (coin) {
                case '0':
                        return '+';
                case '1':
                        return '-';
                case '2':
                        return '*';
                case '3':
                        return '/';
        }
}

void ArithmaticExpression::int_to_string(int x, string& str)
{
        ostringstream oss;
        oss << x;
        str = oss.str();
}

void ArithmaticExpression::get_factors(int n, vector<int> &factors)
{
        for (int i = 1; i < (n + 1) / 2; i++) {
                if (n % i == 0) {
                        factors.push_back(i);
                }
        }
        random_shuffle(factors.begin(), factors.end());
}

int ArithmaticExpression::get_priority(char op)
{
        switch (op) {
                case '+':
                case '-':
                        return 0;
                case '*':
                case '/':
                        return 1;
        }
        return -1;
}

bool ArithmaticExpression::a_plus_b(vector<string> &exp)
{
        int a, b;
        a = gen_random();  // a >= 1
        b = gen_random();  // b >= 1
        if (a < b) {
                int t = a;
                a = b;
                b = a;
        }
        while (a + b > MODULE) {
                a /= 2;
        }

        if (rand() % 2 == 0) {
                int t = a;
                a = b;
                b = a;
        }

        string aa, bb;
        int_to_string(a, aa);
        int_to_string(b, bb);
        string op(1, '+');
        exp.push_back(aa);
        exp.push_back(op);
        exp.push_back(bb);

        return true;
}

bool ArithmaticExpression::a_minus_b(vector<string> &exp)
{
        int a, b;
        a = gen_random();  // a >= 1
        b = gen_random();  // b >= 1
        if (a < b) {
                int t = a;
                a = b;
                b = a;
        }

        string aa, bb;
        int_to_string(a, aa);
        int_to_string(b, bb);
        string op(1, '+');
        exp.push_back(aa);
        exp.push_back(op);
        exp.push_back(bb);

        return true;
}

bool ArithmaticExpression::a_times_b(vector<string> &exp)
{
        int a, b;
        a = gen_random();  // a >= 1
        b = gen_random();  // b >= 1
        if (a < b) {
                int t = a;
                a = b;
                b = a;
        }

        while ( (a * b > MODULE)) {
                a /= 2;
        }

        string aa, bb;
        int_to_string(a, aa);
        int_to_string(b, bb);
        string op(1, '+');
        exp.push_back(aa);
        exp.push_back(op);
        exp.push_back(bb);

        return true;
}

bool ArithmaticExpression::a_over_b(vector<string> &exp)
{
        int a, b;
        a = gen_random();  // a >= 1
        b = gen_random();  // b >= 1
        if (a < b) {
                int t = a;
                a = b;
                b = a;
        }

        while ( (a * b > MODULE)) {
                a /= 2;
        }

        string aa, bb;
        int_to_string(a, aa);
        int_to_string(b, bb);
        string op(1, '+');
        exp.push_back(aa);
        exp.push_back(op);
        exp.push_back(bb);

        return true;
}

/* a op b is ok */
vector<string> ArithmaticExpression::gen_a_op_b()
{
        vector<string> exp;
        switch ( gen_operator()) {
                case '+':
                        a_plus_b(exp);
                        break;
                case '-':
                        a_minus_b(exp);
                        break;
                case '*':
                        a_times_b(exp);
                        break;
                case '/':
                        a_over_b(exp);
                        break;
        }
        return exp;
}

bool ArithmaticExpression::good_enough(const int n)
{
        if (n < 10) {
                return false;
        }
        return true;
}

bool ArithmaticExpression::split_a_plus_b(const int c, int &a, int &b)
{
        if (!good_enough(c)) {
                return false;
        } else {
                int x;
                while ( (x = rand() % c) == 0) {
                        ;
                }
                a = x;
                b = c - a;
        }
        return true;
}

bool ArithmaticExpression::split_a_minus_b(const int c, int &a, int &b)
{
        if (!good_enough(c)) {
                return false;
        } else {
                b = rand() % c;
                a = c + b;
        }
        return true;
}

bool ArithmaticExpression::split_a_times_b(const int c, int &a, int &b)
{
        if (!good_enough(c)) {
                return false;
        }
        vector<int> factors;
        get_factors(c, factors);
        a = factors[0];
        b = c / a;
        return true;
}

bool ArithmaticExpression::split_a_over_b(const int c, int &a, int &b)
{
        if (!good_enough(c)) {
                return false;
        }
        //vector<int> factors;
        //get_factors(c, factors);
        int x = gen_random();
        if ( (x * c > MODULE)) {
                x /= 2;
        }  // x won't be 0
        a = x * c;
        b = x;

        return true;
}

bool ArithmaticExpression::collect_a_op_b_op_c(int a, int b, int c, char op1, char op2, vector<string> &exp)
{
        string aa, bb, cc, str_op1, str_op2;
        int_to_string(a, aa);
        int_to_string(b, bb);
        int_to_string(c, cc);
        str_op1 = string(1, op1);
        str_op2 = string(1, op2);

        exp.push_back(aa);
        exp.push_back(str_op1);
        exp.push_back(bb);
        exp.push_back(str_op2);
        exp.push_back(cc);

        return true;
}

bool ArithmaticExpression::find_good_y_for_x_times_y(const int x, int &y)
{
        if (!good_enough(x)) {
                return false;
        } else {
                y = gen_random();
                while ( (y * x > MODULE)) {
                        y = y / 2;
                }
                return true;
        }
}
bool ArithmaticExpression::find_good_y_for_x_over_y(const int x, int &y)
{
        if (!good_enough(x)) {
                return false;
        } else {
                vector<int> factors;
                get_factors(x, factors);
                y = factors[0];
                return true;
        }
}

bool ArithmaticExpression::find_good_y_for_x_plus_y(const int x, int &y)
{
        if (!good_enough(x)) {
                return false;
        } else {
                y = gen_random();
                while (x + y > MODULE) {
                        y /= 2;
                }
                return true;
        }
}

bool ArithmaticExpression::find_good_y_for_x_minus_y(const int x, int &y)
{
        if (!good_enough(x)) {
                return false;
        } else {
                y = get_random(x);
                return true;
        }
}

/* if return value is empty, not succeed */
vector<string> ArithmaticExpression::gen_a_op_b_op_c()
{
        vector<string> exp;
        char op1, op2;
        int a, b, c;
        int priority_op1, priority_op2;
        int answer = gen_random();
        string aa, bb, cc;
        string str_op1, str_op2;

        op1 = gen_operator();

        if (op1 == '+') {
                if (split_a_plus_b(answer, a, b)) {  // first a + b is ok

                        op2 = gen_operator();

                        if (op2 == '+') {
                                int tmp_b = b;
                                if (split_a_plus_b(tmp_b, b, c)) {  // now a + b + c is ok
                                        collect_a_op_b_op_c(a, b, c, op1, op2, exp);
                                        return exp;
                                }

                        } else if (op2 == '-') {
                                int tmp_b = b;
                                if (split_a_minus_b(tmp_b, b, c)) {  // now a + b - c is ok
                                        collect_a_op_b_op_c(a, b, c, op1, op2, exp);
                                        return exp;
                                }
                        } else if (op2 == '*') {
                                if (find_good_y_for_x_times_y(answer, c)) {  // now (a + b) * c
                                        vector<string> tmp;
                                        collect_a_op_b_op_c(a, b, c, op1, op2, tmp);
                                        exp.push_back(string(1, '('));
                                        exp.push_back(tmp[0]);
                                        exp.push_back(tmp[1]);
                                        exp.push_back(tmp[2]);
                                        exp.push_back(string(1, ')'));
                                        exp.push_back(tmp[3]);
                                        exp.push_back(tmp[4]);
                                        return exp;
                                }
                        } else if (op2 == '/') {  // now (a + b) / c
                                if (find_good_y_for_x_over_y(answer, c)) {  // now (a + b) / c
                                        vector<string> tmp;
                                        collect_a_op_b_op_c(a, b, c, op1, op2, tmp);
                                        exp.push_back(string(1, '('));
                                        exp.push_back(tmp[0]);
                                        exp.push_back(tmp[1]);
                                        exp.push_back(tmp[2]);
                                        exp.push_back(string(1, ')'));
                                        exp.push_back(tmp[3]);
                                        exp.push_back(tmp[4]);
                                        return exp;
                                }
                        }
                }
        } else if (op1 == '-') {
                if (split_a_minus_b(answer, a, b)) {  // first a - b is ok
                        op2 = gen_operator();

                        if (op2 == '+') {
                                int coin = gen_random() % 2;
                                if (coin) {  // a - b + c
                                        c = gen_random();
                                        while (c + answer > MODULE) {
                                                c /= 2;
                                        }
                                        collect_a_op_b_op_c(a, b, c, op1, op2, exp);
                                        return exp;
                                } else {  // a - (b + c) = a - b - c
                                        if (find_good_y_for_x_minus_y(answer, c)) {
                                                vector<string> tmp;
                                                collect_a_op_b_op_c(a, b, c, op1, op2, tmp);
                                                exp.push_back(tmp[0]);
                                                exp.push_back(tmp[1]);
                                                exp.push_back(string(1, '('));
                                                exp.push_back(tmp[2]);
                                                exp.push_back(tmp[3]);
                                                exp.push_back(tmp[4]);
                                                exp.push_back(string(1, ')'));
                                                return exp;

                                        }
                                }

                        } else if (op2 == '-') {  // a - b - c || a - (b - c) = a - b + c
                                int coin = gen_random() % 2;
                                if (coin) {  // a - b - c is ok
                                        c = rand() % answer;
                                        collect_a_op_b_op_c(a, b, c, op1, op2, exp);
                                        return exp;
                                } else {  // a - (b + c)
                                        if (find_good_y_for_x_plus_y(answer, c)) {
                                                vector<string> tmp;
                                                collect_a_op_b_op_c(a, b, c, op1, op2, tmp);
                                                exp.push_back(tmp[0]);
                                                exp.push_back(tmp[1]);
                                                exp.push_back(string(1, '('));
                                                exp.push_back(tmp[2]);
                                                exp.push_back(tmp[3]);
                                                exp.push_back(tmp[4]);
                                                exp.push_back(string(1, ')'));
                                                return exp;
                                        }
                                }
                        } else if (op2 == '*') {
                                if (cast_coin()) {
                                        if (find_good_y_for_x_times_y(answer, c)) {  // now (a - b) * c
                                                vector<string> tmp;
                                                collect_a_op_b_op_c(a, b, c, op1, op2, tmp);
                                                exp.push_back(string(1, '('));
                                                exp.push_back(tmp[0]);
                                                exp.push_back(tmp[1]);
                                                exp.push_back(tmp[2]);
                                                exp.push_back(string(1, ')'));
                                                exp.push_back(tmp[3]);
                                                exp.push_back(tmp[4]);
                                                return exp;
                                        }
                                } else {  // a - b * c
                                        while ( (a = gen_random()) < answer) {
                                                a = gen_random();
                                        }
                                        if (split_a_times_b(answer, b, c)) {
                                                collect_a_op_b_op_c(a, b, c, op1, op2, exp);
                                                return exp;
                                        }
                                }
                        } else if (op2 == '/') {  // now (a + b) / c
                                if (cast_coin()) {
                                        if (find_good_y_for_x_over_y(answer, c)) {  // now (a + b) / c
                                                vector<string> tmp;
                                                collect_a_op_b_op_c(a, b, c, op1, op2, tmp);
                                                exp.push_back(string(1, '('));
                                                exp.push_back(tmp[0]);
                                                exp.push_back(tmp[1]);
                                                exp.push_back(tmp[2]);
                                                exp.push_back(string(1, ')'));
                                                exp.push_back(tmp[3]);
                                                exp.push_back(tmp[4]);
                                                return exp;
                                        }
                                } else {  // a + b / c
                                        while ( (a = gen_random()) + answer > MODULE) {
                                                a /= 2;
                                        }
                                        if (split_a_over_b(answer, b, c)) {
                                                collect_a_op_b_op_c(a, b, c, op1, op2, exp);
                                                return exp;
                                        }
                                }
                        }
                }
        } else if (op1 == '*') {
                if (split_a_times_b(answer, a, b)) {  // a * b is ok
                        op2 = gen_operator();

                        if (op2 == '+') {
                                if (cast_coin()) {  // a * b + c
                                        if (find_good_y_for_x_plus_y(answer, c)) {
                                                collect_a_op_b_op_c(a, b, c, op1, op2, exp);
                                                return exp;
                                        }
                                } else {  // a * (b + c)
                                        int t = 1;
                                        if (find_good_y_for_x_times_y(a, t)) {
                                                if (split_a_plus_b(t, b, c)) {
                                                        vector<string> tmp;
                                                        collect_a_op_b_op_c(a, b, c, op1, op2, tmp);
                                                        exp.push_back(tmp[0]);
                                                        exp.push_back(tmp[1]);
                                                        exp.push_back(string(1, '('));
                                                        exp.push_back(tmp[2]);
                                                        exp.push_back(tmp[3]);
                                                        exp.push_back(tmp[4]);
                                                        exp.push_back(string(1, ')'));
                                                        return exp;
                                                }
                                        }
                                }
                        } else if (op2 == '-') {
                                if (cast_coin()) {  // a * b - c
                                        if (find_good_y_for_x_minus_y(answer, c)) {
                                                collect_a_op_b_op_c(a, b, c, op1, op2, exp);
                                                return exp;
                                        }
                                } else {  // a * (b - c)
                                        int t = 1;
                                        if (find_good_y_for_x_times_y(a, t)) {
                                                if (split_a_minus_b(t, b, c)) {
                                                        vector<string> tmp;
                                                        collect_a_op_b_op_c(a, b, c, op1, op2, tmp);
                                                        exp.push_back(tmp[0]);
                                                        exp.push_back(tmp[1]);
                                                        exp.push_back(string(1, '('));
                                                        exp.push_back(tmp[2]);
                                                        exp.push_back(tmp[3]);
                                                        exp.push_back(tmp[4]);
                                                        exp.push_back(string(1, ')'));
                                                        return exp;
                                                }
                                        }
                                }
                        } else if (op2 == '*') {  // a * b * c
                                c = gen_random();
                                while (c * answer > MODULE) {
                                        c /= 2;
                                }
                                collect_a_op_b_op_c(a, b, c, op1, op2, exp);
                                return exp;
                        } else {  // a * b / c
                                vector<int> factors;
                                get_factors(answer, factors);
                                c = factors[0];
                                collect_a_op_b_op_c(a, b, c, op1, op2, exp);
                                return exp;
                        }
                }
        } else {  // op1 == '/'
                if (split_a_over_b(answer, a, b)) {  // a / b is ok
                        op2 = gen_operator();

                        if (op2 == '+') {
                                if (cast_coin()) {  // a / b + c
                                        if (find_good_y_for_x_plus_y(answer, c)) {
                                                collect_a_op_b_op_c(a, b, c, op1, op2, exp);
                                                return exp;
                                        }
                                } else {  // a / (b + c)
                                        int t = 1;
                                        if (find_good_y_for_x_times_y(a, t)) {
                                                if (split_a_plus_b(t, b, c)) {
                                                        vector<string> tmp;
                                                        collect_a_op_b_op_c(a, b, c, op1, op2, tmp);
                                                        exp.push_back(tmp[0]);
                                                        exp.push_back(tmp[1]);
                                                        exp.push_back(string(1, '('));
                                                        exp.push_back(tmp[2]);
                                                        exp.push_back(tmp[3]);
                                                        exp.push_back(tmp[4]);
                                                        exp.push_back(string(1, ')'));
                                                        return exp;
                                                }
                                        }
                                }
                        } else if (op2 == '-') {
                                if (cast_coin()) {  // a * b - c
                                        if (find_good_y_for_x_minus_y(answer, c)) {
                                                collect_a_op_b_op_c(a, b, c, op1, op2, exp);
                                                return exp;
                                        }
                                } else {  // a / (b - c)
                                        int t = 1;
                                        if (find_good_y_for_x_over_y(a, t)) {
                                                if (split_a_minus_b(t, b, c)) {
                                                        vector<string> tmp;
                                                        collect_a_op_b_op_c(a, b, c, op1, op2, tmp);
                                                        exp.push_back(tmp[0]);
                                                        exp.push_back(tmp[1]);
                                                        exp.push_back(string(1, '('));
                                                        exp.push_back(tmp[2]);
                                                        exp.push_back(tmp[3]);
                                                        exp.push_back(tmp[4]);
                                                        exp.push_back(string(1, ')'));
                                                        return exp;
                                                }
                                        }
                                }
                        } else if (op2 == '*') {  // a / b * c
                                a = answer;
                                vector<int> factors;
                                get_factors(a, factors);

                                int t = factors[0];
                                split_a_times_b(t, b, c);
                                collect_a_op_b_op_c(a, b, c, op1, op2, exp);
                                return exp;
                        } else {  // a / b / c
                                vector<int> factors;
                                get_factors(b, factors);

                                int c = factors[0];
                                collect_a_op_b_op_c(a, b, c, op1, op2, exp);
                                return exp;
                        }
                }
        }
}
