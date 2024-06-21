#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 3e5 + 9;
const double inf = 1e100;
const double eps = 1e-9;
const double PI = acos(-1.0);

struct PT {
	int x, y;
	PT(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
	bool operator < (const PT p) const {
		if (x != p.x) return x < p.x;
		return y < p.y;
	}
	bool operator == (const PT p) const {
		return x == p.x and y == p.y;
	}
	PT operator + (const PT p) const { return PT(x+p.x, y+p.y); }
	PT operator - (const PT p) const { return PT(x-p.x, y-p.y); }
	PT operator * (const int c) const { return PT(x*c, y*c); }
	int operator * (const PT p) const { return x*(int)p.x + y*(int)p.y; }
	int operator ^ (const PT p) const { return x*(int)p.y - y*(int)p.x; }
};

bool ccw(PT p, PT q, PT r) { // counter-clockwise
	return ((q-p)^(r-q)) > 0;
}

struct upper {
	set<PT> se;
	set<PT>::iterator it;

	int is_under(PT p) { // 1 -> inside ; 2 -> border
		it = se.lower_bound(p);
		if (it == se.end()) return 0;
		if (it == se.begin()) return p == *it ? 2 : 0;
		if (ccw(p, *it, *prev(it))) return 1;
		return ccw(p, *prev(it), *it) ? 0 : 2;
	}
	void insert(PT p) {
		if (is_under(p)) return;

		if (it != se.end()) while (next(it) != se.end() and !ccw(*next(it), *it, p))
			it = se.erase(it);
		if (it != se.begin()) while (--it != se.begin() and !ccw(p, *it, *prev(it)))
			it = se.erase(it);

		se.insert(p);
	}
};

struct dyn_hull { // 1 -> inside ; 2 -> border
	upper U, L;

	int is_inside(PT p) {
		int u = U.is_under(p), l = L.is_under({-p.x, -p.y});
		if (!u or !l) return 0;
		return max(u, l);
	}
	void insert(PT p) {
		U.insert(p);
		L.insert({-p.x, -p.y});
	}
	int size() {
		int ans = U.se.size() + L.se.size();
		return ans <= 2 ? ans/2 : ans-2;
	}
};


void solve(){

    int n; cin >> n;
    dyn_hull hull;
    for(int i=0;i<n;i++){
        int t; PT p; cin >> t >> p.x >> p.y; 
        if(t == 1){
            hull.insert(p);
        } else {
            cout << (hull.is_inside(p) ? "YES" : "NO") << endl;
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