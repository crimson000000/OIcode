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

const int N = 100010, M = 1 << 16;
int ans = 0x3f3f3f3f, tot;
int c[N], a[N], s[N];
int g[M], f[M];
int n, m;

int find(int t, int left)
{
    int l = left, r = m;
    while(l <= r)
    {
        int mid = l + r >> 1;
        if(s[mid] - s[left - 1] == t) return mid; 
        if(s[mid] - s[left - 1] < t) l = mid + 1;
        else r = mid - 1;
    }
    return r;
}

// inline int find(int x, int left) 
// {
// 	int l = left, r = m;
// 	while(l <= r) {
//         int mid = (l + r) >> 1;
//         if(s[mid] - s[left - 1] == x) return mid;
//         if(s[mid] - s[left - 1] < x) l = mid + 1;
//         else r = mid - 1;
// 	}
// 	return r;
// }


int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ ) 
    {
        scanf("%d", &c[i]);
        tot += c[i];
    }
    
    for(int i = 1; i <= m; i ++ ) 
    {
        scanf("%d", &a[i]);
        s[i] = s[i - 1] + a[i];
    }

    for(int i = 1; i < (1 << n); i ++ )
        for(int j = 1; j <= n; j ++ )
            if(i & (1 << j - 1))
            {
                int x = i ^ (1 << (j - 1));
                int sum = find(c[j], g[x] + 1);
                if(sum > g[i])
                {
                    g[i] = sum;
                    f[i] = f[x] + c[j];
                }
                if(g[i] == m) ans = min(f[i], ans);
            }

    if(tot - ans < 0) puts("-1");
    else cout << tot - ans << endl;
    
    return 0;
}
