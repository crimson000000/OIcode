#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using PII = pair<ll, ll>;

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

#define y1 __y1
#define y2 __y2

const int N = 1e5 + 10;
struct opt
{
    int op, x1, y1, x2, y2;
    bool operator < (const opt& a) const
    {
        if(y1 - x1 != a.y1 - a.x1) return y1 - x1 < a.y1 - a.x1;
        return x1 < a.x1;
    }
}a[N], b[N];

struct chg
{
    int l, r, x, v;
    bool operator < (const chg& a) const
    {
        return x < a.x;
    }
}c[N];
int ccnt;

int n, m, q, qcnt1, qc2, qcnt2;
ll S;
vector<int> nums;
map<PII, bool> mp;

inline void get_point(int i, int j)
{
    int B = b[i].y1 - b[i].x1;
    if(a[j].op == 1)
    {
        int x = a[j].y1 - B;
        if(x >= a[j].x1 && x <= a[j].x2 && x >= b[i].x1 && x <= b[i].x2) 
        {
            PII t = {x, a[j].y1};
            if(!mp.count(t)) 
            {
                mp[t] = true, S --;
                // printf("%d %d %lld %lld\n", i, j, t.first, t.second);
            }
        }
    }
    else
    {
        int y = a[j].x1 + B;
        if(y >= a[j].y1 && y <= a[j].y2 && y >= b[i].y1 && y <= b[i].y2) 
        {
            PII t = {a[j].x1, y};
            if(!mp.count(t)) 
            {
                mp[t] = true, S --;
                // printf("%d %d %lld %lld\n", i, j, t.first, t.second);
            }
        }
    }
}

struct seg
{
    int l, r;
    ll len, cnt;
}t[N << 2];

inline void build(int p, int l, int r)
{
    t[p] = {l, r, 0, 0};
    if(l == r) return;
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
}

inline void pushup(int p)
{
    if(t[p].cnt) t[p].len = nums[t[p].r + 1] - nums[t[p].l];
    else if(t[p].l != t[p].r)
    {
        t[p].len = t[p << 1].len + t[p << 1 | 1].len;
    }
    else t[p].len = 0;
}

inline void change(int p, int l, int r, int v)
{
    if(t[p].l >= l && t[p].r <= r)
    {
        t[p].cnt += v;
        pushup(p);
        return;
    }
    int mid = t[p].l + t[p].r >> 1;
    if(l <= mid) change(p << 1, l, r, v);
    if(r > mid) change(p << 1 | 1, l, r, v);
    pushup(p);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int id = read();
    n = read(), m = read(), q = read();
    for(int i = 1; i <= q; i ++ )
    {
        int op = read(), x1 = read(), y1 = read(), x2 = read(), y2 = read();
        if(op < 3) 
        {
            a[++ qcnt1] = {op, x1, y1, x2, y2};
            nums.push_back(y1), nums.push_back(y2 + 1);
        }
        else b[++ qc2] = {op, x1, y1, x2, y2};
    }

    sort(b + 1, b + qc2 + 1);

    // for(int i = 1; i <= qc2; i ++ ) 
    // {
    //     printf("%d %d %d %d\n", b[i].x1, b[i].y1, b[i].x2, b[i].y2);
    // }
    qcnt2 = 0;
    for(int i = 1; i <= qc2; i ++ )
    {
        if(i != 1 && b[i].y1 - b[i].x1 == b[qcnt2].y1 - b[qcnt2].x1 && b[i].x1 <= b[qcnt2].x2)
        {
            b[qcnt2].x1 = min(b[qcnt2].x1, b[i].x1), b[qcnt2].y1 = min(b[qcnt2].y1, b[i].y1);
            b[qcnt2].x2 = max(b[qcnt2].x2, b[i].x2), b[qcnt2].y2 = max(b[qcnt2].y2, b[i].y2);
        }
        else b[++ qcnt2] = b[i];
    }

    // for(int i = 1; i <= qcnt2; i ++ ) 
    // {
    //     printf("%d %d %d %d\n", b[i].x1, b[i].y1, b[i].x2, b[i].y2);
    // }

    for(int i = 1; i <= qcnt2; i ++ ) S += b[i].x2 - b[i].x1 + 1;
    // cout << S << endl;
    for(int i = 1; i <= qcnt2; i ++ )
        for(int j = 1; j <= qcnt1; j ++ )
            get_point(i, j);

    // cout << S << endl;

    if(!qcnt1)
    {
        cout << S << endl;
        return 0;
    }

    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    for(int i = 1; i <= qcnt1; i ++ ) 
    {
        a[i].y2 ++;
        a[i].x2 ++;
        a[i].y1 = lower_bound(nums.begin(), nums.end(), a[i].y1) - nums.begin();
        a[i].y2 = lower_bound(nums.begin(), nums.end(), a[i].y2) - nums.begin();
    }

    for(int i = 1; i <= qcnt1; i ++ )
    {
        c[++ ccnt] = {a[i].y1, a[i].y2, a[i].x1, 1};
        c[++ ccnt] = {a[i].y1, a[i].y2, a[i].x2, -1};
    }

    sort(c + 1, c + ccnt + 1);

    build(1, 0, nums.size() - 2);

    for(int i = 1; i <= ccnt; i ++ )
    {
        if(i != 1) S += (ll)t[1].len * (c[i].x - c[i - 1].x);
        change(1, c[i].l, c[i].r - 1, c[i].v);
    }
    
    cout << S << endl;

    return 0;
}