/*
 * @file Closest Pair of Point - Sweep Line.cpp
 * @author Sowrav Nath
 * @version 0.1
 * @date 2024-06-19
 * @copyright Copyright (c) 2024
 * @problem: Closest Pair of Points
 * @approach: Closest Pair of Point - Line Sweep Algorighms....
 * @explanation: https://www.geeksforgeeks.org/closest-pair-of-points-using-sweep-line-algorithm/
 *              Both algorithm has some failure corner case of CSES problem.
 *              See these how they work in Line Sweep.
 *              If necessary use Divide and Conquer Method... 
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define x first
#define y second
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
int n;
vector<pair<int,int>>P;

int dist2(pair<int, int> a, pair<int, int> b) {
	return 1LL * (a.x - b.x) * (a.x - b.x) + 1LL * (a.y - b.y) * (a.y - b.y);
}
// return the indices of points whose distance is minimum among all points.
pair<int,int> closest_pair() {
	assert(n >= 2);
	vector<pair<pair<int,int>,int>> p(n);
	for (int i=0;i<n;i++) p[i] = {P[i], i};
	sort(p.begin(), p.end());
	int l = 0, r = 2;
	int ans = dist2(p[0].x, p[1].x);
	pair<int,int> ret = {p[0].y, p[1].y};
	while (r < n) {
		while (l < r && 1LL * (p[r].x.x - p[l].x.x) * (p[r].x.x - p[l].x.x) >= ans) l++;
		for (int i = l; i < r; i++) {
			int nw = dist2(p[i].x, p[r].x);
			if (nw < ans) {
				ans = nw;
				ret = {p[i].y, p[r].y};
			}
		}
		r++;
	}
	return ret;
}

// Return distance(d^2) of closest pair of points.....
int closestPair() {
	// Sort them according to their x-coordinates
	sort(P.begin(), P.end());
 
	// Minimum distance b/w points seen so far
	int d = INT_MAX;
 
	// Keeping the points in increasing order
	set<pair<int,int>> st;
	st.insert({P[0].first, P[0].second});
 
	for (int i=1;i<n;i++){
        // If the current point is (x, y) and there is a point to the left within a distance of less than d,  
        // the x coordinate of such a point must be between [x – d, x] and the y coordinate must be between [y – d, y+ d]. 
        // Thus, it suffices to only consider points that are located in those ranges. We can achieve this search in O(logN) time by using set st.
		auto l = st.lower_bound({P[i].first - d, P[i].second - d});
		auto r = st.upper_bound({P[i].first, P[i].second + d});
		if (l == st.end()) continue;
 
		for (auto p=l;p!=r;p++) {
			pair<int,int> val = *p;
			int dis = (P[i].first - val.first) * (P[i].first - val.first) + (P[i].second - val.second) * (P[i].second - val.second);
			// Updating the minimum distance dis
			if (d > dis) d = dis;
		}
		st.insert({P[i].first, P[i].second});
	}
 
	return d;
}


void solve(){

    cin >> n;
    for(int i=0;i<n;i++){
        int a, b; cin >> a >> b;
        P.push_back({a, b});
    }

    pair<int,int>id = closest_pair();
    cout << dist2(P[id.x], P[id.y]);

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