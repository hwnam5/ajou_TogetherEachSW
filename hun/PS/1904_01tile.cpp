#include <iostream>
#include <algorithm>
using namespace std;

int tile[1000001];

void fib(int f){
    tile[1] = 1;
    tile[2] = 2;
    for(int i = 3; i <= f; i++)
    {
        tile[i] = (tile[i-1] + tile[i-2]) % 15746;
    }
}

int main(){

    int n;
    cin >> n;
    
    fib(n);
    cout << tile[n] << endl;

    return 0;
}