#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using PII = pair<ll, ll>;
class IO{
private:
    static const unsigned int SIZE=1<<20;
    char buf[SIZE],*p1,*p2,obuf[SIZE],*p3;
    char getchar(){
        return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZE,stdin),p1==p2)?EOF:*p1++;
    }
    void putchar(const char &ch){
        (p3-obuf<SIZE)?(*p3++=ch):(out_end(),*p3++=ch);
    }
public:
    IO():p1(buf),p2(buf),p3(obuf){}
    ~IO(){out_end();}
    void out_end(){fwrite(obuf,p3-obuf,1,stdout),p3=obuf;}
    template<typename T>
    void read(T& x){
        x=0;bool flag=0;char ch=getchar();
        for(;ch<'0'||ch>'9';ch=getchar()) if(ch=='-') flag=1;
        if(flag) for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)-(ch&15);
        else for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch&15);
    }
    template<typename T=int>
    T read(){
        T x=0;bool flag=0;char ch=getchar();
        for(;ch<'0'||ch>'9';ch=getchar()) if(ch=='-') flag=1;
        if(flag) for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)-(ch&15);
        else for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch&15);
        return x;
    }
    void read(char *str){
		while((*str=getchar())==' '||*str=='\n');
		while((*++str=getchar())!=' '&&*str!='\n'&&*str!=EOF);
		*str=0;
    }
    void read(char &c){
        while((c=getchar())==' '||c=='\n');
    }
    template<typename T>
    void write(T x){
        static char sta[40];
        int top=0;
        if(x<0){
            putchar('-');
            do sta[top++]=((-x)%10)^48,x/=10;
            while(x);
        }
        else{
            do sta[top++]=(x%10)^48,x/=10;
            while(x);
        }
        while(top) putchar(sta[--top]);
    }
    void write(char x){putchar(x);}
    void write(char *str){
        while(*str!='\0') putchar(*str++);
    }
    void write(const char *str){
        while(*str!='\0') putchar(*str++);
    }
    template<typename... Args>
    void read(Args &...args){
        (void)std::initializer_list<int>{(read(args),0)...};
    }
    template<typename... Args>
    void write(Args ...args){
        (void)std::initializer_list<int>{(write(args),0)...};
    }
}io;

const int N = 1e6 + 10;
vector<int> G[N];
vector<PII> q;
int n, m;
ll a[N], b[N];
ll s[N], c[3];
int color[N];
int fa[N];

int find(int x)
{
    if(fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}

void init()
{
    q.clear();
    for(int i = 1; i <= n; i ++ ) 
    {
        s[i] = 0;
        G[i].clear();
        color[i] = 0;
    }
}

bool dfs(int u, int col)
{
    color[u] = col;
    c[col] += s[u];
    bool flag = true;
    for(auto v : G[u])
    {
        if(color[v] == color[u]) flag = false;
        if(!color[v] && !dfs(v, 3 - col)) flag = false;
    }
    return flag;
}

bool solve()
{
    init();
    n = io.read(), m = io.read();
    for(int i = 1; i <= n; i ++ ) fa[i] = i;
    for(int i = 1; i <= n; i ++ ) a[i] = io.read();
    for(int i = 1; i <= n; i ++ ) b[i] = io.read();

    for(int i = 1; i <= m; i ++ )
    {
        int op = io.read(), a = io.read(), b = io.read();
        if(op == 1) q.push_back({a, b});
        else fa[find(a)] = find(b);
    }

    for(int i = 1; i <= n; i ++ ) s[find(i)] += b[i] - a[i];
    for(auto t : q)
    {
        int a = t.first, b = t.second;
        a = find(a), b = find(b);
        G[a].push_back(b);
        G[b].push_back(a);
    }

    for(int i = 1; i <= n; i ++ )
        if(find(i) == i && !color[i])
        {
            c[1] = c[2] = 0;
            bool flag = dfs(i, 1);
            if(!flag && ((c[1] ^ c[2]) & 1)) return false;
            if(flag && (c[1] != c[2])) return false;
        }

    return true;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = io.read();
    while(T -- ) 
    {
        solve() ? io.write("YES\n") : io.write("NO\n");
    }

    return 0;
}