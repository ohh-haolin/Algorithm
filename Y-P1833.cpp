#include <algorithm>
#include <stdio.h>

namespace io
{
    using ::std::max;

    typedef unsigned int uint;
}

using namespace io;

uint dp[1010];
uint tc,c,ts;
uint t1_h, t1_t, t2_h, t2_t, N;


void solve()
{
    scanf("%d:%d %d:%d %d", &t1_h, &t1_t, &t2_h, &t2_t, &N);
    uint time = (t2_h - t1_h) * 60 + (t2_t - t1_t);

    for(int i = 1; i <= N; ++i)
    {
        scanf("%d%d%d", &tc, &c, &ts);
        if(ts == 0) //完全背包
        {
            for(int j = tc; j <= time; ++j)
                dp[j] = max(dp[j], dp[j-tc] + c);   //之前状态+当前的美学值就是当前的值
        }
        else    //多重背包
        {
            for(int j = 1; j <= ts; ++j)
                for(int k = time; k >= tc * j; --k)
                {
                    dp[k] = max(dp[k], dp[k - tc] + c);
                }
        }
        
    }

    printf("%d\n", dp[time]);
}


int main()
{
    solve();
    return 0;
}