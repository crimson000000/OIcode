#include<bits/stdc++.h>
using namespace std;
long long a,b,p;

int main(){
	cin>>a>>b>>p;
	long long m=a,n=b,g=p;
	int ans=1%p;
	for(;b;b>>=1){
		if(b&1)
			ans=(long long)ans*a%p;
		a=a*a%p;
	}
	cout<<m<<"^"<<n<<" mod "<<g<<"="<<ans<<endl;
}
