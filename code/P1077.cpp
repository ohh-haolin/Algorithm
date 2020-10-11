#include <algorithm>
#include <iostream>

namespace io
{
    using ::std::cin;
    using ::std::cout;
    using ::std::endl;
    using ::std::min;

    typedef unsigned int uint;
}
using namespace io;

const int MOD = 1000007;
int A[110];
int N, M;
//dp[i][j]  前i束花总共占据了j个位置
int dp[110][110];


void solve()
{
    cin >> N >> M;
    for(int i = 1; i <= N; ++i)
        cin >> A[i];
    
    //不放花也有一种情况
    dp[0][0] = 1;
    for(int i = 1; i <= N; ++i)
        for(int j = 0; j <= M; ++j)
            for(int k = 0; k <= min(j, A[i]); ++k)
            {
                dp[i][j] = (dp[i][j] + dp[i-1][j-k]) % MOD;
            }

    cout << dp[N][M] << endl;
}

int main()
{
    solve();
    return 0;
}