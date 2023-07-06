#define LOCAL
#define lowbit(x) x & -x
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

const int N = 2e5 + 10;
int h[N], e[N], ne[N], idx;
int v[N], f[N];
int c[N];
vector<int> nums;
int n, ans;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void insert(int x, int val){
    for(; x <= n; x += lowbit(x)) c[x] += val;
}

int query(int x)
{
    int res = 0;
    for(; x; x -= lowbit(x)) 
        res += c[x];
    
    return res;
}

void dp(int u)
{
    f[u] = -(query(n) - query(v[u]));
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        
        dp(j);
    }
    f[u] += query(n) - query(v[u]);
    insert(v[u], 1);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif
    
    memset(h, -1, sizeof h);

    n = read();
    for(int i = 1; i <= n; i ++ ) 
    {
        v[i] = read();
        nums.push_back(v[i]);
    }

    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    for(int i = 1; i <= n; i ++ )
        v[i] = lower_bound(nums.begin(), nums.end(), v[i]) - nums.begin() + 1;

    for(int i = 2; i <= n; i ++ )
    {
        int a = read();
        add(a, i);
    }

    dp(1);

    for(int i = 1; i <= n; i ++ ) cout << f[i] << endl;

    return 0;
}
