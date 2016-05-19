#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int maxn = 1e3+10;
int pkg[maxn],public_key[maxn];
int n,p,t;

int inv(int a,int m)
{
    if(a==1) return 1;
    return inv(m%a,m)*(m-m/a)%m;
}

void genarate_key(int n)
{
    for(int i=0;i<n;i++)
        scanf("%d",&pkg[i]);

    scanf("%d%d ",&t,&p);
    printf("public key:");

    for(int i=0;i<n;i++)
    {
        public_key[i] = pkg[i]*t%p;
        printf("%d ",public_key[i]);
    }
    printf("\n");

    printf("private key: ");

    printf("t^-1:%d p:%d\n",(inv(t,p)+p)%p,p);
    t = (inv(t,p)+p)%p;
}

void encrypto(const char *text,int *crypto_text,int &len)
{
    bool bin_text[8*maxn];
    memset(bin_text,0,sizeof bin_text);
    int bin_len=0,text_len = strlen(text);

    for(int i=0;i<text_len;i++)
    {
        char c = text[i];
        printf("\"%c\" ",c);
        int cnt_ = 0;
        while(c)
        {
            cnt_ ++;
            bin_text[bin_len++] = c&1;
            printf("%d",c&1);
            c >>= 1;
        }
        while(cnt_ < 8)
        {
            printf("0");
            bin_text[bin_len++] = 0;
            cnt_++;
        }
        printf("\n");
    }

    bin_len += (n-(bin_len%n))%n;
    printf("\nbin_len:%d\n",bin_len);
    for(int i=0;i<bin_len;i++)
    {
        printf("[%d,%d] ",bin_text[i],public_key[i%n]);
        if(i%n==n-1) printf("\n");
        crypto_text[i/n] += bin_text[i]*public_key[i%n];
    }

    printf("Crypto text:");
    int cnt = 0;
    while(crypto_text[cnt])
        printf("%d ",crypto_text[cnt++]);
    printf("\n");

    len = cnt;
}


/*

3*t+4*t+9*t = 85 (mod 73) = 12
12 * 23 = 57 mod 73

3+4+9 = 12*t^-1 mod 73

*/
void decrypto(const int txt_len,const int *crypto_text,char *text)
{
    bool bin_text[8*maxn];
    memset(bin_text,0,sizeof bin_text);

    for(int i=0;i<txt_len;i++)
    {
        int sum = crypto_text[i]*t%p;

        for(int k=n-1;k>=0;k--)
        {
            if(sum>=pkg[k])
            {
                sum -= pkg[k];
                bin_text[i*n+k] = true;
            }
            else
                bin_text[i*n+k] = false;
        }
        if(sum != 0)
        {
            printf("sum error!\n");
        }
    }

    int bin_len = txt_len*n;
    for(int i=0;i<bin_len;i++)
    {
        printf("%d%s",bin_text[i],i%8==7?" ":"");
        if(i%8==7)
        {
            printf(" %d\n",text[i/8]);
        }
        text[i/8] += bin_text[i]<<((i%8));
    }
    int text_len = bin_len/8;

    printf("\ntext:");
    for(int i=0;i<text_len;i++)
        printf("%c",text[i]);
    printf("\n");
}

int main()
{
    scanf("%d ",&n);
    genarate_key(n);
    char txt[maxn];
    int cry_txt[maxn] = {0};
    int cry_len = 0;
    gets(txt);
    encrypto(txt,cry_txt,cry_len);
    memset(txt,0,sizeof txt);
    decrypto(cry_len,cry_txt,txt);
}

/*
5
3 4 9 17 35
19 73
good night
*/
