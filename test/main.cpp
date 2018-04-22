#include "ArithmaticExpression.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
using namespace std;

int main()
{
        ArithmaticExpression ins(10000);

        for (int i = 0; i < 10; i++) {
                vector<string> exp;
                exp = ins.gen_a_op_b_op_c();
                for (int j = 0; j < exp.size(); j++) {
                        cout << exp[j] << " ";
                }  cout << endl;
        }

        return 0;
}
