#include <iostream>
using namespace std;

int main()
{

    char c = '\0';
    int cnt = 0;

    while (cin.get(c))
    {

        if (c == ' ')
        {
            cnt++;

            if (cnt < 2)
                cout << c;
        }
        else
        {
            cout << c;
            cnt = 0;
        }
    }

    return 0;
}