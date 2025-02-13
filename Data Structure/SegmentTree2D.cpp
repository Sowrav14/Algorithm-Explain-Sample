/*
 * @file SegmentTree2D.cpp
 * @author Sowrav Nath
 * @version 0.1
 * @date 2024-07-02
 * @copyright Copyright (c) 2024
 * @problem: CSES Forest Query II 
 * @approach: Two dimensional Segment Tree
 * @explanation:
 */

#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 1000 + 10;
int a[N][N];

// Structuring Segment Tree...
struct SegmentTree {
    int n,m;
	int tree[4010][4010];
	SegmentTree() {
		memset(tree, 0, sizeof(tree));
	}
    SegmentTree(int n_, int m_) : n(n_), m(m_) {
        memset(tree, 0, sizeof(tree));
    }
	void build_y(int vx, int lx, int rx, int vy, int ly, int ry) {
        if (ly == ry) {
            if (lx == rx)
                tree[vx][vy] = a[lx][ly];
            else
                tree[vx][vy] = tree[vx*2][vy] + tree[vx*2+1][vy];
        } else {
            int my = (ly + ry) / 2;
            build_y(vx, lx, rx, vy*2, ly, my);
            build_y(vx, lx, rx, vy*2+1, my+1, ry);
            tree[vx][vy] = tree[vx][vy*2] + tree[vx][vy*2+1];
        }
    }

    void build_x(int vx, int lx, int rx) {
        if (lx != rx) {
            int mx = (lx + rx) / 2;
            build_x(vx*2, lx, mx);
            build_x(vx*2+1, mx+1, rx);
        }
        build_y(vx, lx, rx, 1, 1, m);
    }

    int sum_y(int vx, int vy, int tly, int try_, int ly, int ry) {
        if (ly > ry) return 0;
        if (ly == tly && try_ == ry) return tree[vx][vy];
        int tmy = (tly + try_) / 2;
        return sum_y(vx, vy*2, tly, tmy, ly, min(ry, tmy)) + sum_y(vx, vy*2+1, tmy+1, try_, max(ly, tmy+1), ry);
    }

    int sum_x(int vx, int tlx, int trx, int lx, int rx, int ly, int ry) {
        if (lx > rx) return 0;
        if (lx == tlx && trx == rx) return sum_y(vx, 1, 1, m, ly, ry);
        int tmx = (tlx + trx) / 2;
        return sum_x(vx*2, tlx, tmx, lx, min(rx, tmx), ly, ry) + sum_x(vx*2+1, tmx+1, trx, max(lx, tmx+1), rx, ly, ry);
    }

    void update_y(int vx, int lx, int rx, int vy, int ly, int ry, int x, int y, int new_val) {
        if (ly == ry) {
            if (lx == rx) tree[vx][vy] = new_val;
            else tree[vx][vy] = tree[vx*2][vy] + tree[vx*2+1][vy];
        } else {
            int my = (ly + ry) / 2;
            if (y <= my) update_y(vx, lx, rx, vy*2, ly, my, x, y, new_val);
            else update_y(vx, lx, rx, vy*2+1, my+1, ry, x, y, new_val);
            tree[vx][vy] = tree[vx][vy*2] + tree[vx][vy*2+1];
        }
    }

    void update_x(int vx, int lx, int rx, int x, int y, int new_val) {
        if (lx != rx) {
            int mx = (lx + rx) / 2;
            if (x <= mx) update_x(vx*2, lx, mx, x, y, new_val);
            else update_x(vx*2+1, mx+1, rx, x, y, new_val);
        }
        update_y(vx, lx, rx, 1, 1, m, x, y, new_val);
    }
};


void solve(){

    int n,q; cin >> n >> q;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            char ch; cin >> ch;
            a[i][j] = (ch == '.' ? 0 : 1);
        }
    }

    SegmentTree st(n, n);
    st.build_x(1, 1, n);
    // cout << st.sum_x(1, 1, n, 4, 4, 1, 4) << endl;
    while(q--){
		int t; cin >> t;
		if(t == 1){
			int x,y; cin >> x >> y;
			a[x][y] = 1 - a[x][y];
			st.update_x(1, 1, n, x, y, a[x][y]);
		} else{
			int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        	cout << st.sum_x(1, 1, n, x1, x2, y1, y2) << endl;
		}
    }


}


signed main(){
    Fast_IO()
    int t = 1;
    // cin >> t;
    for(int i=1;i<=t;i++){
        // cout << "Case " << t << ": ";
        solve();
    }
}