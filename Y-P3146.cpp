#include <iostream>
#include <cstdio>
#include <algorithm>

namespace io
{
    using ::std::cin;
    using ::std::cout;
    using ::std::max;

    using uint = unsigned int;
};
using namespace io;

uint const MAX_N = 260;

uint N;
uint dp[MAX_N][MAX_N];
uint ans;

void solve()
{
    cin >> N;
    for(uint i = 1; i <= N; ++i)
    {
        cin >> dp[i][i];
    }    

    //枚举区间长度
    for(uint len = 2; len <= N; ++len)
    {
        //枚举左端点和算出右端点
        for(uint left = 1, right = len; right <= N; ++left, ++right)
        {
            //枚举断点
            for(uint k = left; k <= right; ++k)
                //如果相同则合并
                    if(dp[left][k] == dp[k+1][right])
                    {
                        dp[left][right] = max(dp[left][right], dp[left][k]+1);
                        ans = max(ans, dp[left][right]);
                    }
        }
    }

    cout << ans << '\n';
}

int main()
{
    solve();
    return 0;
}

