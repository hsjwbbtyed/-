#include<cstdio>
#include<vector>
using namespace std;
const int N=100010;

int n,m,vis[N],cnt=0;



vector<int> G[N];

void addedge(int u,int v){     // without weight
	G[u].push_back(v);G[v].push_back(u);
}

//with weight 
/*-------------------------------------------------
struct Edge{
	int next,weight;
};

void addedge_w(int u,int v,int w){  
	Edge e1;  e1.next=v; e1.weight=w;
	G[u].push_back(e1);
	Edge e2;  e2.next=u; e2.weight=w;
	G[v].push_back(e2);
}
---------------------------------------------------*/

void dfs(int u){
	printf("%d ",u);
	vis[u]=1;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i].next, w=G[u][i].weight; 
		if(vis[v])continue;
		dfs(v);
	}
}
int main(){
	printf("Please input count of the Graph and start point\n") ;
	int start;
	scanf("%d",&cnt,&start);
		printf("And then input each pair of relationship\n"); 
	for(int i=0;i<cnt-1;i++){
		scanf("%d%d",&n,&m);
		addedge(n,m);
	}
	dfs(start);
}
