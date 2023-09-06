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

const int INF = 0x3f3f3f3f;
struct state
{
    int x, y, z;
    bool operator==(const state &t) const
    {
        return (x == t.x) && (y == t.y) && (z == t.z);
    }
} st, ed;
int a[5];

int k, step;
state find_root(state t, int s)
{
    for(step = 0; s; step += k)
    {
        int d1 = t.y - t.x, d2 = t.z - t.y;
        if(d1 == d2) return t;
        if(d1 < d2)
        {
            k = min((d2 - 1) / d1, s);
            t.x += k * d1, t.y += k * d1;
            s -= k;
        }
        else
        {
            k = min((d1 - 1) / d2, s);
            t.y -= k * d2, t.z -= k * d2;
            s -= k;
        }
    }
    return t;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    a[0] = read(), a[1] = read(), a[2] = read();
    sort(a, a + 3);
    st.x = a[0], st.y = a[1], st.z = a[2];

    a[0] = read(), a[1] = read(), a[2] = read();
    sort(a, a + 3);
    ed.x = a[0], ed.y = a[1], ed.z = a[2];

    auto st_root = find_root(st, INF);
    int stp1 = step;
    auto ed_root = find_root(ed, INF);
    int stp2 = step;

    if(!(st_root == ed_root))
    {
        puts("NO");
        return 0;
    }

    if(stp1 < stp2)
    {
        swap(st, ed);
        swap(stp1, stp2);
    }

    st = find_root(st, stp1 - stp2);
    int l = 0, r = stp2;
    while(l < r)
    {
        int mid = l + r >> 1;
        if(find_root(st, mid) == find_root(ed, mid)) r = mid;
        else l = mid + 1;
    }
    
    puts("YES");
    cout << (l << 1) + stp1 - stp2 << endl;

    return 0;
}