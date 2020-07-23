#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

constexpr int MAX_N = 110;

int N;
int A[MAX_N];
//dp[i][j] 从i删刀j的最小值
int dp[MAX_N][MAX_N];

void solve()
{
    cin >> N;
    for(int i = 1; i <= N; ++i)
    {
        cin >> A[i];
        dp[i][i] = A[i];
    }

    // // 枚举右端点
    for(int j = 2; j <= N; ++j)
        // 枚举左端点
        for(int i = j-1; i > 0; --i)
        {
            //直接求得一个基础值
            dp[i][j] = abs(A[i]-A[j]) * (j-i+1);
            
            //枚举断点
            for(int k = i; k < j; ++k)
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[k+1][j]);
        }


    cout << dp[1][N] << '\n';h
{
    solve();
    return 0;
}