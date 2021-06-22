#include <iostream>
using namespace std;


int main()
{
    unsigned T = 0;
    int a = 0, b = 0;
    
    cin >> T;
    
    for (int i = 0; i < T; i++) {

        cin >> a >> b;
        cout << a + b <<endl;
    }

    return 0;
}