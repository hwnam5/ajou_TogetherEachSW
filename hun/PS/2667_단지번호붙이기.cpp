#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int visited[26][26];
char inp[26][26];
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};
int n, cnt = 0;
queue<pair<int,int> > q;

void init()
{
    for(int i = 0; i < 25; i++)
    {
        for(int j = 0; j < 25; j++)
        {
            visited[i][j] = 0;
        }
    }
}

int range_check(int x, int y)
{
    if(x < 0) return 0;
    else if(x > n-1) return 0;
    else if(y < 0) return 0;
    else if(y > n-1) return 0;
    else{
        return 1;
    }
}

void bfs(int x, int y)
{
    q.push(make_pair(x,y));
    visited[x][y] = 1;
    cnt++;
    
    while(!q.empty()) {
        int a = q.front().first;
        int b = q.front().second;
        q.pop();
        for(int i = 0; i < 4; i++)
        {
            int nx = a + dx[i];
            int ny = b + dy[i];
            if(range_check(nx, ny) && visited[nx][ny] == 0 && inp[nx][ny] == '1'){
                q.push(make_pair(nx,ny));
                visited[nx][ny] = 1;
                cnt++;
            }
        }
    }
}

int main()
{
    cin >> n;
    init();
    for(int i = 0; i < n; i++)
    {
        cin >> inp[i];
    }
    int result[1000] = {0, };
    int r_cnt = 0;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(inp[i][j] == '1' && visited[i][j] == 0){
                cnt = 0;
                bfs(i,j);
                result[r_cnt] = cnt;
                r_cnt++;
            }
        }
    }

    sort(result, result + r_cnt);
    cout << r_cnt << endl;
    for(int i = 0; i < r_cnt; i++)
    {
        cout << result[i] << endl;
    }

    return 0;
}