#include <iostream>
#include <queue>
#include <vector>
using namespace std;

queue <vector<int> > q;
int n, m;

void promising(vector<int> v)
{
    int size = v.size();

    if(size == m){
        //print & return;
        for(int i = 0; i < m; i++)
        {
            cout << v[i] << " ";
        }
        cout << "\n";
        return;
    }

    for(int i = 1; i <= n; i++)
    {
        // int varified = 1;
        // for(int s = 0; s < size; s++){
        //     if(v[s] == i){
        //         varified = 0;
        //     }
        // }
        // if(varified == 1){
        //     vector<int> add(v);
        //     add.push_back(i);
        //     q.push(add);
        // }
        vector<int> add(v);
        add.push_back(i);
        q.push(add);
    }
}

int main(){
    cin >> n >> m;

    for(int i = 1; i <= n; i++)
    {
        vector<int> v;
        v.push_back(i);
        q.push(v);
    }

    while(!q.empty()){
        int qsize = q.size();
        //cout << "q_size : " << qsize << endl;
        for(int i = 0; i < qsize; i++)
        {
            vector<int> t = q.front();
            q.pop();
            promising(t);

        }
    }
    
    return 0;
}