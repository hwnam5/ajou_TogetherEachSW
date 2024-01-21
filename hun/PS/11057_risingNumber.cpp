#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;

    int dp[10];
    for(int i = 0; i <= 9; i++)
    {
        dp[i] = 1;
    }

    for(int c = 0; c < n-1; c++)
    {
        for(int i = 0; i <= 9; i++)
        {
            int sum = 0;
            for(int k = i; k <= 9; k++)
            {
                sum += dp[k];
            }
            dp[i] = sum % 10007;
        }
    }
    int result = 0;
    for(int i = 0; i <= 9; i++)
    {
        result += dp[i];
    }
    cout << result % 10007 << endl;

}