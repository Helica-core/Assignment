#include <cstdio>

int inv(int a,int m)
{
    if(a==1) return 1;
    return inv(m%a,m)*(m-m/a)%m;
}

int main()
{
    int n,p;
    scanf("%d%d",&n,&p);
    printf("inv:%d\n",inv(n,p));
}
