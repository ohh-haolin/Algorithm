#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string.h>

namespace io
{
    using ::std::cin;
    using ::std::cout;
    using ::std::endl;
    using ::std::max;
    using ::std::sort;

    typedef unsigned int uint;
}

using namespace io;

uint N, W;
uint ws[20];
uint sts[1<<18];    //每个电梯状态的最少情况，最终答案为    (1<<18) - 1
uint elv[1<<18];    //状态中，最后一个电梯的剩余空间

void solve()
{
    cin >> N >> W;
    for(uint i = 1; i <= N; ++i)
        cin >> ws[i];
    
    memset(sts, 0x3f, sizeof(sts));
    sts[0] = 1; //无论如何都要使用一个
    elv[0] = W; //对应上面

    //枚举所有状态
    for(int i = 0; i < (1<<N); ++i)
    {
        for(uint j = 1; j <= N; ++j)
        {   
            //牛已经在里面
            if(i & (1 <<(j-1)))  continue;

            //如果放得下，并且比之前的结果更好
            if(elv[i] >= ws[j] && sts[i | (1 << (j-1))] > sts[i])
            {   
                //转移
                sts[i | (1 << (j-1))] = sts[i];
                //因为sts的变化，elv必须变
                elv[i | (1 << (j-1))] = elv[i] - ws[j];
            }
            //如果放得下，并且当前结果和之前结果一样好
            else if(elv[i] >= ws[j] && sts[i | (1 << (j-1))] == sts[i])
            {
                //一样好 sts无需转移
                //elv 转移为更大的保证最优情况
                elv[i | (1 << (j-1))] = max(elv[i] - ws[j], elv[i | (1 << (j-1))]);
            }
            //如果塞不下，并且比之前结果好
            else if(elv[i] < ws[j] && sts[i | (1 << (j-1))] > sts[i] + 1)
            {
                //开一个新的
                sts[i | (1 << (j-1))] = sts[i] + 1;
                //因为sts的变化，elv必须变
                elv[i | (1 << (j-1))] = W - ws[j];
            }
            //如果塞不下，并且结果比之前的一样好
            else if(elv[i] < ws[j] && sts[i | (1 << (j-1))] > sts[i] + 1)
            {
                //一样好 sts无需转移
                //elv 转移为更大的保证最优情况
                elv[i | (1 << (j-1))] = max(W - ws[j], elv[i | (1 << (j-1))]);
            }
        }
    }

    cout << sts[(1 << N) - 1] << endl;
}

int main()
{
    solve();
    return 0;
}
