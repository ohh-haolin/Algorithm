#include <iostream>
using namespace std;
int f[201],n,i,j,x; //f[x]表示从1到x的距离
int main()
{
    scanf("%d",&n);
    for (i=1;i<n;i++)
        for (j=i+1;j<=n;j++)
        {
            scanf("%d",&x);
            if (f[j]==0||f[j]>f[i]+x) //如果j还没有到过或者到j的距离比原来短
                f[j]=f[i]+x; //替换
        }
    printf("%d\n",f[n]); //输出到n的距离
}