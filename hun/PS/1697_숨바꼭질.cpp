#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int n, k;
int area[100001];
int visited[100001];
queue<pair<int, int> > q;
int cnt = 0;

void init()
{
    for(int i = 0; i <= 100000; i++)
    {
        area[i] = 0;
        visited[i] = 0;
    }
}

void bfs(int s){
    visited[s] = 1;
    q.push(make_pair(s, cnt));

    while(!q.empty()){
        int ns = q.front().first;
        cnt = q.front().second;
        q.pop();
        visited[ns] = 1;
        int ns_f = ns + 1;
        int ns_b = ns - 1;
        int ns_t = 2 * ns;
        if(ns_f == k || ns_b == k || ns_t == k){
            cout << cnt + 1 << endl;
            return;
        }

        if(ns_f >= 0 && ns_f <= 100000 && visited[ns_f] == 0){
            q.push(make_pair(ns_f, cnt + 1));
        }
        if(ns_b >= 0 && ns_b <= 100000 && visited[ns_b] == 0){
            q.push(make_pair(ns_b, cnt + 1));
        }
        if(ns_t >= 0 && ns_t <= 100000 && visited[ns_t] == 0){
            q.push(make_pair(ns_t, cnt + 1));
        }
    }
}

int main()
{
    cin >> n >> k;
    init();
    if(n != k){
        bfs(n); 
    } else{
        cout << 0 << endl;
    }
    return 0;
}