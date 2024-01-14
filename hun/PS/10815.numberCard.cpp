#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> n_card;
vector<int> m_card;

int bin_search(int s, int e, int v)
{
    while(s <= e){
        int i = (s + e) / 2;
        if(v == n_card[i]){
            return 1;
        } else if(v > n_card[i]){
            s = i + 1;
        } else{
            e = i - 1;
        }
    }
    return -1;
}


int main()
{
    int n, m;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        n_card.push_back(x);
    }
    cin >> m;
    for(int i = 0; i < m; i++)
    {
        int x;
        cin >> x;
        m_card.push_back(x);
    }

    sort(n_card.begin(), n_card.end());
    
    for(int i = 0; i < m; i++)
    {
        if(bin_search(0, n-1, m_card[i]) == 1){
            cout << 1 << " ";
        } else{
            cout << 0 << " ";
        }
    }

    return 0;
}