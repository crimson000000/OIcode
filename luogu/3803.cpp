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
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const double PI = acos(-1);
const int N = 3e6 + 10;
struct Complex
{
    double a, b;
    Complex() 
    {
        a = 0, b = 0;
    }

    Complex(double real, double imag): a(real), b(imag) {}

    Complex operator + (const Complex& x) const
    {
        return Complex(a + x.a, b + x.b);
    }

    Complex operator - (const Complex& x) const
    {
        return Complex(a - x.a, b - x.b);
    }

    Complex operator * (const Complex& x) const
    {
        return Complex(a * x.a - b * x.b, a * x.b + b * x.a);
    }
}F[N], G[N];

void FFT(Complex a[], int lim, int opt)
{
    if(lim == 1) return;
    Complex a1[lim >> 1], a2[lim >> 1];
    for(int i = 0; i < lim; i += 2)
        a1[i >> 1] = a[i], a2[i >> 1] = a[i + 1];
    FFT(a1, lim >> 1, opt);
    FFT(a2, lim >> 1, opt);
    Complex wn = Complex(cos(2.0 * PI / lim), opt * sin(2.0 * PI / lim));
    Complex w = Complex(1, 0);
    for(int k = 0; k < (lim >> 1); k ++ )
    {
        a[k] = a1[k] + w * a2[k];
        a[k + lim / 2] = a1[k] - w * a2[k];
        w = w * wn;
    }
}

int n, m;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 0; i <= n; i ++ ) scanf("%lf", &F[i].a);
    for(int i = 0; i <= m; i ++ ) scanf("%lf", &G[i].a);

    int lim = 1;
    while(lim <= n + m) lim <<= 1;
    FFT(F, lim, 1), FFT(G, lim, 1);

    for(int i = 0; i <= lim; i ++ ) F[i] = F[i] * G[i];
    FFT(F, lim, -1);

    for(int i = 0; i <= n + m; i ++ ) cout << (int)(F[i].a / lim + 0.5) << ' ';

    return 0;
}
