#include <iostream>
using namespace std;

#define sqr(x) x * x

double square (double x);

int main()
{
    int i = 42;
    double d = 3.14;
    const char *s = "C-style string";

    int a = 0;
    double g = 0.0;
    bool flag = false;


    cout << "enter value [a] = ";
    cin >> a;
    

    cout << "You enter value [a] = " << a << "\n\n";
    cout << "This is an integer " << i << "\n\n";
    cout << "This is a double " << d << "\n";
    cout << "This is a \"" << s << "\"\n";
    cout << "value [flag] =     " << flag << "\n";
    cout << "reverse [flag]\n";
    flag = true;
    cout << "value [flag] =     " << flag << "\n";

    cout << "enter value any value to square\n";
    cin >> g;

    cout << "result square = " << square(g) << "\n";
    
    cout << sqr(3 + 0);

    return 0;
}

double square (double x) {
    return x * x;
}