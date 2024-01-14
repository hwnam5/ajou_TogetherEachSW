#include <iostream>
#include <algorithm>
using namespace std;



int main(){

    int n;
    cin >> n;
    int tri[n][n];
    int dp[n][n];
    
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < i + 1; j++){
            cin >> tri[i][j];
        }
    }

    dp[0][0] = tri[0][0];
    for(int i = 1; i < n; i++)
    {
        for(int j = 0; j < i + 1; j++){
            if(j == 0){
                dp[i][j] = dp[i-1][j] + tri[i][j];
            } else if(j == i){
                dp[i][j] = dp[i-1][j-1] + tri[i][j];
            } else {
                dp[i][j] = max(dp[i-1][j-1],dp[i-1][j]) + tri[i][j];
            }
        }
    }
    int last[n];
    for(int i = 0; i < n; i++)
    {
        last[i] = dp[n-1][i];
    }
    sort(last, last + n);
    cout << last[n-1] << endl;
    return 0;
}