#include<bits/stdc++.h>
using namespace std;

const int N=1e6+10;

int q[N];//序列 

int rev[N];//用来存储翻转的序列 

void msort(int q[],int l,int r){
	if(l>=r) return;//递归边界 
	int mid=l+r>>1;//选取分界点 
	msort(q,l,mid);msort(q,mid+1,r);//递归处理 
	int i=l,j=mid+1,k=0;
	while(i<=mid && j<=r){//双指针算法，把2段里面的最小值放在rev里 
		if(q[i]<q[j]) rev[k++] = q[i++];
		else rev[k++] = q[j++];
	}
	while(i<=mid) rev[k++] =q[i++];//把剩余有序元素放入rev 
	while(j<=r) rev[k++] =q[j++];
	for(int i=l,j=0;i<=r;i++) q[i]=rev[j++];//把rev中元素放回q 
} 

int main(){
	int m;
	cin>>m;
	for(int i=0;i<m;i++) scanf("%d",&q[i]);
	msort(q,0,m-1);
	for(int i=0;i<m;i++) printf("%d ",q[i]);
	return 0; 
}
