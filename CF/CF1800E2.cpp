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
char s1[N], s2[N];
int cnt1[150], cnt2[150];
int n, k;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- )
    {
        bool flag = false;
        memset(cnt1, 0, sizeof cnt1);
        memset(cnt2, 0, sizeof cnt2);

        n = read(), k = read();
        scanf("%s%s", s1 + 1, s2 + 1);

        for(int i = 1; i <= n; i ++ )
        {
            cnt1[s1[i]] ++;
            cnt2[s2[i]] ++;
        }

        for(int i = 0; i <= 128; i ++ )
            if(cnt1[i] != cnt2[i])
            {
                flag = true;
                break;
            }

        if(k >= n)
        {
            for(int i = 1; i <= n; i ++ )
                if(s1[i] != s2[i])
                {
                    flag = true;
                    break;
                }
        }
        
        // if(k == n - 1)
        // {
        //     for(int i = 2; i < n; i ++ )
        //         if(s1[i] != s2[i])
        //         {
        //             flag = true;
        //             break;
        //         }
        // }

        // if(k == n - 2)
        // {
        //     for(int i = 3; i < n - 1; i ++ )
        //         if(s1[i] != s2[i])
        //         {
        //             flag = true;
        //             break;
        //         }
        // }

        if(k < n)
        {
            for(int i = 1 + (n - k); i <= k; i ++ )
                if(s1[i] != s2[i])
                {
                    flag = true;
                    break;
                }
        }

        if(flag) puts("NO");
        else puts("YES");
    }

    return 0;
}