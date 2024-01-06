#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int dp[302];
int arr[302];

void up_stair(int n)
{
    dp[1] = arr[1];
    dp[2] = arr[1] + arr[2];
    dp[3] = max(arr[1] + arr[3], arr[2] + arr[3]);
    
    for(int i = 4; i <= n; i++)
    {
        dp[i] = max(dp[i-2] + arr[i], dp[i-3] + arr[i-1] + arr[i]);
    }
}

int main(){
    int n;
    cin >> n;

    for(int i = 1; i <= n; i++)
    {
        cin >> arr[i];
        dp[i] = 0;
    }
    
    up_stair(n);

    cout << dp[n] << endl;

    return 0;
}