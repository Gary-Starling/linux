#include <iostream>
using namespace std;

int log2toExp(long a);

int main()
{
    int T = 0;

    cin >> T;

    int log;

    while (T--)
    {
        cin >> log;
        cout << log2toExp(log) << endl;
    }

    return 0;
}

int log2toExp(long a)
{
    int cnt = 0;

    if ((a / 2) != 1)
    {
        cnt += log2toExp(a / 2);
        return (cnt + 1);
    }
    else
        return 1;
}