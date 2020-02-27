#include<iostream>
using namespace std;

int main(){
    int n=10;
    const int* p1=&n;
    int* p2 = (int*)p1;
    *p2 = 5;
    cout << n << endl;
    return 0;
}