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

const int N = 1e7 + 10;
bitset<N> st;
int nxt[N];

inline bool check(int x)
{
    while(x)
    {
        if(x % 10 == 7) return true;
        x /= 10;
    }
    return false;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    for(int i = 1; i <= 1e7 + 1; i ++ )
    {
        if(check(i))
        {
            st[i] = true;
            for(int j = i + i; j <= 1e7; j += i)
                st[j] = true;
        }
    }

    nxt[10000001] = 1e7 + 1;
    for(int i = 1e7; i; i -- )
    {
        if(st[i + 1]) nxt[i] = nxt[i + 1];
        else nxt[i] = i + 1;
    }

    int T = read();
    while(T -- )
    {
        int x = read();
        if(st[x]) puts("-1");
        else printf("%d\n", nxt[x]);
    }

    return 0;
}