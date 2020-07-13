#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string.h>

#define force_inline __attribute__((always_inline)) inline 

namespace io
{
    using ::std::cout;
    using ::std::min;

    typedef unsigned int uint;

    struct Input
    {
        template<typename T>
        force_inline static T& read(T& ans)
        {
            char ch = getchar();
            int sign = 1;

            while(ch < '0' || ch > '9')
            {
                ch=='-' ? sign = -1 : ch;
                ch = getchar();
            }
            while(ch >= '0' && ch <= '9')
            {
                ans = (ans << 3) + (ans << 1) + (ch ^ 48);
                ch = getchar();
            }
            ans *= sign;
            return ans;
        }

        template<typename T>
        force_inline Input& operator >> (T& x)
        {
            read(x);
            return *this;
        }

    }input;

}
using namespace io;

const uint MAX_N = 10010;
const uint MAX_M = 1010;

uint N, M, K;

struct Pos
{
    uint x,y;
}poss[MAX_N];

struct Tube
{
    uint p, l, h ;
}tubes[MAX_N];

bool isTubed[MAX_M];

uint dp[MAX_N][MAX_M*2];

void solve()
{
    Input::read(N), Input::read(M), Input::read(K);
    
    for(uint i = 1; i <= N; ++i)
        Input::read(poss[i].x), Input::read(poss[i].y);
    for(uint i = 1; i<= K; ++i)
        Input::read(tubes[i].p), ++(Input::read(tubes[i].l)), --(Input::read(tubes[i].h)), isTubed[tubes[i].p] = true;

    memset(dp, 0x3f, sizeof(dp));
    //cout << tubes[K].h << '\n';

    for(uint i = 1; i <= M; ++i)
        dp[0][i] = 0;   //可从任意位置出发
    
    for(uint i = 1; i <= N; ++i){
        //通过向上跳得到的，上一秒向上跳，这一秒向上跳
        for(uint j = poss[i].x+1; j <= poss[i].x+M; ++j)
            dp[i][j] = min(dp[i-1][j-poss[i].x]+1, dp[i][j-poss[i].x]+1);
        

        //处理超过天花板的情况
        for(uint j = M+1; j <= poss[i].x+M; ++j)
            dp[i][M] = min(dp[i][M], dp[i][j]);
        
        
        //下降的情况，这一秒不动，或者上一秒下降
        for(uint j = 1; j <= M-poss[i].y; ++j)
            dp[i][j] = min(dp[i][j], dp[i-1][j+poss[i].y]);
        

        //如果有柱子且撞到柱子，处理成极大值
        if(isTubed[i])
        {
            for(uint j = 1; j < tubes[i].l; ++j)
                dp[i][j] = 0x3f3f3f;
            for(uint j = M; j > tubes[i].h; --j)
                dp[i][j] = 0x3f3f3f;
        }
        
    }

    //cout << "finish" << '\n';

    uint ans = 0x3f3f3f;
    for(uint i = 1; i <= M; ++i)
        ans = min(ans, dp[N][i]);
    
    //有答案，直接输出
    if(ans < 0x3f3f3f)
    {
        cout << 1 << '\n' << ans << '\n';
        return;
    }

    //没答案，找到最远端
    for(int i = N; i >= 1; --i)
    {
        bool flag = false;
        for(int j = M; j >= 1; --j)
            if(dp[i][j] < 0x3f3f3f)
            {
                flag = true;
                ans = i;
                break;
            }
        if(flag) break;
    }

    for(int i = ans, ans = 0; i >= 1; --i)
        if(isTubed[i])  ++ans;
    
    cout << 0 << '\n' << ans << '\n';
}

int main()
{
    solve();
    return 0;
}