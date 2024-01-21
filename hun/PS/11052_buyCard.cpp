#include <iostream>
#include <algorithm>
using namespace std;

int main(){

    int n;
    cin >> n;
    int dp[n + 1];
    for(int i = 1; i <= n; i++)
    {
        cin >> dp[i];
    }

    if(n == 1){
        cout << dp[1] << endl;
        return 0;
    }

    for(int i = 2; i <= n; i++)
    {
        int tempNum = i/2;
        int temp[tempNum + 1];
        temp[0] = dp[i];
        for(int j = 1; j <= tempNum; j++)
        {
            temp[j] = dp[i - j] + dp[j];
        }
        sort(temp, temp + tempNum + 1);
        // for(int k = 0; k < tempNum + 1; k++)
        // {
        //     cout << temp[k] << " ";
        // }
        // cout << endl;
        dp[i] = temp[tempNum];
    }

    cout << dp[n] << endl;

    return 0;
}