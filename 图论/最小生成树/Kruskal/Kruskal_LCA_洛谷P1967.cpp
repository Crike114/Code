#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cxx __gnu_cxx
#define pbds __gnu_pbds
#define _inf 0x3f3f3f3f
#define inf (INT_MAX >> 1)
#define llinf (LLONG_MAX >> 1)
#define for_0(rangeNum) for(int i = 0;i < rangeNum;i++)
#define for_1(rangeNum) for(int i = 1;i <= rangeNum;i++)
#define lc (mid << 1)
#define rc (mid << 1 | 1)
#define mid ((l + r) >> 1)
#define lg(log2Num) __lg(log2Num)

// #define int long long
// #define int unsigned long long
#define base 131

#define maxn 10005
#define mxlg 15

using namespace std;

struct edge{
	int u, v, w;
};

int n, m, q; // 1e4 5e4 3e4
int dp[maxn][mxlg], minw[maxn][mxlg];
vector<vector<pair<int, int>>> gra;
vector<edge> edges;
vector<int> fa, dep;

int find(int u){
	return fa[u] == u ? u : fa[u] = find(fa[u]);
}
void unite(int u, int v, int w){
	int ru = find(u), rv = find(v);
	if(ru != rv){
		fa[ru] = rv;
		gra[u].push_back({v, w});
		gra[v].push_back({u, w});
	}
}
void kruskal(){
	sort(edges.begin(), edges.end(), [](edge x, edge y){ return x.w > y.w; });
	for_1(n){
		fa[i] = i;
	}
	for_0(m){
		unite(edges[i].u, edges[i].v, edges[i].w);
	}
}

void dfs(int u, int fa, int w){
	dp[u][0] = fa;
	minw[u][0] = w;
	dep[u] = dep[fa] + 1;
	for(int k = 1;k < mxlg;k++){
		dp[u][k] = dp[dp[u][k - 1]][k - 1];
		minw[u][k] = min(minw[u][k - 1], minw[dp[u][k - 1]][k - 1]);
	}
	for(auto x : gra[u]){
		int v = x.first, w = x.second;
		if(v == fa){
			continue;
		}
		dfs(v, u, w);
	}
}

int lca(int u, int v){
	if(find(u) != find(v)){
		return -1;
	}
	int ans = inf;
	if(dep[u] < dep[v]){
		swap(u, v);
	}
	int step = dep[u] - dep[v];
	for_0(mxlg){
		if(step & (1 << i)){
			ans = min(ans, minw[u][i]);
			u = dp[u][i];
		}
	}
	if(u == v){
		return ans;
	}
	for(int i = mxlg - 1;i >= 0;i--){
		if(dp[u][i] != dp[v][i]){
			ans = min(ans, minw[u][i]);
			ans = min(ans, minw[v][i]);
			u = dp[u][i];
			v = dp[v][i];
		}
	}
	ans = min(ans, minw[u][0]);
	ans = min(ans, minw[v][0]);
	return ans;
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	
	cin>>n>>m;
	gra.resize(n + 5);
	fa.resize(n + 5);
	dep.resize(n + 5);
	for_0(m){
		int x, y, z; // 1e5
		cin>>x>>y>>z;
		edges.push_back({x, y, z});
	}
	memset(dp, 0, sizeof(dp));
	memset(minw, 0x3f, sizeof(minw));
	kruskal();
	for_1(n){
		if(dep[i] == 0 && fa[i] == i){
			dep[i] = 1;
			dfs(i, 0, 0x3f3f3f3f);
		}
	}
	cin>>q;
	for_0(q){
		int x, y;
		cin>>x>>y;
		cout<<lca(x, y)<<"\n";
	}
	return 0;
}