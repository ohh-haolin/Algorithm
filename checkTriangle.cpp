#include <cstdio>
#include <iostream>
using namespace std;

int n, a[100];

bool check(int a, int b, int c) {
    if (a + b > c) return true;
    if (b + c > a) return true;
    if (a + c > b) return true;

    return false;
}

void solve() {

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

    int ans = 0;

    for (int i = 1; i <= n-2; i++)
        for (int j = i+1; j <= n-1; j++)
            for (int k = j; k <= n; k++) 
                if (check(i, j, k)) {
                    ans = ans > k + j + i ? ans : k + j + i;
                };
            
  printf("%d",ans);

}

int main() { solve(); }