#include <iostream>
#include <algorithm>
#include <cstdio>

namespace io
{
    using ::std::cin;
    using ::std::cout;
    using ::std::max;
}
using namespace io;

const int MAX_N = 1010;

int N,X;

struct cr
{
    int loss, win, use;
}cr[MAX_N];

int dp[MAX_N];


void solve()
{
    cin >> N >> X;
    for(int i = 1; i <= N; ++i)
        cin >> cr[i].loss >> cr[i].win >> cr[i].use;

    for(int i = 1; i <= N; ++i)
    {
        //我的子弹比当前的对手多
        //01背包所以倒叙，二维压一维
        for(int j = X; j >= cr[i].use; --j)
        {
            dp[j] = max(dp[j]+cr[i].loss, dp[j-cr[i].use] + cr[i].win);
        }
        //子弹比对手少
        for(int j = cr[i].use-1; j >= 0; --j)
        {
            int tmp = cr[i].loss;
            dp[j] += tmp;
        }
    }
    cout << 5ll*dp[X] << '\n';
}


int main()
{
    solve();
    return 0;
}