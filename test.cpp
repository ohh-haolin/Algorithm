#include <iostream>
using namespace std;

struct node{
    node(){

    };
    node(int a,int b){
        this->nxt = a;
        this->var = b;
    };
    int nxt,var;
};


int main(){
    node* A = new node(1,2);
    A->nxt = 9;
    cout << A->nxt << endl;
    
    return 0;
}