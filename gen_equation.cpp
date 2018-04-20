#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <ctime>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define MODULE 100000

/**
 * type1:
 *      a op b
 * type2:
 *      a [* /] (b [+-] c)
 *      (a [+-] b) [* /] c
 *      a op b op c
 * type3:
 *      a op b op c op d
 *      a [* /] (b [+-] c) [* /] d
 *      (a [+-] b) [* /] c [+-* /] d
 */

/**
 * get random number
 */
/************************************/
char gen_operator()
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

int gen_random()  // need srand first
{
        int x;
        while ( (x = rand() % MODULE) == 0)
                ;
        return x;
}

int get_random(int m)  // need srand first
{
        int x;
        while ( (x = rand() % m) == 0)
                ;
        return x;  // x >= 1
}

bool good_divide(int a, int b)
{
        return a % b == 0;
}

int fix_divide(int& a, int& b)
{
        if (b == 0) {
                return -1;
        }
        int m = a % b;
        if (m != 0) {
                a -= m;
                a += gen_random() * b;
        }
        return 0;
}
/************************************/

vector<string> gen_type1_equa()
{
        vector<string> equa;
        int m = 0;
        int a = gen_random();
        cout << "a: " << a << endl;
        char op = gen_operator();
        int b = gen_random();
        cout << "b: " << b << endl;
        switch (op) {
                case '/':
                        if (a < b) {
                                int t = a;
                                a = b;
                                b = a;
                        }
                        m = a % b;
                        if (m != 0) {
                                a -= m;
                                a += gen_random() * b;
                        }
                        // cat equation
                        equa.push_back(to_string(a));
                        equa.push_back(string(1, op));
                        equa.push_back(to_string(b));
                        return equa;
                case '-':
                        if (a < b) {
                                int t = a;
                                a = b;
                                b = t;
                        }
                default:  // this is very easy
                        equa.push_back(to_string(a));
                        equa.push_back(string(1, op));
                        equa.push_back(to_string(b));
                        return equa;

        }
}

vector<int> gen_factors(int x)
{
        vector<int> factors;
        for (int i = 1; i < (x + 1) / 2; i++) {
                if (x % i == 0) {
                        factors.push_back(i);  // collect factors
                }
        }
        return factors;
}

bool split_num_plus(const int& x, int& a, int& b)
{
        bool ok = true;
        int a = get_random(x);  // 1 to x - 1;
        int b = x - y;

        return ok;
}

bool split_num_minus(const int& x, int& a, int& b)
{
        bool ok = true;
        int t = get_random(x);
        while (t + x > MODULE) {
                t /= 2;
        }  // x should be good
        b = x - t;

        return ok;
}

vector<string> gen_type2_equa()
{
        vector<string> equa;
        int a ;
        int b, c;
        while ( (a = gen_random()) < 9) {
                a = gen_random();
        }
        char op1 = gen_operator();
        switch (op1) {
                case '+': {
                          }
        }
        /* a op b op c */
        return equa;
}


int main()
{
        srand(time(NULL));
        vector<string> equa;
        equa = gen_type1_equa();
        for (int i = 0; i < equa.size(); i++) {
                cout << equa[i] << " ";
        }
        cout << endl;
        //cout << gen_type1_equa(1000) << endl;
        return 0;
}

