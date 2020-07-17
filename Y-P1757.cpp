#include <iostream>
#include <cstdio>

namespace io
{
    using ::std::cin;
    using ::std::cout;
    using ::std::max;

    using uint = unsigned int;
}
using namespace io;

const uint MAX_N = 1010;

uint N, M;
uint dp[MAX_N];

struct Object
{
    // weight value
    uint w,v;
}obj[MAX_N];

uint grp[MAX_N][MAX_N];
uint tmp;

void solve()
{
    cin >> M >> N;
    for(uint i = 1; i <= N; ++i)
    {
        cin >> obj[i].w >> obj[i].v >> tmp;
        //保存节点编号
        ++grp[tmp][0]; grp[tmp][grp[tmp][0]]  = i;
        //保存总组数
        grp[0][0] = max(grp[0][0], tmp);
    }

    for(uint i = 1; i <= grp[0][0]; ++i)
    {
        for(int j = M; j >= 0; --j)
        {
            for(uint k = 1; k <= grp[i][0]; ++k)
                {
                    //如果包里放得下
                    if(j >= obj[grp[i][k]].w)
                    {
                        dp[j] = max(dp[j], dp[j - obj[grp[i][k]].w] + obj[grp[i][k]].v);
                    }                
                }
        }
    }
    cout << dp[M] << '\n';

}


int main()
{
    solve();
    return 0;
}