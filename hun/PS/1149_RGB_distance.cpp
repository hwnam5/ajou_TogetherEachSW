#include <iostream>
#include <algorithm>
using namespace std;

int RGB[1001][3] = {0,};
int dp[1001][3] = {0,};

void dist(int n)
{
    dp[0][0] = RGB[0][0];
    dp[0][1] = RGB[0][1];
    dp[0][2] = RGB[0][2];
    
    for(int i = 1; i < n; i++)
    {
        dp[i][0] = min(dp[i-1][1], dp[i-1][2]) + RGB[i][0];
        dp[i][1] = min(dp[i-1][0], dp[i-1][2]) + RGB[i][1];
        dp[i][2] = min(dp[i-1][1], dp[i-1][0]) + RGB[i][2];
    }
}

int main(){

    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            cin >> RGB[i][j];
        }
    }
    dist(n);
    cout << min(dp[n-1][0], min(dp[n-1][1], dp[n-1][2]))<< endl;

    return 0;
}