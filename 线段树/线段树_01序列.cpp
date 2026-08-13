#include<bits/stdc++.h>
#define lc (rt << 1)
#define rc (rt << 1 | 1)
#define mid ((l + r) >> 1)
using namespace std;

struct node{
	int len, ll, lr, lx, cnt;
};

int n, q;
vector<node> tr0, tr1;
vector<int> a, tag, settag;

void pushu(vector<node>& x, int rt){
	x[rt].len = x[lc].len + x[rc].len;
	x[rt].ll = x[lc].ll;
	if(x[lc].ll == x[lc].len){
		x[rt].ll = x[lc].len + x[rc].ll;
	}
	x[rt].lr = x[rc].lr;
	if(x[rc].lr == x[rc].len){
		x[rt].lr = x[rc].len + x[lc].lr;
	}
	x[rt].lx = max(max(x[lc].lx, x[rc].lx), x[lc].lr + x[rc].ll);
	x[rt].cnt = x[lc].cnt + x[rc].cnt;
}
void rev(int rt){
	swap(tr0[rt].ll, tr1[rt].ll);
	swap(tr0[rt].lr, tr1[rt].lr);
	swap(tr0[rt].lx, tr1[rt].lx);
	swap(tr0[rt].cnt, tr1[rt].cnt);
	if(settag[rt] != -1){
		settag[rt] ^= 1;
		tag[rt] = 0;
	}
	else{
		tag[rt] ^= 1;
	}
}
void setval(int rt){
	if(settag[rt] == 0){
		tr0[rt].ll = tr0[rt].len;
		tr0[rt].lr = tr0[rt].len;
		tr0[rt].lx = tr0[rt].len;
		tr0[rt].cnt = tr0[rt].len;
		tr1[rt].ll = 0;
		tr1[rt].lr = 0;
		tr1[rt].lx = 0;
		tr1[rt].cnt = 0;
	}
	else if(settag[rt] == 1){
		tr1[rt].ll = tr1[rt].len;
		tr1[rt].lr = tr1[rt].len;
		tr1[rt].lx = tr1[rt].len;
		tr1[rt].cnt = tr1[rt].len;
		tr0[rt].ll = 0;
		tr0[rt].lr = 0;
		tr0[rt].lx = 0;
		tr0[rt].cnt = 0;
	}
}
void pushup(int rt){
	pushu(tr0, rt);
	pushu(tr1, rt);
}
void pushdown(int rt){
	if(settag[rt] != -1){
		settag[lc] = settag[rt];
		settag[rc] = settag[rt];
		setval(lc);
		setval(rc);
		tag[rt] = 0;
		settag[rt] = -1;
	}
	if(tag[rt] == 1){
		rev(lc);
		rev(rc);
		tag[rt] = 0;
	}
}
void build(int l, int r, int rt){
	settag[rt] = -1;
	if(l == r){
		if(a[l] == 1){
			tr1[rt].len = 1;
			tr0[rt].len = 1;
			tr1[rt].ll = 1;
			tr1[rt].lr = 1;
			tr1[rt].lx = 1;
			tr1[rt].cnt = 1;
		}
		else if(a[l] == 0){
			tr0[rt].len = 1;
			tr1[rt].len = 1;
			tr0[rt].ll = 1;
			tr0[rt].lr = 1;
			tr0[rt].lx = 1;
			tr0[rt].cnt = 1;
		}
		return;
	}
	build(l, mid, lc);
	build(mid + 1, r, rc);
	pushup(rt);
}
void update(int x, int y, int l, int r, int rt, int op, int num){
	if(x <= l && r <= y){
		if(op == 0){
			settag[rt] = num;
			setval(rt);
		}
		else if(op == 1){
			settag[rt] = num;
			setval(rt);
		}
		else if(op == 2){
			rev(rt);
		}
		return;
	}
	pushdown(rt);
	if(x <= mid){
		update(x, y, l, mid, lc, op, num);
	}
	if(y > mid){
		update(x, y, mid + 1, r, rc, op, num);
	}
	pushup(rt);
}
node query(int x, int y, int l, int r, int rt){
	if(x <= l && r <= y){
		return tr1[rt];
	}
	pushdown(rt);
	bool flagl = 0, flagr = 0;
	vector<node> tmp(4, {0, 0, 0, 0, 0});
	if(x <= mid){
		tmp[2] = query(x, y, l, mid, lc);
		flagl = 1;
	}
	if(y > mid){
		tmp[3] = query(x, y, mid + 1, r, rc);
		flagr = 1;
	}
	if(flagl == 1 && flagr == 1){
		pushu(tmp, 1);
		return tmp[1];
	}
	else if(flagl == 1){
		return tmp[2];
	}
	else if(flagr == 1){
		return tmp[3];
	}
}

void input(){
	cin>>n>>q;
	a.resize(n + 5);
	tr0.resize(4 * n + 5);
	tr1.resize(4 * n + 5);
	tag.resize(4 * n + 5);
	settag.resize(4 * n + 5);
	for(int i = 1;i <= n;i++){
		cin>>a[i];
	}
}
void process(){
	build(1, n, 1);
	while(q--){
		int c, l, r;
		cin>>c>>l>>r;
		l++, r++;
		if(c == 0){
			update(l, r, 1, n, 1, 0, 0);
		}
		else if(c == 1){
			update(l, r, 1, n, 1, 1, 1);
		}
		else if(c == 2){
			update(l, r, 1, n, 1, 2, 0);
		}
		else if(c == 3){
			cout<<query(l, r, 1, n, 1).cnt<<"\n";
		}
		else if(c == 4){
			cout<<query(l, r, 1, n, 1).lx<<"\n";
		}
	}
}

signed main(){
	input();
	process();

	return 0;
}