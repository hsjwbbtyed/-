//without  optimize
#include<iostream>
#include<queue>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>

using namespace std;

int g[310][310];
int n,m,a,b,c,Min_n[310],mmax=-1;    //Min_n[i] 是 
bool u[310];
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i){
        scanf("%d%d%d",&a,&b,&c);
        g[a][b]=c;
        g[b][a]=c;
    }
    memset(Min_n,0x7f,sizeof(Min_n));    
    Min_n[1]=0;
    memset(u,1,sizeof(u));
    for(int i=1;i<=n;++i){
        int k=0;
        for(int j=1;j<=n;j++)
            if(u[j]&&(Min_n[j]<Min_n[k]))
                k=j;
        u[k]=0;
        for(int j=1;j<=n;j++)
            if(u[j] && g[k][j]!=0 && g[k][j]<Min_n[j])
                Min_n[j]=g[k][j];
    }
    for(int i=1;i<=n;++i){
        if(Min_n[i]>mmax)
            mmax=minn[i];
    }
    printf("%d %d",n-1,mmax);
    return 0;
}




//optimize by heap

struct node{
	int p,d;
};

bool operator <(const node &a,const node &b){
	return a.d > b.d;
}

int n,m,ans,dist[301];
bool mark[301];
int sz,to[30001],v[30001],pre[30001],last[301];
priority_queue<node> q;

void Ins(int a,int b,int c){
	sz++;to[sz]=b;v[sz]=c;pre[sz]=last[a];last[a]=sz;
}

void init(){
	int i,a,b,c;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++){
		scanf("%d%d%d",&a,&b,&c);
		Ins(a,b,c);Ins(b,a,c);
	}
}

void solve(){
	int num=0,i,now;
	memset(dist,127,sizeof(dist));
	dist[1]=0;
	node P;
	P.p=1;P.d=0;
	q.push(P);
	while(!q.empty()){
		P=q.top();
		q.pop();
		now=P.p;
		if(mark[now]) continue;
		mark[now]=1;
		ans=max(ans,dist[now]);
		num++;
		if(num==n) break;
		for(i=last[now];i;i=pre[i]){
			if(v[i]<dist[to[i]]){
				dist[to[i]]=v[i];
				P.p=to[i];P.d=v[i];
				q.push(P);
			}
		}
	}
	printf("%d %d\n",num-1,ans);
}

int main(){
	init();
	solve();
	return 0;
}
