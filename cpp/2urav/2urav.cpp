#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    int a, b, c;
    double D = 0.0;
    double x1 = 0.0, x2 = 0.0;

    cin >> a >> b >> c;
    D = pow(b, 2) - (4 * a * c);

    if (D > 0.0) // 2 корня
    {
        x1 = ((-b) + sqrt(D)) / (2 * a); 
        x2 = ((-b) - sqrt(D)) / (2 * a); 
        cout << x1 << " " << x2  << endl;
    }
    else if (D == 0.0) // 1 корень
    {
        x1 = x2 = ((-1 * b) + sqrt(D)) / 2 * a; 
        cout << x1 << " " << x2  << endl;
    }
    else // Корней нет
    {
        cout << "No real roots" << endl;
    }

    return 0;
}