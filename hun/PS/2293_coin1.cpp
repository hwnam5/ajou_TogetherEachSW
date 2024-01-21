#include <iostream>
using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;
    int coin[n];
    for(int i = 0; i < n; i++)
    {
        cin >> coin[i];
    }
    int dp[k + 1];
    for(int i = 0; i <= k; i++)
    {
        dp[i] = 0;
    }
    dp[0] = 1;
    
    for(int i = 0; i < n; i++)
    {
        for(int y = coin[i]; y <= k; y++)
        {
            dp[y] += dp[y - coin[i]];
        }
    }
    cout << dp[k] << endl;

    return 0;
}