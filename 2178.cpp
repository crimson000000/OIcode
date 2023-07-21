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
const ll INF = 0x3f3f3f3f3f3f3f3f;
int sa[N], rk[N], id[N], oldrk[N], cnt[N], height[N];
ll a[N];
char s[N];
int n, m, p, w;
vector<int> q[N];

ll a1, a2;
int fa[N], siz[N], minn[N], maxn[N];
ll ans1[N], ans2[N];

inline int find(int x)
{
	if(fa[x] != x) fa[x] = find(fa[x]);
	return fa[x]; 
}

inline void merge(int x, int y)
{
	x = find(x), y = find(y);
	a1 += (ll)siz[x] * siz[y], a2 = max(a2, max((ll)minn[x] * minn[y], (ll)maxn[x] * maxn[y]));
	fa[y] = x;
	siz[x] += siz[y], minn[x] = min(minn[x], minn[y]), maxn[x] = max(maxn[x], maxn[y]);
}

inline void build(char *s)
{
	m = 127;
	for(int i = 1; i <= n; i ++ ) rk[i] = s[i];
	for(int i = 1; i <= n; i ++ ) cnt[rk[i]] ++;
	for(int i = 1; i <= m; i ++ ) cnt[i] += cnt[i - 1];
	for(int i = n; i >= 1; i -- ) sa[cnt[rk[i]] -- ] = i;
	swap(rk, oldrk);
	for(int i = 1; i <= n; i ++ )
	{
		if(oldrk[sa[i]] != oldrk[sa[i - 1]])
			rk[sa[i]] = ++ p;
		else rk[sa[i]] = p;
	}

	for(w = 1; w < n; w <<= 1)
	{
		m = p;
		p = 0;
		for(int i = n; i > n - w; i -- ) id[++ p] = i;
		for(int i = 1; i <= n; i ++ )
			if(sa[i] > w)
				id[++ p] = sa[i] - w;
		
		memset(cnt, 0, sizeof cnt);
		for(int i = 1; i <= n; i ++ ) cnt[rk[id[i]]] ++;
		for(int i = 1; i <= m; i ++ ) cnt[i] += cnt[i - 1];
		for(int i = n; i >= 1; i -- ) sa[cnt[rk[id[i]]] -- ] = id[i];

		swap(rk, oldrk);
		p = 0;
		for(int i = 1; i <= n; i ++ )
		{
			if(oldrk[sa[i]] != oldrk[sa[i - 1]] || oldrk[sa[i] + w] != oldrk[sa[i - 1] + w])
				rk[sa[i]] = ++ p;
			else rk[sa[i]] = p;
		}
	}

	// for(int i = 1; i <= n; i ++ ) cout << rk[i] << ' ';
	// puts("");

	for(int i = 1, j = 0; i <= n; i ++ )
	{
		if(j) j --;
		while(s[i + j] == s[sa[rk[i] - 1] + j]) j ++;
		height[rk[i]] = j;
	}

	// for(int i = 1; i <= n; i ++ ) cout << height[i] << ' ';
}

int main()
{
	#ifdef LOCAL
		freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
		freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
	#endif

	n = read();
	scanf("%s", s + 1);
	for(int i = 1; i <= n; i ++ ) a[i] = read();

	build(s);

	a2 = -INF;
	for(int i = 1; i <= n; i ++ ) 
	{
		fa[i] = i, siz[i] = 1;
		minn[i] = maxn[i] = a[sa[i]];
		q[height[i]].push_back(i);
	}

	for(int i = n - 1; i >= 0; i -- )
	{
		for(auto v : q[i])
			merge(v, v - 1);
		if(a1) ans1[i] = a1, ans2[i] = a2;
	}

	for(int i = 0; i < n; i ++ )
		printf("%lld %lld\n", ans1[i], ans2[i]);

	return 0;
}
