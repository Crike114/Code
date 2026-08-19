#include<bits/stdc++.h>
#define lg(xyz) __lg(xyz) 
#define lg2n lg(500005)

using namespace std;

int n, m, s;
int dp[500005][lg2n + 5];
vector<vector<int>> tr;
vector<int> dep;

void dfs(int u, int fa){
    dp[u][0] = fa;
    dep[u] = dep[fa] + 1;
    for(auto x : tr[u]){
        if(x != fa){
            dfs(x, u);
        }
    }
}
int lca(int u, int v){
    if(dep[u] < dep[v]){
        swap(u, v);
    }
    while(dep[u] > dep[v]){
        u = dp[u][lg(dep[u] - dep[v])];
    }
    if(u == v){
        return u;
    }
    for(int i = lg(dep[u] - 1);i >= 0;i--){
        if(dp[u][i] != dp[v][i]){
            u = dp[u][i], v = dp[v][i];
        }
    }
    return dp[u][0];
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
	cin>>n>>m>>s;
	tr.resize(n + 5);
	dep.resize(n + 5);
	for(int i = 0;i < n - 1;i++){
		int u, v;
		cin>>u>>v;
		tr[u].push_back(v);
		tr[v].push_back(u);
	}
	dfs(s, s);
    for(int j = 1;j <= lg2n;j++){
        for(int i = 1;i <= n;i++){
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
        }
    }
	while(m--){
		int a, b;
		cin>>a>>b;
		cout<<lca(a, b)<<"\n";
	}
}