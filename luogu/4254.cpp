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

const int N = 1e6 + 10, INF = 0x3f3f3f3f, X = 5e4 + 10;
const double eps = 1e-10;
int n;

struct seg
{
    double k, b;
}a[N];
int sid;

inline double f(int id, int x)
{
    return a[id].k * x + a[id].b;
}

struct node
{
    int l, r;
    int maxn;
}t[N << 2];
int root, cnt;

inline void insert(int &p, int l, int r, int id)
{
    if(!p) p = ++ cnt;
    if(t[p].maxn == 0)
    {
        t[p].maxn = id;
        return;
    }
    if(l == r) return;
    int mid = l + r >> 1;
    if(f(id, mid) - f(t[p].maxn, mid) > eps) swap(id, t[p].maxn);
    if(f(id, l) - f(t[p].maxn, l) > eps) insert(t[p].l, l, mid, id);
    if(f(id, r) - f(t[p].maxn, r) > eps) insert(t[p].r, mid + 1, r, id);
    return;
}

inline double query(int p, int l, int r, int x)
{
    if(!p) return 0;
    double ans = 0;
    if(t[p].maxn != 0) ans = max(ans, f(t[p].maxn, x));
    if(l == r) return ans;
    int mid = l + r >> 1;
    if(x <= mid) ans = max(ans, query(t[p].l, l, mid, x));
    else ans = max(ans, query(t[p].r, mid + 1, r, x));
    return ans;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    while(n -- )
    {
        char op[20];
        cin >> op + 1;

        if(op[1] == 'Q')
        {
            int x;
            cin >> x;
            cout << fixed << setprecision(0) << floor(query(root, 1, X, x) / 100.0) << endl;
        }
        else
        {
            double b, k;
            cin >> b >> k;
            b -= k;
            sid ++;
            a[sid] = {k, b};
            insert(root, 1, X, sid);
        }
    }

    return 0;
}