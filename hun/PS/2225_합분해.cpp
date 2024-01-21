#include <iostream>
using namespace std;

int main(){

    int n, k;
    cin >> n >> k;
    int dp[n+1];

    for(int i = 0; i <= n; i++)
    {
        dp[i] = 1;
    }

    if(k == 1){
        cout << 1 << endl;
        return 0;
    } else if(k == 2)
    {
        cout << n+1 << endl;
        return 0;
    }

    for(int kth = 3; kth <= k; kth++)
    {
        for(int d = 0; d <= n; d++)
        {
            int sum = 0;
            for(int s = d; s <= n; s++)
            {
                sum = (sum + dp[s]) % 1000000000;
            }
            dp[d] = sum % 1000000000;
        }

        // for(int i = 0; i <= n; i++)
        // {
        //     printf("%10d", dp[i]);
        // }
        // cout << endl;
    }

    int result = 0;
    for(int i = 0; i <= n; i++)
    {
        result = (result + dp[i]) % 1000000000;
    }

    cout << result % 1000000000 << endl;

    return 0;
}