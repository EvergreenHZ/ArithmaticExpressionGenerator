#include <iostream>
using namespace std;

int main()
{
        cout << "#pragma once"<<endl;
        cout << "namespace huaizhi {" << endl <<
                "const static int NUMBER_TABLE[100000] = {"<<endl;
        for (int i = 0; i < 100000; i++) {
                cout << i <<", ";
        }
        cout << "};"<<endl<<"}"<<endl;

        return 0;
}

