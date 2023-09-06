#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
using ull = unsigned long long;

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

const int N = 2e6 + 10;
const ull P = 131;
char s[N];
int n;
ull h[N], p[N];
int sa[N];

inline ll gethash(int l, int r)
{
    return h[r] - h[l - 1] * p[r - l + 1];
}

inline bool cmp(int a, int b)
{
    int l = -1, r = min(n - a, n - b);
    while(l < r)
    {
        int mid = l + r + 1 >> 1;
        if(gethash(a, a + mid) == gethash(b, b + mid)) 
            l = mid;
        else r = mid - 1;
    }
    if(l > min(n - a, n - b)) return a > b;
    else return s[a + l + 1] < s[b + l + 1];
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s", s + 1);
    n = strlen(s + 1);

    p[0] = 1;
    for(int i = 1; i <= n; i ++ ) p[i] = p[i - 1] * P;

    for(int i = 1; i <= n; i ++ )
        h[i] = (h[i - 1] * P + s[i]);

    for(int i = 1; i <= n; i ++ ) sa[i] = i;

    stable_sort(sa + 1, sa + n + 1, cmp);

    for(int i = 1; i <= n; i ++ ) printf("%d ", sa[i]);

    return 0;
}