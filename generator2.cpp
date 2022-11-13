#include <bits/stdc++.h>
using namespace std;

int main()
{
    srand((unsigned)time(NULL));
    freopen("input6.txt", "w", stdout);
    int n = 1000;
    cout << n << endl;
    cout << (n * (n - 1)) / 2 << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            cout << i << " " << j << " " << rand() << endl;
        }
    }
    return 0;
}