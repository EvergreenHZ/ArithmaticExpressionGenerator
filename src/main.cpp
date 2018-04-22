#include "ArithmaticExpression.h"
#include "Evaluation.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
using namespace std;

int main()
{
        ArithmaticExpression ins(10000);
        Evaluation eval;

        for (int i = 0; i < 10; i++) {
                vector<string> exp;
                exp = ins.gen_a_op_b_op_c();
                string s;
                for (int j = 0; j < exp.size(); j++) {
                        cout << exp[j] << " ";
                        s += exp[j];
                }  cout << endl;
                if (s.empty()) {
                        continue;
                }
                cout << eval.solution(s) << endl;
        }
        return 0;
}
