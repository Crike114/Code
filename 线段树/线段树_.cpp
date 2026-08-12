#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;

int n, q;
vector<int> a, b, s, sa, sb, atag, btag;

// adda addb pushup pushdown build update query
void adda(int rt, int len, int num){
	s[rt] = (s[rt] + num * sb[rt]) % mod;
	sa[rt]  = (sa[rt]  + num * len) % mod;
	atag[rt] = (atag[rt] + num) % mod;
}
void addb(int rt, int len, int num){
	s[rt] = (s[rt] + num * sa[rt]) % mod;
	sb[rt]  = (sb[rt]  + num * len) % mod;
	btag[rt] = (btag[rt] + num) % mod;
}
void pushup(int rt){
	sa[rt] = (sa[rt << 1] + sa[rt << 1 | 1]) % mod;
	sb[rt] = (sb[rt << 1] + sb[rt << 1 | 1]) % mod;
	s[rt] = (s[rt << 1] + s[rt << 1 | 1]) % mod;
}
void pushdown(int l, int r, int rt){
	int lc = rt << 1, rc = rt << 1 | 1;
	int mid = (l + r) >> 1;
	int lenl = mid - l + 1, lenr = r - mid;
	if(atag[rt] != 0){
		adda(lc, lenl, atag[rt]);
		adda(rc, lenr, atag[rt]);
        atag[rt] = 0;
    }
    if(btag[rt] != 0){
		addb(lc, lenl, btag[rt]);
		addb(rc, lenr, btag[rt]);
        btag[rt] = 0;
    }
}
void build(int l, int r, int rt){
	atag[rt] = 0;
	btag[rt] = 0;
	if(l == r){
		sa[rt] = a[l];
		sb[rt] = b[l]; 
		s[rt] = a[l] * b[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, rt << 1);
	build(mid + 1, r, rt << 1 | 1);
	pushup(rt);
}
void update(int x, int y, int l, int r, int rt, int num, int op){
	if(x <= l && r <= y){
		int len = r - l + 1;
		if(op == 1){
			adda(rt, len, num);
			return;
		}
		else if(op == 2){
			addb(rt, len, num);
			return;		
		}
	}
	pushdown(l, r, rt);
	int mid = (l + r) >> 1;
	if(x <= mid){
		update(x, y, l, mid, rt << 1, num, op);
	}
	if(y > mid){
		update(x, y, mid + 1, r, rt << 1 | 1, num, op);
	}
	pushup(rt);
}
int query(int x, int y, int l, int r, int rt){
	if(x <= l && r <= y){
		return s[rt] % mod;
	}
	pushdown(l, r, rt);
	int mid = (l + r) >> 1;
	int res = 0;
	if(x <= mid){
		res = (res + query(x, y, l, mid, rt << 1)) % mod;
	}
	if(y > mid){
		res = (res + query(x, y, mid + 1, r, rt << 1 | 1)) % mod;
	}
	return res % mod;
}
// input preprocess output
void input(){
	cin>>n>>q;
	a.resize(n + 5);
	b.resize(n + 5);
	for(int i = 1;i <= n;i++){
		cin>>a[i];
	}
	for(int i = 1;i <= n;i++){
		cin>>b[i];
	}
}
void process(){
	s.resize(4 * n + 5);
    sa.resize(4 * n + 5);
    sb.resize(4 * n + 5);
    atag.resize(4 * n + 5);
    btag.resize(4 * n + 5);
	build(1, n, 1);
	for(int i = 0;i < q;i++){
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
	input();
	process();

	return 0;
}