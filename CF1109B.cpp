#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;

inline ll read()
{
    ll x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10;
char s[N];

bool cmp(int l)
{
    bool f = true;
    int mid = l >> 1;
    for(int i = 1, j = mid; i <= mid; i ++ , j -- )
        if(s[i] != s[j])
        {
            f = false;
            break;
        }
    if(f && (l & 1)) return 1;
    if(f) return cmp(mid);
    if(!f && (l & 1)) return 1;
    return 0;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s", s + 1);
    int n = strlen(s + 1);
    bool flag = true;
    if((n & 1) == 0)
    {
        for(int i = 2; i <= n; i ++ )
            if(s[i] != s[i - 1])
                flag = false;
    }
    else
    {
        for(int i = 2; i <= n / 2; i ++ )
            if(s[i] != s[i - 1])
                flag = false;
        if(s[n / 2 + 2] != s[n / 2]) flag = false;
        for(int i = n / 2 + 3; i <= n; i ++ )
            if(s[i] != s[i - 1])
                flag = false;
    }
    
    if(flag) 
    {
        puts("Impossible");
        return 0;
    }

    if(cmp(n))
    {
        puts("2");
    }
    else puts("1");

    return 0;
}