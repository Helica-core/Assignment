#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

int pow_m(int b,int n,int m)
{
    int res = 1,base = b;
    while(n)
    {
        if(n&1)
        {
            res *= base;
            res %= m;
        }
        base *= base;
        base %= m;
        n >>= 1;
    }
    return res%m;
}

int main()
{
    printf("%d\n",pow_m(29,26,71));
    int ans = 1;
    for(int i=1;i<100;i++)
    {
        ans *= 7;
        ans %= 71;
        if(ans == 3)
        {
            printf("%d",i);
            break;
        }
    }
}
