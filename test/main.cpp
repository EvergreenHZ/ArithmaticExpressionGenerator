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

        //for (int i = 0; i < 10; i++) {
        //        cout << rand() % 10000 <<endl;
        //}

        //cout << "MODULE: " <<ins.MODULE<<endl;
        for (int i = 0; i < 10; i++) {
                vector<string> exp;
                ins.gen_a_op_b(exp);
                for (int j = 0; j < exp.size(); j++) {
                        cout << exp[j] << " ";
                }  cout << endl;
                //exp.clear();
        }

        return 0;
}
