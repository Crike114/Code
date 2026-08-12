#include<bits/stdc++.h>
#define int long long
using namespace std;

int n, q, mod = 571373, m;
vector<int> a, s, addtag, multag;

void pushup(int rt){
    s[rt] = (s[rt << 1] + s[rt << 1 | 1]) % mod;
}
void pushdown(int l, int r, int rt){
    if(addtag[rt] != 0 || multag[rt] != 1){
        int mid = (l + r) >> 1;
		s[rt << 1] = (s[rt << 1] * multag[rt] + addtag[rt] * (mid - l + 1)) % mod;
        s[rt << 1 | 1] = (s[rt << 1 | 1] * multag[rt] + addtag[rt] * (r - mid)) % mod;
        addtag[rt << 1] = (addtag[rt << 1] * multag[rt] + addtag[rt]) % mod;
        addtag[rt << 1 | 1] = (addtag[rt << 1 | 1] * multag[rt] + addtag[rt]) % mod;
        multag[rt << 1] = (multag[rt << 1] * multag[rt]) % mod;
        multag[rt << 1 | 1] = (multag[rt << 1 | 1] * multag[rt]) % mod;
		addtag[rt] = 0;
		multag[rt] = 1;
    }
}
void build(int l, int r, int rt){
	addtag[rt] = 0;
    multag[rt] = 1;
    if(l == r){
        s[rt] = a[l] % mod;
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
        s[rt] = (s[rt] * mulnum + addnum * (r - l + 1)) % mod;
		multag[rt] = (multag[rt] * mulnum) % mod;
        addtag[rt] = (addtag[rt] * mulnum + addnum) % mod;
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
        sum += quary(x, y, l, mid, rt << 1) % mod;
    }
    if(y > mid){
        sum += quary(x, y, mid + 1, r, rt << 1 | 1) % mod;
    }
    return sum % mod;
}

void init(){
    cin.tie(0)->sync_with_stdio(0);
    cout.tie(0)->sync_with_stdio(0);
}
void input(){
    cin>>n>>q>>m;
    a.resize(n + 5);
    s.resize(4 * n + 5);
	addtag.resize(4 * n + 5);
    multag.resize(4 * n + 5);
    multag.assign(4 * n + 5, 1);
    for(int i = 1;i <= n;i++){
        cin>>a[i];
    }
}
void output(){
    int op, x, y, k;
    for(int i = 1;i <= q;i++){
        cin>>op>>x>>y;
        if(op == 1){
            cin>>k;
            update(x, y, 1, n, 1, 0, k);
        }
        else if(op == 2){
            cin>>k;
            update(x, y, 1, n, 1, k, 1);
        }
        else if(op == 3){
            cout<<quary(x, y, 1, n, 1) % mod<<"\n";
        }
    }
}

signed main(){
    init();
    input();
    build(1, n, 1);
    output();

    return 0;
}