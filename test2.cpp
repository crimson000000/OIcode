#include <iostream>
#include <algorithm>
#include <cstring>

namespace read_write
{
	inline int read()
	{
		int x = 0, f = 1;
		char ch = getchar();
		while(ch > '9' || ch < '0')
		{
			if(ch == '-')
				f = -1;
			ch = getchar();
		}
		while(ch >= '0' && ch <= '9')
			x = x * 10 + ch - '0', ch = getchar();
		return x * f;
	}

	inline void write(int x)
	{
		if(x < 0)
		{
			x = -x;
			putchar('-');
		}
		if(x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

namespace Graph_Theory
{
	const int N = 1e6 + 10;
	
	int n, m, mx;
	int h[N], idx;
	int w[N], fa[N][22], elapse[N], dep[N], d[N];

	int dfn[N], son[N], timestamp, siz[N], top[N], Fa[N];

	struct Edge
	{
		int ne, v, w;
	} e[N];

	int max(int x, int y)
	{
		return x > y ? x : y;
	}

	int min(int x, int y)
	{
		return x > y ? y : x;
	}

	void swap(int &x, int &y)
	{
		int tem = x;
		x = y, y = tem;
	}

	void add(int u, int v, int w)
	{
		e[++ idx].v = v, e[idx].ne = h[u], e[idx].w = w, h[u] = idx;
		e[++ idx].v = u, e[idx].ne = h[v], e[idx].w = w, h[v] = idx; 
	}

	/*
	void dfs(int x, int fath)
	{
		fa[x][0] = fath, dep[x] = dep[fath] + 1;
		for(int i = h[x] ; i ; i = e[i].ne)
		{
			int v = e[i].v;
			if(v == fath)
				continue;
			d[v] = d[x] + e[i].w, w[v] = e[i].w;
			dfs(v, x);
		}
	} */

	void dfs1(int x, int fath)
	{
		Fa[x] = fath, dep[x] = dep[fath] + 1;
		siz[x] = 1;

		for(int i = h[x] ; i ; i = e[i].ne)
		{
			int v = e[i].v;
			if(v == fath)
				continue;
			d[v] = d[x] + e[i].w, w[v] = e[i].w;
			dfs1(v, x);
			siz[x] += siz[v];
			if(siz[v] > siz[son[x]])
				son[x] = v;
		}
	}

	void dfs2(int x, int tp)
	{
		dfn[x] = ++ timestamp, top[x] = tp; 
		if(son[x])
			dfs2(son[x], tp);
		for(int i = h[x] ; i ; i = e[i].ne)
		{
			int v = e[i].v;
			if(v == Fa[x] || v == son[x])
				continue;
			dfs2(v, v);
		}
	}

	void calc()
	{
		for(int i = 1 ; i <= n ; ++ i)
			mx = max(mx, d[i]);
		for(int i = 1 ; i <= 20 ; ++ i)
			for(int j = 1 ; j <= n ; ++ j )
				fa[j][i] = fa[fa[j][i - 1]][i - 1];
	}

	int LCA(int u, int v)
	{
		while(top[u] != top[v])
		{
			if(dep[top[u]] < dep[top[v]])
			{
				v = Fa[top[v]];
				continue;
			}	
			if(dep[top[u]] > dep[top[v]])
			{
				u = Fa[top[u]];
				continue;
			}
		}
		if(dep[u] < dep[v])
			return u;
		return v;
	}

	/*int LCA(int u, int v)
	{
		if(dep[u] < dep[v])
			swap(u, v);
		for(int i = 20 ; i >= 0 ; -- i)
			if(dep[fa[u][i]] >= dep[v])
				u = fa[u][i];
		for(int i = 20 ; i >= 0 ; -- i)
			if(fa[u][i] != fa[v][i])
				u = fa[u][i], v = fa[v][i];
		if(u != v)
			return fa[u][0];
		return u;
	}*/

	int get(int x)
	{
		for(int i = h[x] ; i ; i = e[i].ne)
		{
			int v = e[i].v;
			if(v == fa[x][0])
				continue;
			elapse[x] += get(v); 
		}
		return elapse[x];
	}
}

namespace Solve
{
	using namespace Graph_Theory;
	const int N = 1e6 + 10, INF = 0x3f3f3f3f;

	int ans, s[N], t[N], lca[N], dis[N];

	void memset()
	{
		for(int i = 0 ; i < N ; i ++)
			elapse[i] = 0;
	}

	void differ(int x)
	{
		++ elapse[s[x]];
		++ elapse[t[x]];
		elapse[lca[x]] -= 2;
	}

	bool check(int mid)
	{
		memset();
		int Len = 0, cnt = 0;
		for(int i = 1 ; i <= m ; ++ i)
		{
			if(dis[i] > mid)
				differ(i), Len = max(Len, dis[i] - mid), ++ cnt;
		}
		get(1);

		for(int i = 1 ; i <= n ; ++ i)
			if(elapse[i] >= cnt && Len <= w[i])
			{
				ans = min(ans, mid);
				return true;
			}
		return false;
	}

	int get_ans()
	{
		int l = 0, r = mx << 1, mid;
		ans = INF;
		while(l <= r)
		{
			
			mid = l + r >> 1;
			if(check(mid))
				r = mid - 1;
			else 
				l = mid + 1;
		}
		std::cout<<"yes";
		return ans;
	}
}

using namespace Solve;
using namespace read_write;

int main()
{
	n = read(), m = read();

	for(int i = 1 ; i < n ; ++ i )
	{
		int a = read(), b = read(), c = read();
		add(a, b, c);
	}

	dfs1(1, 0);
	calc();
	dfs2(1, 1);
	
	for(register int i = 1 ; i <= m ; ++ i)
	{
		int a = read(), b = read();
		lca[i] = LCA(a, b);
		s[i] = a, t[i] = b;
		dis[i] = d[a] + d[b] - 2 * d[lca[i]];
	}

	write(get_ans());

	return 0;
}