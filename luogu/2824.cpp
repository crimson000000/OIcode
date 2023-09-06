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

const int N = 1e6 + 10;
int a[N];

struct qq
{
	int l, r;
	int dec;
}q[N];

int n, m, position;

struct seg
{
	int l, r;
	int val, cov;
}t[N << 2];

inline void pushup(int p)
{
	t[p].val = t[p << 1].val + t[p << 1 | 1].val;
}

inline void cover(int p, int val)
{
	t[p].cov = val;
	if(val) t[p].val = t[p].r - t[p].l + 1;
	else t[p].val = 0;
}

inline void pushdown(int p)
{
	if(t[p].cov != -1)
	{
		cover(p << 1, t[p].cov);
		cover(p << 1 | 1, t[p].cov);
		t[p].cov = -1;
	}
}

inline void build(int p, int l, int r, int bin)
{
	t[p].l = l, t[p].r = r;
	t[p].cov = -1;
	if(l == r)
	{
		t[p].val = (a[l] > bin);
		return;
	}
	int mid = l + r >> 1;
	build(p << 1, l, mid, bin);
	build(p << 1 | 1, mid + 1, r, bin);
	pushup(p);
}

inline void cover(int p, int l, int r, int val)
{
	if(l > r) return;
	if(t[p].l >= l && t[p].r <= r)
	{
		cover(p, val);
		return;
	}
	pushdown(p);
	int mid = t[p].l + t[p].r >> 1;
	if(l <= mid) cover(p << 1, l, r, val);
	if(r > mid) cover(p << 1 | 1, l, r, val);
	pushup(p);
}

inline int query(int p, int pos)
{
	if(t[p].l == t[p].r) return t[p].val;
	pushdown(p);
	int mid = t[p].l + t[p].r >> 1;
	if(pos <= mid) return query(p << 1, pos);
	else return query(p << 1 | 1, pos);
}

inline int query(int p, int l, int r)
{
	if(l > r) return 0;
	if(t[p].l >= l && t[p].r <= r) return t[p].val;
	pushdown(p);
	int mid = t[p].l + t[p].r >> 1;
	int res = 0;
	if(l <= mid) res += query(p << 1, l, r);
	if(r > mid) res += query(p << 1 | 1, l, r);
	return res; 
}

inline void sort(int l, int r, int de)
{
	// cerr << "yeah" << endl;
	int cnt = query(1, l, r);
	// cout << cnt << endl;
	if(de)
	{
		cover(1, l, l + cnt - 1, 1);
		cover(1, l + cnt, r, 0);
	}
	else
	{
		cnt = r - l + 1 - cnt;
		cover(1, l, l + cnt - 1, 0);
		cover(1, l + cnt, r, 1);
	}
}

inline bool check(int mid)
{
	build(1, 1, n, mid);
	// cout << mid << endl;
	// for(int i = 1; i <= n; i ++ ) printf("%d ", query(1, i));
	// puts("");
	
	for(int i = 1; i <= m; i ++ )
	{
		int l = q[i].l, r = q[i].r, de = q[i].dec;
		
		sort(l, r, de);
	}
	// for(int i = 1; i <= n; i ++ ) printf("%d ", query(1, i));
	// puts("");
	return query(1, position) == 1;
}

int main()
{
	#ifdef LOCAL
		freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
		freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
	#endif

	n = read(), m = read();

	for(int i = 1; i <= n; i ++ ) a[i] = read();
	for(int i = 1; i <= m; i ++ )
	{
		int op = read(), l = read(), r = read();
		q[i] = {l, r, op};
	}

	position = read();

	int l = 0, r = 1e9;
	while(l < r)
	{
		int mid = l + r >> 1;
		if(check(mid)) l = mid + 1;
		else r = mid;
	}

	cout << l << endl;

	// for(int i = 1; i <= n; i ++ ) a[i] = i;
	// build(1, 1, n, n / 2 + 1);
	// for(int i = 1; i <= n; i ++ ) printf("%d ", query(1, i));
	// puts("");

	// sort(1, 6, 0);
	// for(int i = 1; i <= n; i ++ ) printf("%d ", query(1, i));
	// puts("");

	return 0;
}