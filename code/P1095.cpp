#include <algorithm>
#include <iostream>

namespace io
{
    using ::std::cout;
    using ::std::cin;
    using ::std::endl;
    using ::std::max;
    typedef unsigned int uint;
}
using namespace io;

uint dp[300001];
uint M, S, T;

void solve()
{
    cin >> M >> S >> T;
    //只闪现
    for(uint i = 1; i <= T; ++i)
    {
        if(M >= 10)
        {
            dp[i] = dp[i - 1] + 60;
               M -= 10; 
        }else
        {
            dp[i] = dp[i - 1];
            M += 4;
        }
    }

    //只跑步
    for(uint i = 1; i <= T; ++i)
    {
        dp[i] = max(dp[i], dp[i-1]+17);
        if(dp[i] >= S)
        {
            cout << "Yes" << '\n' << i << endl;
            return;
        }
    }

    cout << "No" << '\n' << dp[T] << endl;
}


int main() {
    solve();
    return 0;
}