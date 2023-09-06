#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<long long, long long> PII;

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

const int N = 2e6 + 10;
int h[N], e[N], ne[N], idx;
bitset<N> st;
int din[N];
int n, m;
priority_queue<int> q;
vector<int> ans;

inline void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

inline bool topsort()
{
	st.reset();
	ans.clear();
	for(int i = 1; i <= n; i ++ )
		if(!din[i])	
		{
			q.emplace(i);
			st[i] = true;
		}
	while(q.size())
	{
		int u = q.top();
		q.pop();
		ans.emplace_back(u);

		for(int i = h[u]; i != -1; i = ne[i])
		{
			int v = e[i];
			din[v] --;
			if(!din[v]) 
			{
				q.emplace(v);
				st[v] = true;
			}
		}
	}

	for(int i = 1; i <= n; i ++ ) 
		if(!st[i])
			return false;
	return true;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

	int T = read();
	while(T -- )
	{
		n = read(), m = read();
		memset(din, 0, sizeof din);
		memset(h, -1, sizeof h);
		for(int i = 1; i <= m; i ++ )
		{
			int a = read(), b = read();
			add(b, a);
			din[a] ++;
		}

		if(!topsort()) puts("Impossible!");
		else 
		{
			for(int i = ans.size() - 1; i >= 0; i -- ) 
				printf("%d ", ans[i]);
			puts("");
		}
	}

    return 0;
}