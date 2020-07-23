#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

constexpr int MAX_N = 10010;

int N, K;
vector<int> mins[MAX_N];
int dp[MAX_N];

void solve()
{
    cin >> N >> K;
    int tmp1, tmp2;
    for(int i = 1; i <= K; ++i)
    {
        cin >> tmp1 >> tmp2;
        mins[tmp1].push_back(tmp2);
    }

    for(int i = N; i > 0; --i)
    {
        if(mins[i].empty())
        {
            dp[i] = dp[i+1] + 1;
            continue;
        }

        for(size_t j = 0; j < mins[i].size(); ++j)
        {
            dp[i] = max(dp[i], dp[i + mins[i][j] ]);
        }
        
    }

    cout << dp[1] << '\n';
}


int main()
{
    solve();
    return 0;
}