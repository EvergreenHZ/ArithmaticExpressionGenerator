#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include "ArithmaticExpression.h"
using namespace std;


/* MODULE should be good enough */
ArithmaticExpression::ArithmaticExpression(int module): MODULE(module)
{
        if (module < 10) {  // make sure MODULE is good
                MODULE = 10000;
        }
        for (int i = 1; i < MODULE - 1; i++) {
                sequence.push_back(i);
        }
        random_shuffle(sequence.begin(), sequence.end());
        srand(time(NULL));  // initialize seed
}

bool ArithmaticExpression::cast_coin()
{
        random_shuffle(sequence.begin(), sequence.end());
        if ( (rand() % 2) == 0) {
                return false;
        } else {
                return true;
        }
}

int ArithmaticExpression::gen_random()
{
        //srand(time(NULL));
        int x;
        //while ( (x = sequence[rand() % (MODULE - 1)]) == 0) {  // bad number
        //        random_shuffle(sequence.begin(), sequence.end());
        //}
        x = sequence[rand() % (MODULE - 1)];
        random_shuffle(sequence.begin(), sequence.end());
        //x = sequence[rand() % (MODULE - 1)];
        x = sequence[x];
        return x;  // 1 <= x <= MODULE - 1
}

int ArithmaticExpression::get_random(int module)
{
        int x;
        x = sequence[rand() % (MODULE - 1)];
        random_shuffle(sequence.begin(), sequence.end());
        //x = sequence[rand() % (MODULE - 1)];
        x = sequence[x];
        //random_shuffle(sequence.begin(), sequence.end());
        //x = sequence[rand() % (MODULE - 1)];
        //while ( (x = rand() % module) == 0) {  // bad number
        //        random_shuffle(sequence.begin(), sequence.end());
        //}
        return x;  // 1 <= x <= module - 1
}

char ArithmaticExpression::gen_operator()
{
        int coin = rand() % 4;
        switch (coin) {
                case 0:
                        return '+';
                case 1:
                        return '-';
                case 2:
                        return '*';
                case 3:
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
        for (int i = 1; i < (n + 1) / 2; i++) {  // n >= 1
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

/* generate a + b */
bool ArithmaticExpression::a_plus_b(vector<string> &exp)
{
        int a, b;
        a = gen_random();  // a >= 1
        cast_coin();
        b = gen_random();  // b >= 1
        //cout << a << " " << b <<endl;
        if (a < b) {
                int t = a;
                a = b;
                b = a;
        }
        // a >= b
        while (a + b > MODULE) {
                if (cast_coin()) {
                        a = (a + 1) / 2;
                } else {
                        b = (b + 1) / 2;
                }
        }

        if (cast_coin()) {
                int t = a;
                a = b;
                b = t;
        }

        string aa, bb;
        int_to_string(a, aa);
        int_to_string(b, bb);
        string op(1, '+');
        /* exp: a + b */
        exp.push_back(aa);
        exp.push_back(op);
        exp.push_back(bb);

        return true;
}

/* generate a - b */
bool ArithmaticExpression::a_minus_b(vector<string> &exp)
{
        int a, b;
        a = gen_random();  // a >= 1
        cast_coin();
        b = gen_random();  // b >= 1
        //cout << a << " " << b <<endl;
        if (a < b) {
                int t = a;
                a = b;
                b = t;
        }
        //cout << a << " " << b <<endl;

        string aa, bb;
        int_to_string(a, aa);
        int_to_string(b, bb);
        string op(1, '-');
        /* exp: a - b */
        exp.push_back(aa);
        exp.push_back(op);
        exp.push_back(bb);

        return true;
}

bool ArithmaticExpression::a_times_b(vector<string> &exp)
{
        int a, b;
        a = gen_random();  // a >= 1
        cast_coin();
        b = gen_random();  // b >= 1
        if (a < b) {
                int t = a;
                a = b;
                b = t;
        }

        while ( (a * b > MODULE)) {
                if (cast_coin()) {
                        a = (a + 1) / 2;
                } else {
                        b = (b + 1) / 2;
                }
        }

        string aa, bb;
        int_to_string(a, aa);
        int_to_string(b, bb);
        string op(1, '*');
        /* exp: a * b */
        exp.push_back(aa);
        exp.push_back(op);
        exp.push_back(bb);

        return true;
}

bool ArithmaticExpression::a_over_b(vector<string> &exp)
{
        int a, b;
        a = gen_random();  // a >= 1
        cast_coin();
        b = gen_random();  // b >= 1
        if (a < b) {
                int t = a;
                a = b;
                b = t;
        }


        vector<int> factors;
        get_factors(a, factors);
        b = factors[0];

        string aa, bb;
        int_to_string(a, aa);
        int_to_string(b, bb);
        string op(1, '/');
        /* exp: a / b */
        exp.push_back(aa);
        exp.push_back(op);
        exp.push_back(bb);

        return true;
}

/* a op b is ok */
bool ArithmaticExpression::gen_a_op_b(vector<string> &exp)
{
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
        return true;
}

bool ArithmaticExpression::good_enough(const int n)
{
        if (n < 7) {
                return false;
        }
        return true;
}

/* the next four functinos is to split c */
/********************************************************************/
bool ArithmaticExpression::split_a_plus_b(const int c, int &a, int &b)
{
        if (!good_enough(c)) {
                return false;
        } else {
                int x;
                while ( (x = get_random(c)) == 0) {
                        ;
                }
                a = x;
                b = c - a;
        }
        return true;
}

bool ArithmaticExpression::split_a_minus_b(const int c, int &a, int &b)
{
        /* c should not be too small or too large */
        if (!good_enough(c)) {
                return false;
        } else {
                int i = 0;
                while (a > MODULE && i < 100) {
                        i++;
                        b = get_random(c);
                        a = c + b;
                }
                if (i >= 100) {
                        return false;
                }
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
/*********************************************************************/

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

/* the next four are find good y */
/***********************************************************************/
bool ArithmaticExpression::find_good_y_for_x_times_y(const int x, int &y)
{
        if (!good_enough(x)) {
                return false;
        } else {
                y = gen_random();
                while ( (y * x > MODULE)) {
                        y = (y + 1) / 2;
                }  // y >= 1
                return true;
        }
}

bool ArithmaticExpression::find_good_y_for_x_over_y(const int x, int &y)
{
        if (!good_enough(x)) {  // x >= 7
                return false;
        } else {
                vector<int> factors;
                get_factors(x, factors);
                y = factors[0];  // y >= 1
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
                        y = (y + 1) / 2;
                }  // y >= 1
                return true;
        }
}

bool ArithmaticExpression::find_good_y_for_x_minus_y(const int x, int &y)
{
        if (!good_enough(x)) {
                return false;
        } else {
                y = get_random(x);  // y >= 1 && y <= x - 1
                return true;
        }
}
/************************************************************************/

/* if return value is empty, not succeed */
vector<string> ArithmaticExpression::gen_a_op_b_op_c()
{
        vector<string> exp;
        char op1, op2;
        int a, b, c;
        string aa, bb, cc;
        string str_op1, str_op2;

        int answer = gen_random();

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
