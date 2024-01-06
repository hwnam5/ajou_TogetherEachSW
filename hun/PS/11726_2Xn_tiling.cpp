#include <iostream>
using namespace std;

int tile[1002];

void dp(int n)
{
    tile[1] = 1;
    tile[2] = 2;
    for(int i = 3; i <= n; i++)
    {
        tile[i] = (tile[i-1] + tile[i-2]) % 10007;
    }
}

int main()
{
    int n;
    cin >> n;

    for(int i = 0; i <= 1000; i++)
    {
        tile[i] = 0;
    }
    
    dp(n);

    cout << tile[n] << endl;

    return 0;
}