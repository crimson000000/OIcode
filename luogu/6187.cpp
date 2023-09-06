#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using PII = pair<ll, ll>;

class IO{
private:
    static const unsigned int SIZE=1<<23;
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
int a[N];
int n, m;
ll f[N];

int gcd(int a, int b)
{
    int az = __builtin_ctz(a), bz = __builtin_ctz(b), z = min(az, bz);
    b >>= bz;
    while (a)
    {
        a >>= az; int diff = a - b; az = __builtin_ctz(diff);
        b = min(a, b), a = abs(diff);
    }
    return b << z;
}

int w, cnt[N], b[N];
void counting_sort()
{
    for(int i = 1; i <= n; i ++) cnt[a[i]] ++;
    for(int i = 1; i <= w; i ++) cnt[i] += cnt[i - 1];
    for(int i = n; i; i --) b[cnt[a[i]] --] = a[i];
    swap(a, b);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = io.read(), m = io.read();
    for(int i = 1; i <= n; i ++ ) 
    {
        a[i] = io.read();
        w = a[i] > w ? a[i] : w;
    }
    
    counting_sort();
    // for(int i = 0; i < n; i ++ ) cout << a[i] << ' ';
    // puts("");

    while(m -- )
    {
        int k = io.read();
        if(!k || n == 1)
        {
            if(f[0]) io.write(f[0], '\n');
            else
            {
                ll ans = 0;
                for(int i = 1; i <= n; i ++ ) ans += (ll)a[i] * a[i];
                f[0] = ans;
                io.write(ans, '\n');
            }
            continue;
        }
        
        ll p = n / gcd(n, k);
        if(f[p])
        {
            io.write(f[p], '\n');
            continue;
        }

        ll ans = 0;
        for(int i = 1; i <= n; i += p)
        {
            for(int j = 0; j < p - 2; j ++ ) ans += (ll)a[i + j] * a[i + j + 2];
            ans += ((ll)a[i] * a[i + 1] + (ll)a[i + p - 1] * a[i + p - 2]);
        }

        io.write(ans, '\n');
        f[p] = ans;
    }

    return 0;
}