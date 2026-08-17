#include<bits/stdc++.h>
#define inf 0x3f3f3f3f

using namespace std;

int n, m, s = 0;
vector<vector<pair<int, int>>> gra;
vector<int> dist, cnt;
vector<bool> vis;

bool spfa(){
	dist.assign(n + 5, inf);
	cnt.assign(n + 5, 0);
	vis.assign(n + 5, 0);
	queue<int> q;
	dist[s] = 0;
	q.push(s);
	vis[s] = 1;
	cnt[s] = 1;
	while(!q.empty()){
		int u = q.front();
		q.pop();
		vis[u] = 0;
		for(auto x : gra[u]){
			int v = x.first, w = x.second;
			if(dist[v] > dist[u] + w){
				dist[v] = dist[u] + w;
				if(vis[u] != 1){
					q.push(v);
					vis[v] = 1;
					cnt[v]++;
					if(cnt[v] > n){
						return 0;
					}
				}
			}
		}
	}
	return 1;
}

int main(){
	cin>>n>>m;
	gra.resize(n + 5);
	dist.resize(n + 5);
	dist.assign(n + 5, inf);
	vis.resize(n + 5);
	for(int i = 0;i < m;i++){
		int u, v, w;
		cin>>v>>u>>w;
		gra[u].push_back({v, w});
	}
	for(int i = 1;i <= n;i++){
		gra[0].push_back({i, 0});
	}
	if(spfa() == 1){
		for(int i = 1;i <= n;i++){
			cout<<dist[i]<<" ";
		}
		cout<<"\n";
		return 0;
	}
	cout<<"NO\n";
	return 0;
}