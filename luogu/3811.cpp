#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int inv[1000010];

LL phi(LL n){
	LL res=n;
	for(int i=2;i<n/i;i++){
		if(n%i==0){
			res=res/i*(i-1);
			while(n%i==0) n/=i;
		}
	}
	if(n>1) res=res/n*(n-1);
	return res;
}

LL qmi(LL a,LL b,LL p){
	LL res=1%p,t=a;
	while(b){
		if(b&1) res=res*t%p;
		t=t*t%p;
		b>>=1;
	}
	return res;
}

int main(){
	LL a,b;
	cin>>a>>b;
	inv[1]=1;
	puts("1");
	for(register int i=2;i<=a;i++){
		inv[i]=(b-b/i)*inv[b%i]%b;
		printf("%d\n",inv[i]);
	}
	return 0;
}
