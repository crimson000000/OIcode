#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
typedef long double ld;

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

const int N = 1e5 + 10, M = 1e6 + 10;
int a[N], pre[N];
int n, m;

struct change
{
    int time, x, y, val;
    bool type;
    
    change(int _time, int _x, int _y, int _val, bool _type):
        time(_time), x(_x), y(_y), val(_val), type(_type) {};
};
vector<change> vc;
unordered_map<int, int> mp;
int mptot;

namespace kdt
{
    struct node
    {
        int l, r;
        mutable int val;
        bool operator < (const node& a) const
        {
            return l < a.l;
        }
    };

    set<node> odt, col[N];

    inline auto insert(int l, int r, int v)
    {
        col[v].insert({l, r, v});
        return odt.insert({l, r, v}).first;
    }

    inline void del(int l, int r, int v)
    {
        col[v].erase({l, r, v});
        odt.erase({l, r, v});
    }

    inline auto split(int x)
    {
        auto it = odt.lower_bound({x, 0, 0});
        if(it != odt.end() && it -> l == x) return it;
        it --;
        int l = it -> l, r = it -> r, val = it -> val;
        del(l, r, val);
        insert(l, x - 1, val);
        return insert(x, r, val);
    }

    inline int Prev(int pos)
    {
        auto it = odt.upper_bound({pos, 0, 0});
        it --;
        if(it -> l < pos) return pos - 1;
        else
        {
            auto rm = col[it -> val].lower_bound({pos, 0, 0});
            if(rm != col[it -> val].begin())
            {
                rm --;
                return rm -> r;
            }
            return 0;
        }
    }

    inline void assign(int l, int r, int v, int t)
    {
        auto itr = split(r + 1), itl = split(l);
        vector<int> deal;
        deal.clear();
        for(auto it = itl; it != itr; it ++ )
        {
            if(it != itl) deal.push_back(it -> l);
            auto nxt = col[it -> val].upper_bound(*it);
            if(nxt != col[it -> val].end()) deal.push_back(nxt -> l);
            col[it -> val].erase(*it);
        }
        odt.erase(itl, itr);
        odt.insert({l, r, v});
        col[v].insert({l, r, v});
        deal.push_back(l);
        auto nxt = col[v].upper_bound({l, r, v});
        if(nxt != col[v].end()) deal.push_back(nxt -> l);
        for(int i = 0; i < deal.size(); i ++ )
        {
            if(deal[i] < 1 || deal[i] > n) continue;
            vc.emplace_back(t, deal[i], pre[deal[i]], -1, 0);
            pre[deal[i]] = Prev(deal[i]);
            vc.emplace_back(t, deal[i], pre[deal[i]], 1, 0);
        }
    }
}

int lst[N];
inline void prefix()
{
    vc.emplace_back(-1, 0, 0, 0, 0);
    for(int i = 1; i <= n; i ++ )
    {
        pre[i] = lst[a[i]];
        vc.emplace_back(0, i, pre[i], 1, 0);
        lst[a[i]] = i;
        kdt::odt.insert({i, i, a[i]});
        kdt::col[a[i]].insert({i, i, a[i]});
    }
}

int idx[M];
int ans[N];

struct treea
{
    int c[N];
    #define lowbit(x) x & -x
    inline void add(int x, int val)
    {
        for(; x <= n; x += lowbit(x)) c[x] += val;
    }

    inline int query(int x)
    {
        int res = 0;
        for(; x; x -= lowbit(x)) res += c[x];
        return res;
    }

    inline void clear(int x)
    {
        for(; x <= n; x += lowbit(x)) c[x] = 0;
    }
} bit;

void cdq(int l, int r)
{
    if(l == r) return;
    int mid = l + r >> 1;
    cdq(l, mid), cdq(mid + 1, r);

    vector<int> tmp;
    tmp.clear();

    int i = l, j = mid + 1;
    while(i <= mid && j <= r)
    {
        if(vc[idx[i]].x <= vc[idx[j]].x)
        {
            if(vc[idx[i]].type == 0) bit.add(vc[idx[i]].y, vc[idx[i]].val);
            tmp.push_back(idx[i]);
            i ++;
        }
        else
        {
            if(vc[idx[j]].type == 1) 
                ans[vc[idx[j]].time] += vc[idx[j]].val * bit.query(vc[idx[j]].y);
            tmp.push_back(idx[j]);
            j ++;
        }
    }

    while(j <= r)
    {
        if(vc[idx[j]].type == 1)
            ans[vc[idx[j]].time] += vc[idx[j]].val * bit.query(vc[idx[j]].y);
        tmp.push_back(idx[j]);
        j ++;
    }

    for(int k = l; k < i; k ++ )
        if(vc[idx[k]].type == 0)
            bit.clear(vc[idx[k]].y);
    
    while(i <= mid)
    {
        tmp.push_back(idx[i]);
        i ++;
    }

    for(int i = l; i <= r; i ++ ) idx[i] = tmp[i - l];
}

int main()
{
    #ifdef LOCAL
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ ) 
    {
        a[i] = read();
        if(!mp[a[i]]) mp[a[i]] = ++ mptot;
        a[i] = mp[a[i]];
    }

    prefix();

    for(int i = 1; i <= m; i ++ )
    {
        int op = read(), l = read(), r = read();
        if(op == 1)
        {
            int x = read();
            if(!mp[x]) mp[x] = ++ mptot;
            x = mp[x];
            kdt::assign(l, r, x, i);
        }
        else 
        {
            vc.emplace_back(i, r, l - 1, 1, 1);
            vc.emplace_back(i, l - 1, l - 1, -1, 1);
        }
    }

    int pcnt = vc.size() - 1;
    for(int i = 1; i <= pcnt; i ++ ) vc[i].y ++;

    int maxx = 0, maxy = 0, maxz = 0;
    for(int i = 1; i <= pcnt; i ++ )
        if(vc[i].type)
        {
            maxx = max(maxx, vc[i].time);
            maxy = max(maxy, vc[i].x);
            maxz = max(maxz, vc[i].y);
        }
    
    vector<int> idd;
    idd.clear();
    for(int i = 1; i <= pcnt; i ++ )
        if(vc[i].type || (vc[i].time <= maxx && vc[i].x <= maxy && vc[i].y <= maxz))
            idd.push_back(i);
    
    pcnt = idd.size();
    for(int i = 1; i <= pcnt; i ++ ) idx[i] = idd[i - 1];

    cdq(1, pcnt);

    for(int i = 1; i <= m; i ++ )
        if(ans[i])
            printf("%d\n", ans[i]);
    
    return 0;
}
