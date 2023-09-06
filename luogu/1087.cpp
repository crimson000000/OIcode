#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

int n;
char s[110];
const char ans[] = {"FBI"};

int qmi(int x, int k)
{
    int res = 1;
    while(k)
    {
        if(k & 1) res *= x;
        x = x * x;
        k >>= 1;
    }
    return res;
}

int get(int l, int r)
{
    bool b = false, I = false;
    for(int i = l; i <= r; i ++ )
    {
        if(s[i] == '0') b = true;
        if(s[i] == '1') I = true;
        if(b && I) return 0;
    }
    if(b) return 1;
    return 2;
}

void dfs(int l, int r)
{
    if(l == r)
    {
        cout << ans[get(l, r)];
        return;
    }
    int mid = l + r >> 1;
    dfs(l, mid);
    dfs(mid + 1, r);
    cout << ans[get(l, r)];
    return;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    cin >> s + 1;

    dfs(1, qmi(2, n));
    
    return 0;
}
