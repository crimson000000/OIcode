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

const int N = 1e6 + 10, base = 1e8, mod = 1e9 + 7;
int n;
ll b[N], c[N];
ll a[N], sum[N], f[N], g[N];

// struct bigint
// {
//     vector<int> val;

//     inline void read()
//     {
//         ll x = 0;
//         int cnt = 0;
//         char ch = getchar();
//         while(ch < '0' || ch > '9')
//             ch = getchar();
//         while(ch >= '0' && ch <= '9')
//         {
//             cnt ++;
//             x = (x << 3) + (x << 1) + ch - '0';
//             if(cnt % 8 == 0) val.push_back(x), x = 0;
//             // val.push_back(x), x = 0;
//             ch = getchar(); 
//         }
//         reverse(val.begin(), val.end());
//     }

//     bigint() {val.clear();}
//     bigint(int x)
//     {
//         while(x) val.push_back(x % base), x /= base;
//     }

//     bigint operator + (const bigint a) const
//     {
//         bigint res;
//         int t = 0;
//         for(int i = 0; i < val.size() || i < a.val.size() || t; i ++ )
//         {
//             if(i < val.size()) t += val[i];
//             if(i < a.val.size()) t += a.val[i];
//             res.val.push_back(t % base);
//             t /= base;
//         }
//         return res;
//     }

//     bigint operator - (const bigint a) const
//     {
//         bigint res;
//         int t = 0;
//         for(int i = 0; i < val.size(); i ++ )
//         {
//             t = val[i] - t;
//             if(i < a.val.size()) t -= a.val[i];
//             res.val.push_back((t + base) % base);
//             if(t >= 0) t = 0;
//             else t = 1;
//         }
//         while(res.val.back() == 0 && res.val.size() > 1)
//             res.val.pop_back();
//         return res;
//     }

//     bigint operator * (const ll a) const
//     {
//         bigint res;
//         ll t = 0;
//         for(int i = 0; i < val.size() || t; i ++ )
//         {
//             if(i < val.size()) t += a * val[i];
//             res.val.push_back(t % base);
//             t /= base;
//         }
//         return res;
//     }

//     bigint operator / (const ll a) const
//     {
//         bigint res;
//         ll r = 0;
//         for(int i = val.size() - 1; i >= 0; i -- )
//         {
//             r = r * base + val[i];
//             res.val.push_back(r / a);
//             r %= a;
//         }
//         reverse(res.val.begin(), res.val.end());
//         while(res.val.back() == 0 && res.val.size() > 1)
//             res.val.pop_back();
//         return res;
//     }
    
//     inline bool operator < (const bigint a)
//     {
//         if(val.size() != a.val.size()) return val.size() < a.val.size();
//         for(int i = 0; i < val.size(); i ++ )
//             if(val[i] != a.val[i])
//                 return val[i] < a.val[i];
//         return false;
//     }

//     inline bool empty()
//     {
//         for(auto v : val)
//             if(v) return false;
//         return true;
//     }

//     inline ll to_int()
//     {
//         ll res = 0;
//         for(int i = val.size() - 1; i >= 0; i -- )
//             res = res * 10 + val[i];
//         return res;
//     }

//     inline void print()
//     {
//         printf("%d", val[val.size() - 1]);
//         for(int i = int(val.size()) - 2; i >= 0; i -- )
//             printf("%d", val[i]);
//         puts("");
//     }
// }m;

struct big
{
	int pos, val[1205];
	big()
	{
		memset(val, 0, sizeof(val));
		val[0] = 1;
	}
	big operator + (const big &x) const
	{
		big result;
		result.val[0] = 0;
		for (int i = 0; i <= 1200; i++)
		{
			result.val[i] += val[i] + x.val[i];
			if (result.val[i] >= 1000000000) result.val[i] -= 1000000000, result.val[i + 1]++;
		}
		return result;
	}
	big operator - (const big &x) const
	{
		big result;
		result.val[0] = 0;
		for (int i = 0; i <= 1200; i++)
		{
			result.val[i] += val[i] - x.val[i];
			if (result.val[i] < 0) result.val[i] += 1000000000, result.val[i + 1]--;
		}
		return result;
	}
	big operator * (long long x) const
	{
		big result;
		result.val[0] = 0;
		for (int i = 0; i <= 1200; i++)
		{
			long long tmp = val[i] * x;
			result.val[i] += tmp % 1000000000, result.val[i + 1] += tmp / 1000000000;
			if (result.val[i] >= 1000000000) result.val[i] -= 1000000000, result.val[i + 1]++;
		}
		return result;
	}
	big operator / (long long x)
	{
		big result;
		result.val[0] = 0;
		result.pos = pos;
		long long tmp = 0;
		for (int i = pos; i >= 0; i--)
		{
			result.val[i] = (tmp + val[i]) / x;
			tmp = (tmp + val[i]) % x * 1000000000;
			if (!result.val[i] && i == result.pos) result.pos--;
		}
		return result;
	}
	void get(string s)
	{
		int siz = s.size();
		val[0] = 0;
		for (int i = 0; i < siz; i++)
		{
			for (int j = 1200; j >= 0; j--)
			{
				long long tmp = val[j] * 10LL;
				val[j] = tmp % 1000000000;
				val[j + 1] += tmp / 1000000000;
			}
			val[0] += s[i] - '0';
			for (int j = 0; j <= 1200; j++)
				if (val[j] >= 1000000000)
					val[j] -= 1000000000, val[j + 1]++;
		}
		pos = 1200;
	}
	bool empty(void)
	{
		for (int i = 0; i <= 1200; i++)
			if (val[i]) return false;
		return true;
	}
} m;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    a[1] = 1;

    for(int i = 2; i <= n; i ++ ) a[i] = read();
    for(int i = 1; i <= n; i ++ ) b[i] = read();

    string str;
    cin >> str;
    m.get(str);
    // m.print();
    // int a = read();

    // (m / a).print();

    big now = m;
    for(int i = 2; i <= n; i ++ )
    {
        if(now.empty())
        {
            n = i - 1;
            break;
        }
        if(a[i] != 1)
        {
            big tmp = now / a[i];
            c[i] = (now - tmp * a[i]).val[0];
            now = tmp;
        }
    }

    // for(int i = 1; i <= n; i ++ ) cout << c[i] << endl;

    int lim = 0;
    f[0] = 1;
    for(int i = 1; i <= n; i ++ )
    {
        memcpy(g, f, (lim + 1) * sizeof(ll));
        memset(f, 0, (lim + 1) * sizeof(ll));
        
        for(int j = c[i]; j <= lim; j += a[i])
            f[j / a[i]] = g[j];
        
        lim = lim / a[i] + b[i];
        for(int j = 1; j <= lim + 1; j ++ )
            sum[j] = (sum[j - 1] + f[j - 1]) % mod;
        for(int j = 0; j <= lim; j ++ )
            f[j] = (sum[j + 1] - sum[max(0ll, j - b[i])] + mod) % mod;
    }

    // cout << "yeah" << endl;

    for(int i = 1; i <= 1200; i ++ )
        if(now.val[i])
        {
            puts("0");
            return 0;
        }
    
    if(now.val[0] > lim)
    {
        puts("0");
        return 0;
    }

    // now.print();

    // for(int i = 1; i <= now.to_int(); i ++ )
    //     cout << f[i] << endl;

    cout << f[now.val[0]] << endl;

    return 0;
}
