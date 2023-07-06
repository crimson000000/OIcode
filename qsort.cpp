#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int q[N];//序列 

void qsort(int q[],int l,int r){
	if(l>=r) return;//递归终点 
	int s=q[l+r>>1],i=l-1,j=r+1;//s为标准值，i为左指针，j为右指针 
	while(i<j){
		do i++;while(q[i]<s);
		do j--;while(q[j]>s);
		if(i<j) swap(q[i],q[j]);//出现逆序，交换 
	}
	qsort(q,l,j);qsort(q,j+1,r);//递归处理左右两段 
} 

int main(){
	int m;
	cin>>m;
	for(int i=0;i<m;i++) scanf("%d",&q[i]);
	qsort(q,0,m-1);
	for(int i=0;i<m;i++) printf("%d ",q[i]);
	return 0; 
}
