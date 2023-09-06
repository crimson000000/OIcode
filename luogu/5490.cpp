#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
struct seg{
    ll x, y1, y2;
    int k;
    bool operator < (const seg &W) const{
        return x < W.x;
    }
}segs[N];

struct segment{
    int l, r;
    int cnt;
    ll len;
}t[N * 4];
int n;
vector<ll> ys;

int find(ll x){
    return lower_bound(ys.begin(), ys.end(), x) - ys.begin();
}

void build(int p, int l, int r){
    t[p] = {l, r, 0, 0};
    if(l == r) return;
    int mid = l + r >> 1;
    build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
}

void pushup(int p){
    if(t[p].cnt) t[p].len = ys[t[p].r + 1] - ys[t[p].l];
    else if(t[p].r != t[p].l){
        t[p].len = t[p << 1].len + t[p << 1 | 1].len;
    }
    else t[p].len = 0;
}

void change(int p, int l, int r, int k){
    if(t[p].l >= l && t[p].r <= r){
        t[p].cnt += k;
        pushup(p);
        return;
    }
    int mid = t[p].l + t[p].r >> 1;
    if(l <= mid) change(p << 1, l, r, k);
    if(r > mid) change(p << 1 | 1, l, r, k);
    pushup(p);
}

int main()
{
    
    scanf("%d", &n);
    ys.clear();
    for (int i = 0, j = 0; i < n; i ++ ){
        ll x1, x2, y1, y2;
        scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
        segs[j ++ ] = {x1, y1, y2, 1};
        segs[j ++ ] = {x2, y1, y2, -1};
        ys.push_back(y1), ys.push_back(y2);
    }
    sort(segs, segs + 2 * n);
        
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
        
    build(1, 0, ys.size() - 2);
        
    ll res = 0;
    for(int i = 0; i < 2 * n; i ++ ){
        if(i > 0) res += t[1].len * (segs[i].x - segs[i - 1].x);
        change(1, find(segs[i].y1), find(segs[i].y2) - 1, segs[i].k);
    }
        
    cout << res << endl;
}
