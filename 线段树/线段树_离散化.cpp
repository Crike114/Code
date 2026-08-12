#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;

struct R{
	int op, x, y, k;
};

int n, m, cnt;
vector<int> a, s, addtag, multag, len, xs;
vector<R> r;

void pushup(int rt){
    s[rt] = (s[rt << 1] + s[rt << 1 | 1]);
	len[rt] = len[rt << 1] + len[rt << 1 | 1];
}
void pushdown(int l, int r, int rt){
    if(addtag[rt] != 0 || multag[rt] != 1){
        int mid = (l + r) >> 1;
        int lc = rt << 1, rc = rt << 1 | 1;
        s[lc] = s[lc] * multag[rt] + addtag[rt] * len[lc];
        s[rc] = s[rc] * multag[rt] + addtag[rt] * len[rc];
        addtag[lc] = addtag[lc] * multag[rt] + addtag[rt];
        addtag[rc] = addtag[rc] * multag[rt] + addtag[rt];
        multag[lc] = multag[lc] * multag[rt];
        multag[rc] = multag[rc] * multag[rt];
        addtag[rt] = 0;
        multag[rt] = 1;
    }
}
void build(int l, int r, int rt){
	addtag[rt] = 0;
    multag[rt] = 1;
    if(l == r){
        s[rt] = a[l];
		len[rt] = xs[l + 1] - xs[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, rt << 1);
    build(mid + 1, r, rt << 1 | 1);
    pushup(rt);
}
void update(int x, int y, int l, int r, int rt, int addnum, int mulnum){
	if(x > r || y < l){
		return;
	}
    if(x <= l && r <= y){
		s[rt] = s[rt] * mulnum + addnum * len[rt];
        multag[rt] = multag[rt] * mulnum;
        addtag[rt] = addtag[rt] * mulnum + addnum;
		return;
    }
    pushdown(l, r, rt);
    int mid = (l + r) >> 1;
    if(x <= mid){
        update(x, y, l, mid, rt << 1, addnum, mulnum);
    }
    if(y > mid){
        update(x, y, mid + 1, r, rt << 1 | 1, addnum, mulnum);
    }
    pushup(rt);
}
int quary(int x, int y, int l, int r, int rt){
	if(x > r || y < l){
		return 0;
	}
    int sum = 0, mid = (l + r) >> 1;
    if(x <= l && r <= y){
        return s[rt];
    }
    pushdown(l, r, rt);
    if(x <= mid){
        sum += quary(x, y, l, mid, rt << 1);
    }
    if(y > mid){
        sum += quary(x, y, mid + 1, r, rt << 1 | 1);
    }
    return sum;
}

void init(){
    cin.tie(0)->sync_with_stdio(0);
    cout.tie(0)->sync_with_stdio(0);
}
void input(){
    cin>>n>>m;
	r.resize(m + 5);
    for(int i = 1;i <= m;i++){
        cin>>r[i].op>>r[i].x>>r[i].y;
        if(r[i].op == 1){
            cin>>r[i].k;
        }
		xs.push_back(r[i].x);
        xs.push_back(r[i].y + 1);
    }
	xs.push_back(1);
    xs.push_back(n + 1);
}
void preprocess(){
	sort(xs.begin(), xs.end());
	xs.erase(unique(xs.begin(), xs.end()), xs.end());
	cnt = xs.size();  

    a.resize((cnt - 1) + 5);
    s.resize(4 * (cnt - 1) + 5);
	len.resize(4 * (cnt - 1) + 5);
	addtag.resize(4 * (cnt - 1) + 5);
    multag.resize(4 * (cnt - 1) + 5);
    multag.assign(4 * (cnt - 1) + 5, 1);
	for(int i = 0;i < cnt - 1;i++){
        int left = xs[i];
        int right = xs[i + 1] - 1;
        int length = xs[i + 1] - xs[i];
        a[i] = (left + right) * length / 2;
    }
	build(0, cnt - 2, 1);
}
void output(){
    for(int i = 1;i <= m;i++){
		auto &op = r[i];
        int l = lower_bound(xs.begin(), xs.end(), op.x) - xs.begin();
        int r = lower_bound(xs.begin(), xs.end(), op.y + 1) - xs.begin();
        if(op.op == 1){
            update(l, r - 1, 0, cnt - 2, 1, op.k, 1);
        }
		else{
            cout<<quary(l, r - 1, 0, cnt - 2, 1)<<"\n";
        }
    }
}

signed main(){
    init();
    input();
	preprocess();
    output();

    return 0;
}