#include<bits/stdc++.h>
#define inf 0x3f3f3f3f

using namespace std;

int f, n, m, w, s = 0;
vector<vector<pair<int, int>>> gra;
vector<int> dist, cnt;
vector<bool> vis;

bool spfa(){
	queue<int> q;
	dist.assign(n + 5, inf);
	cnt.assign(n + 5, 0);
	vis.assign(n + 5, 0);
	dist[s] = 0;
	vis[s] = 1;
	cnt[s] = 1;
	q.push(s);
	while(!q.empty()){
		int u = q.front();
		q.pop();
		vis[u] = 0;
		for(auto edge : gra[u]){
			int v = edge.first, w = edge.second;
			if(dist[v] > dist[u] + w){
				dist[v] = dist[u] + w;
				if(vis[v] != 1){
					vis[v] = 1;
					cnt[v]++;
					if(cnt[v] >= n){
						return 1;
					}
					q.push(v);
				}
			}
		}
	}
	return 0;
}

int main(){
	cin>>f;
	while(f--){
		cin>>n>>m>>w;
		dist.resize(n + 5);
		cnt.resize(n + 5);
		vis.resize(n + 5);
		gra.resize(n + 5);
		gra.clear();
		for(int i = 0;i < m;i++){
			int s, e, t;
			cin>>s>>e>>t;
			gra[s].push_back({e, t});
			gra[e].push_back({s, t});
		}
		for(int i = 0;i < w;i++){
			int s, e, t;
			cin>>s>>e>>t;
			gra[s].push_back({e, -t});
		}
		for(int i = 1;i <= n;i++){
			gra[0].push_back({i, 0});
		}
		cout<<(spfa() ? "YES\n" : "NO\n");
	}
}