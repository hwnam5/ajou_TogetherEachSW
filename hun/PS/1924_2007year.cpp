#include <iostream>
#include <string>
using namespace std;

int main(){
    int m, d;
    cin >> m >> d;

    int days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int day = 0;
    string week[7] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};

    for(int i = 0; i < m-1; i++)
    {
        day += days[i];
    }
    day += d-1;
    cout << week[day % 7] << endl;

    return 0;
}