#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string.h>

#define force_inline __attribute__((always_inline)) inline 

namespace io
{
    using ::std::cin;
    using ::std::cout;
    using ::std::min;

    typedef unsigned int uint;

    struct Input
    {
        template<typename T>
        force_inline static T& read(T& x)
        {
            char ch = getchar();
            int sign = 1;
            T ans = 0;

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
            x = ans;
            return x;
        }

        template<typename T>
        force_inline Input& operator >> (T& x)
        {
            read(x);
            return *this;
        }

    }input;


    template<typename T>
    force_inline T myMin(const T& a, const T& b, const T& c = ::std::numeric_limits<T>::max())
    {
        return a < b ? a < c ? a : c : b < c ? b : c;
    }
}
using namespace io;

const uint MAX_N = 10010;
const uint MAX_M = 1010;

uint N, M, K;

struct Pos
{
    uint x,y,l,h;
    bool isTubed;
}poss[MAX_N];

uint dp[MAX_N][MAX_M*2];

uint tmp;

void solve()
{
    input >> N >> M >> K;
    for(uint i = 1; i <= N; ++i)
        input >> poss[i].x >> poss[i].y;
        
    for(uint i = 1; i<= K; ++i)
    {
        input >> tmp >> poss[tmp].l >> poss[tmp].h;
        poss[tmp].isTubed = true;
    }

    memset(dp, 0x3f, sizeof(dp));

    for(uint i = 1; i <= M; ++i)
        dp[0][i] = 0;   //可从任意位置出发
    
    for(uint i = 1; i <= N; ++i){
        //通过向上跳得到的，上一秒向上跳，这一秒向上跳
        for(uint j = poss[i].x+1; j <= poss[i].x+M; ++j)
            dp[i][j / M ? M : j] = j <= M ? myMin(dp[i-1][j-poss[i].x]+1, dp[i][j-poss[i].x]+1) :
                                            //处理超过天花板的情况
                                            myMin(dp[i-1][j-poss[i].x]+1, dp[i][j-poss[i].x]+1, dp[i][M]);

        //下降的情况，这一秒不动，或者上一秒下降
        for(uint j = 1; j <= M-poss[i].y; ++j)
            dp[i][j] = myMin(dp[i][j], dp[i-1][j+poss[i].y]);

        //如果有柱子且撞到柱子，处理成极大值
        if(poss[i].isTubed)
        {
            for(uint j = 1; j <= poss[i].l; ++j)
                dp[i][j] = 0x3f3f3f;
            for(uint j = M; j >= poss[i].h; --j)
                dp[i][j] = 0x3f3f3f;
        }
    }

    //cout << "finish" << '\n';

    uint ans = 0x3f3f3f;
    for(uint i = 1; i <= M; ++i)
        ans = myMin(ans, dp[N][i]);
    
    //有答案，直接输出
    if(ans < 0x3f3f3f)
    {
        cout << 1 << '\n' << ans << '\n';
        return;
    }

    //没答案统计柱子
    uint i,j;
    for(i = N; i >= 1; --i)
    {
        for(j = 1; j <= M; ++j){
            if(dp[i][j] < 0x3f3f3f) break;
        }
        if(j <= M) break;
        
    }
	ans = 0;
    for(j = 1; j <= i; ++j){
        if(poss[j].isTubed)
            ++ans;
    }
    
    cout << 0 << '\n' << ans << '\n';
}

int main()
{
    solve();
    return 0;
}