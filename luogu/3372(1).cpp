#define LOCAL
#include <bits/stdc++.h>

using namespace std;

int main()
{
	#ifdef LOCAL
		freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
		freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
	#endif











using ll = long long;

auto read = [] ()
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
};

const int N = 1e6 + 10;
struct seg
{
	int l, r;
	ll add, sum;
};
static seg t[N << 2];
static int a[N];
static int n, m;

function<ll(int, int, int)> query;
function<void(int, int, int)> build;
function<void(int, int, int, ll)> change;
function<void(int)> pushup;
function<void(int)> pushdown;

pushup = [&] (int p)
{
	t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum;
};

pushdown = [&] (int p)
{
	if(t[p].add)
	{
		t[p << 1].add += t[p].add;
		t[p << 1 | 1].add += t[p].add;
		t[p << 1].sum += (t[p << 1].r - t[p << 1].l + 1) * t[p].add;
		t[p << 1 | 1].sum += (t[p << 1 | 1].r - t[p << 1 | 1].l + 1) * t[p].add;
		t[p].add = 0;
	}
};

build = [&] (int p, int l, int r)
{
	t[p].l = l, t[p].r = r;
	if(l == r)
	{
		t[p].sum = a[l];
		return;
	}
	int mid = l + r >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	pushup(p);
};

change = [&] (int p, int l, int r, ll v)
{
	if(t[p].l >= l && t[p].r <= r)
	{
		t[p].add += v;
		t[p].sum += (ll)v * (t[p].r - t[p].l + 1);
		return;
	}
	pushdown(p);
	int mid = t[p].l + t[p].r >> 1;
	if(l <= mid) change(p << 1, l, r, v);
	if(r > mid) change(p << 1 | 1, l, r, v);
	pushup(p);
};

query = [&] (int p, int l, int r)
{
	if(t[p].l >= l && t[p].r <= r) return t[p].sum;
	pushdown(p);
	int mid = t[p].l + t[p].r >> 1;
	ll res = 0;
	if(l <= mid) res += query(p << 1, l, r);
	if(r > mid) res += query(p << 1 | 1, l, r);
	return res;
};

auto Main = [&] ()
{
	n = read(), m = read();
	for(int i = 1; i <= n; i ++ ) a[i] = read();
	
	build(1, 1, n);
	while(m -- )
	{
		int op = read(), l = read(), r = read();
		if(op == 1)
		{
			ll v = read();
			change(1, l, r, v);
		}
		else
		{
			printf("%lld\n", query(1, l, r));
		}
	}
};

Main();





















	return 0;
}