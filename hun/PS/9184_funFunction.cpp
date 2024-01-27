#include <iostream>
#include <string>
#include <vector>
using namespace std;

int stored[21][21][21];

int w(int a, int b, int c){
    // cout << "w(" << a << " " << b << " " << c << ")" << endl;
    if(a <= 0 || b <= 0 || c <= 0){
        return 1;
    } 
    if(a > 20 || b > 20 || c > 20){
        return w(20,20,20);
    } 

    if(stored[a][b][c]){
        return stored[a][b][c];
    }
    
    if( a < b && b < c){ 
        stored[a][b][c] = w(a, b, c-1) + w(a, b-1, c-1) - w(a, b-1, c);
        return stored[a][b][c];
    } else{
        stored[a][b][c] = w(a-1, b, c) + w(a-1, b-1, c) + w(a-1, b, c-1) - w(a-1, b-1, c-1);
        return stored[a][b][c];
    }
}

int main(){
    // cout << w(5, 5, 1) << endl;
    string str;
    string end_point = "-1 -1 -1 ";
    getline(cin, str);
    str += " ";
    while(end_point.compare(str) != 0){
        string delim = " ";
        vector<string> words;

        size_t pos = 0;
        while((pos = str.find(delim)) != string::npos)
        {
            words.push_back(str.substr(0, pos));
            str.erase(0, pos + delim.length());
        }

        int num[3];
        for(int i = 0; i < 3; i++)
        {
            num[2-i] = stoi(words.back());
            words.pop_back();
        }
        // cout << num[0] << num[1] << num[2] << endl;
        cout << "w(" << num[0] << ", " << num[1] << ", " << num[2] << ") = ";
        cout << w(num[0], num[1], num[2]) << endl;
        getline(cin, str);
        str += " ";
    }


    return 0;
}