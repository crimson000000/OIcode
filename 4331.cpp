#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

const int N = 1e6 + 10;
struct node
{
    int l, r;
    int ls, rs;
    int val, siz, fa;
    int dis;
}t[N];
ll a[N], b[N], ans;
int n, cnt;

int merge(int x, int y)
{
    if(!x || !y) return x + y;

    if(a[x] < a[y] || (a[x] == a[y] && x > y)) 
        swap(x, y);
    t[x].rs = merge(t[x].rs, y);
    t[t[x].rs].fa = x;

    if(t[t[x].ls].dis < t[t[x].rs].dis) swap(t[x].ls, t[x].rs);
    t[x].dis = t[t[x].rs].dis + 1;
    return x;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%d", &n);
    t[0].dis = -1;
    for(int i = 1; i <= n; i ++ ) 
    {
        scanf("%lld", &a[i]);
        a[i] -= i;
    }

    for(int i = 1; i <= n; i ++ )
    {
        t[cnt].l = t[cnt].r = t[ ++ cnt].fa = i;
        t[cnt].siz = 1;
        t[cnt].val = (int)a[i];
        while(cnt > 1 && t[cnt].val < t[cnt - 1].val)
        {
            cnt --;
            t[cnt].fa = merge(t[cnt].fa, t[cnt + 1].fa);
            
            t[cnt].siz += t[cnt + 1].siz;
            t[cnt].r = t[cnt + 1].r;
            while(t[cnt].siz << 1 > t[cnt].r - t[cnt].l + 2)
            {
                t[cnt].siz --;
                t[cnt].fa = merge(t[t[cnt].fa].ls, t[t[cnt].fa].rs);
            } 
            t[cnt].val = a[t[cnt].fa];
        }
    }

    for(int i = 1; i <= cnt; i ++ )
    {
        for(int j = t[i].l; j <= t[i].r; j ++ )
        {
            b[j] = t[i].val;
            ans += abs(a[j] - b[j]);
        }
    }

    cout << ans << endl;
    for(int i = 1; i <= n; i ++ ) cout << b[i] + i << ' ';
    
    return 0;
}