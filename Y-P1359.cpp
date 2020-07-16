#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

namespace io
{
    using ::std::cin;
    using ::std::cout;
    using ::std::min;
    using ::std::memset;

    using uint = unsigned int;
}
using namespace io;

const uint MAX_N = 210;

uint N;
uint rent[MAX_N][MAX_N];
uint dp[MAX_N];

uint tmp;

void solve()
{
    cin >> N;
    
    memset(dp, 0x3f, sizeof(dp));
    dp[1] = 0;

    for(uint i = 1; i < N; ++i)
    {
        for(uint j = i+1; j <= N; ++j)
        {
            cin >> rent[i][j];
            // cout << "i:" << i << "j:" << j << "\t value:" << rent[i][j] <<'\n';
        }
    }


    for(uint i = 1; i <= N; ++i)
        for(uint j = 1; j < i; ++j)
            dp[i] = min(dp[i], dp[j]+rent[j][i]);
        
    cout << dp[N] << '\n';
}

int main()
{
    solve();
    return 0;
}