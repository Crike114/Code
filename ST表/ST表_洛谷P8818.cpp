#include<bits/stdc++.h>
#define int long long
#define inf (LLONG_MAX >> 1)

using namespace std;

int n, m, q, ans = -inf;
vector<vector<int>> amax, amin, anegmax, aposmin, bmax, bmin;

signed main(){
	cin>>n>>m>>q;
	amax.resize(__lg(n) + 5, vector<int>(n + 5));
	amin.resize(__lg(n) + 5, vector<int>(n + 5));
	anegmax.resize(__lg(n) + 5, vector<int>(n + 5));
	aposmin.resize(__lg(n) + 5, vector<int>(n + 5));
	bmax.resize(__lg(m) + 5, vector<int>(m + 5));
	bmin.resize(__lg(m) + 5, vector<int>(m + 5));
	for(int i = 0;i < n;i++){
		int x;
		cin>>x;
		amax[0][i] = x;
		amin[0][i] = x;
		if(x >= 0){
			anegmax[0][i] = -inf;
			aposmin[0][i] = x;
		}
		else{
			anegmax[0][i] = x;
			aposmin[0][i] = inf;
		}
		
	}
	for(int i = 0;i < m;i++){
		int x;
		cin>>x;
		bmax[0][i] = x;
		bmin[0][i] = x;
	}
	for(int j = 1;j <= __lg(n);j++){
		for(int i = 0;i + (1 << j) - 1 < n;i++){
			int p = i + (1 << (j-1));
			amax[j][i] = max(amax[j - 1][i], amax[j - 1][p]);
			amin[j][i] = min(amin[j - 1][i], amin[j - 1][p]);
			anegmax[j][i] = max(anegmax[j - 1][i], anegmax[j - 1][p]);
			aposmin[j][i] = min(aposmin[j - 1][i], aposmin[j - 1][p]);
		}
	}
	for(int j = 1;j <= __lg(m);j++){
		for(int i = 0;i + (1 << j) - 1 < m;i++){
			int p = i + (1 << (j-1));
			bmax[j][i] = max(bmax[j - 1][i], bmax[j - 1][p]);
			bmin[j][i] = min(bmin[j - 1][i], bmin[j - 1][p]);
		}
	}
	while(q--){
		int l1, r1, l2, r2;
		cin>>l1>>r1>>l2>>r2;
		l1--, r1--, l2--, r2--;
		int ka = __lg(r1 - l1 + 1);
		int la = 1 << ka;
		int amx = max(amax[ka][l1], amax[ka][r1 - la + 1]);
		int amn = min(amin[ka][l1], amin[ka][r1 - la + 1]);
		int aneg = max(anegmax[ka][l1], anegmax[ka][r1 - la + 1]);
		int apos = min(aposmin[ka][l1], aposmin[ka][r1 - la + 1]);
		int kb = __lg(r2 - l2 + 1);
		int lb = 1 << kb;
		int bmx = max(bmax[kb][l2], bmax[kb][r2 - lb + 1]);
		int bmn = min(bmin[kb][l2], bmin[kb][r2 - lb + 1]);
		ans = -inf;
		if(amx >= 0){
			ans = max(ans, amx * bmn);
		}
		else{
			ans = max(ans, amx * bmx);
		}
		if(amn >= 0){
			ans = max(ans, amn * bmn);
		}
		else{
			ans = max(ans, amn * bmx);
		}
		if(aneg != -inf){
			if(aneg >= 0){
				ans = max(ans, aneg * bmn);
			}
			else{
				ans = max(ans, aneg * bmx);
			}
		}
		if(apos != inf) {
			if(apos >= 0){
				ans = max(ans, apos * bmn);
			}
			else{
				ans = max(ans, apos * bmx);
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}