#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

constexpr int MAX_N = 32768;

int N, T, ans;
int dp[MAX_N+10][5];

void solve()
{
    //初始边界
    dp[0][0] = 1;

    //枚举所有的平方数
    for(int i = 1; i*i <= MAX_N; ++i)
        //枚举所有可以转移到的数 
        for(int j = i*i; j <= MAX_N; ++j)
            //枚举当前是第几位
            for(int k = 1; k <= 4; ++k)
                //由j-i^2转移而来
                dp[j][k] += dp[j-i*i][k-1];

    cin >> T;
    for(int i = 1; i <= T; ++i)
    {  
        //还原ans
        ans = 0;

        cin >> N;
        for(int j = 1; j <= 4; ++j)
            ans += dp[N][j];
        cout << ans << '\n';
    }
}

int main()
{
    solve();
    return 0;
}