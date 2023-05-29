#include <iostream>

using namespace std;

void foo(int& a)
{
    cout << a << endl;
}

void foofoo()
{
    int a=10;
    foo(a);
}

int  main()
{
    int a=5;

    foo(a);
    foofoo();

    return 0;
}