#include<bits/stdc++.h>
#define minx LONG_LONG_MIN
#define int long long
using namespace std;

struct node{
	int mx = 0, smx = 0, mxc = 0, smxc = 0;
};

int n, q;
vector<int> a;
vector<node> tr;

node mergeans(node x, node y){
	node ans;
	if(x.mx > y.mx){
		ans.mx = x.mx;
		ans.mxc = x.mxc;
		if(x.smx > y.mx){
			ans.smx = x.smx;
			ans.smxc = x.smxc;
		}
		else if(x.smx < y.mx){
			ans.smx = y.mx;
			ans.smxc = y.mxc;
		}
		else if(x.smx == y.mx){
			ans.smx = x.smx;
			ans.smxc = x.smxc + y.mxc;
		}
	}
	else if(x.mx < y.mx){
		ans.mx = y.mx;
		ans.mxc = y.mxc;
		if(y.smx > x.mx){
			ans.smx = y.smx;
			ans.smxc = y.smxc;
		}
		else if(y.smx < x.mx){
			ans.smx = x.mx;
			ans.smxc = x.mxc;
		}
		else if(y.smx == x.mx){
			ans.smx = x.mx;
			ans.smxc = x.mxc + y.smxc;
		}
	}
	else if(x.mx == y.mx){
		ans.mx = x.mx;
		ans.mxc = x.mxc + y.mxc;
		if(x.smx > y.smx){
			ans.smx = x.smx;
			ans.smxc = x.smxc;
		}
		else if(x.smx < y.smx){
			ans.smx = y.smx;
			ans.smxc = y.smxc;
		}
		else if(x.smx == y.smx){
			ans.smx = x.smx;
			ans.smxc = x.smxc + y.smxc;
		}
	}
	if(ans.smx == minx){
		ans.smxc = 0;
	}
	return ans;
}
// pushup build update query
void pushup(int rt){
	int lc = rt << 1, rc = rt << 1 | 1;
	tr[rt] = mergeans(tr[lc], tr[rc]);
}
void build(int l, int r, int rt){
	if(l == r){
		tr[rt].mx = a[l];
		tr[rt].mxc = 1;
		tr[rt].smx = minx;
		tr[rt].smxc = 0;
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, rt << 1);
	build(mid + 1, r, rt << 1 | 1);
	pushup(rt);
}
void update(int pos, int l, int r, int rt, int num){
	if(l == r){
		tr[rt].mx = num;
		tr[rt].mxc = 1;
		tr[rt].smx = minx;
		tr[rt].smxc = 0;
		return;
	}
	int mid = (l + r) >> 1;
	if(pos <= mid){
		update(pos, l, mid, rt << 1, num);
	}
	else if(pos > mid){
		update(pos, mid + 1, r, rt << 1 | 1, num);
	}
	pushup(rt);
}
node query(int x, int y, int l, int r, int rt){
	if(x <= l && r <= y){
		return tr[rt];
	}
	int mid = (l + r) >> 1;
	bool isl = 0, isr = 0;
	node tmp1, tmp2;
	if(x <= mid){
		tmp1 = query(x, y, l, mid, rt << 1);
		isl = 1;
	}
	if(y > mid){
		tmp2 = query(x, y, mid + 1, r, rt << 1 | 1);
		isr = 1;
	}
	if(isl == 1 && isr == 1){
		return mergeans(tmp1, tmp2);
	}
	else if(isl == 1){
		return tmp1;
	}
	else if(isr == 1){
		return tmp2;
	}
}
// input process output
void input(){
	cin>>n>>q;
	a.resize(n + 5);
	tr.resize(4 * n + 5);
	for(int i = 1;i <= n;i++){
		cin>>a[i];
	}
}
void process(){
	build(1, n, 1);
	while(q--){
		int op, x, y;
		cin>>op>>x>>y;
		if(op == 1){
			update(x, 1, n, 1, y);
		}
		else if(op == 2){
			cout<<query(x, y, 1, n, 1).smxc<<"\n";
		}
	}
}

signed main(){
	input();
	process();

	return 0;
}