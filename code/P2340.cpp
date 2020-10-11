#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

namespace io
{
    using ::std::cin;
    using ::std::cout;
    using ::std::getchar;
    using ::std::max;
    using ::std::min;
    using ::std::memset;
    using ::std::printf;
    using ::std::sort;
};
using namespace io;

const int MAX_N = 410;
const int Res = 400000;

int N;
struct Cow
{
    int iq,eq;
}cows[MAX_N];

//向右移动 MAX_N * MAX{iq or eq}
int dp[Res*2 + 20];
//优化卡常
int maxx[MAX_N], minn[MAX_N];

void solve()
{  
    //初始化dp数组
    memset(dp, ~0x3f, sizeof(dp));
    dp[Res] = 0;

    cin >> N;
    for(int i = 1; i <= N; ++i)
    {
        cin >> cows[i].iq >> cows[i].eq;
        if(cows[i].iq > 0)
			maxx[i]=maxx[i-1]+cows[i].iq,   minn[i]=minn[i-1];
        else
            maxx[i]=maxx[i-1],              minn[i]=minn[i-1]+cows[i].iq;
    }

    for(int i = 1; i <= N; ++i)
    {
        if(cows[i].iq <= 0 && cows[i].eq <= 0) continue;
        if(cows[i].iq > 0)
        {
            //正常的奶牛
            for(int j = Res + maxx[i]; j >= Res + minn[i]; --j)
                dp[j] = max(dp[j], dp[j - cows[i].iq] + cows[i].eq);
            
        }
        else
        {   //呆瓜奶牛
            for(int j = Res + minn[i]; j <= Res + maxx[i]; ++j)
                dp[j] = max(dp[j], dp[j - cows[i].iq] + cows[i].eq);
            
        }
    }

    
    int ans = 0;
    for(int i = 0; i <= Res; ++i)
    {   
        if(dp[i + Res] > 0) //必须情商大于0
            ans = max(ans, dp[i + Res] + i);
    }
    cout << ans << '\n';
}

int main()
{
    solve();
    return 0;
}