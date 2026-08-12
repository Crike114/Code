#include<bits/stdc++.h>
#define int long long
#define maxn LONG_LONG_MAX
#define minn LONG_LONG_MIN
using namespace std;

int n, q;
vector<int> a, s, addtag, settag;

void pushup(int rt){
	s[rt] = max(s[rt << 1], s[rt << 1 | 1]);
}
void pushdown(int rt){
	int lc = rt << 1, rc = rt << 1 | 1;
	if(settag[rt] != minn){
		s[lc] = settag[rt];
		s[rc] = settag[rt];
		settag[lc] = settag[rt];
		settag[rc] = settag[rt];
		addtag[lc] = 0;
		addtag[rc] = 0;
		settag[rt] = minn;
	}
	if(addtag[rt] != 0){
		s[lc] += addtag[rt];
		s[rc] += addtag[rt];
		if (settag[lc] != minn){
			settag[lc] += addtag[rt];
		}
        else{
			addtag[lc] += addtag[rt];
		}
        if (settag[rc] != minn){
			settag[rc] += addtag[rt];
		}
        else{
			addtag[rc] += addtag[rt];
		}
		addtag[rt] = 0;
	}
}
void build(int l, int r, int rt){
	addtag[rt] = 0;
	settag[rt] = minn;
	if(l == r){
		s[rt] = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, rt << 1);
	build(mid + 1, r, rt << 1 | 1);
	s[rt] = max(s[rt << 1], s[rt << 1 | 1]);
}
void update(int x, int y, int l, int r, int rt, int num, int op){
	if(x <= l && r <= y){
		if(op == 1){
			s[rt] = num;
			settag[rt] = num;
			addtag[rt] = 0;
			return;
		}
		else if(op == 2){
			s[rt] += num;
			addtag[rt] += num;
			return;		
		}
	}
	pushdown(rt);
	int mid = (l + r) >> 1;
	if(x <= mid){
		update(x, y, l, mid, rt << 1, num, op);
	}
	if(mid < y){
		update(x, y, mid + 1, r, rt << 1 | 1, num, op);
	}
	pushup(rt);
}
int query(int x, int y, int l, int r, int rt){
	if(x <= l && r <= y){
		return s[rt];
	}
	pushdown(rt);
	int mid = (l + r) >> 1;
	int res = LONG_LONG_MIN;
	if(x <= mid){
		res = max(res, query(x, y, l, mid, rt << 1));
	}
	if(mid < y){
		res = max(res, query(x, y, mid + 1, r, rt << 1 | 1));
	}
	return res;
}

void init(){
	cin.tie(0)->sync_with_stdio(0);
	cout.tie(0)->sync_with_stdio(0);
}
void input(){
	cin>>n>>q;
	a.resize(n + 5);
	for(int i = 1;i <= n;i++){
		cin>>a[i];
	}
}
void preprocess(){
	s.resize(4 * n + 5);
	addtag.resize(4 * n + 5);
	settag.resize(4 * n + 5);
	build(1, n, 1);
}
void output(){
	while(q--){
		int op, l, r, x;
		cin>>op>>l>>r;
		if(op != 3){
			cin>>x;
			update(l, r, 1, n, 1, x, op);
			continue;
		}
		cout<<query(l, r, 1, n, 1)<<"\n";
	}
}

signed main(){
	init();
	input();
	preprocess();
	output();

	return 0;
}