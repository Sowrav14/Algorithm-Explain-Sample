/*
 * @file Convex Hull example.cpp
 * @author Sowrav Nath
 * @version 0.1
 * @date 2024-06-20
 * @copyright Copyright (c) 2024
 * @problem: https://codeforces.com/contest/166/problem/B
 * @approach: Constructing convex hull (graham scan)
 * @explanation:
 */


#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

struct pt {
    int x, y;
    bool operator == (pt const& t) const {
        return x == t.x && y == t.y;
    }
};

int orientation(pt a, pt b, pt c) {
    int v = a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
    if (v < 0) return -1; // clockwise
    if (v > 0) return +1; // counter-clockwise
    return 0;
}

bool cw(pt a, pt b, pt c, bool include_collinear) {
    int o = orientation(a, b, c);
    return o < 0 || (include_collinear && o == 0);
}
bool collinear(pt a, pt b, pt c) { return orientation(a, b, c) == 0; }

void convex_hull(vector<pt>& a, bool include_collinear = false) {
    // starting point , find the bottom_most point if many at bottom take the left_most.
    pt p0 = *min_element(a.begin(), a.end(), [](pt a, pt b) {
        return make_pair(a.y, a.x) < make_pair(b.y, b.x);
    });
    // sort all points based on polar angle between  each point and the starting point.
    // comparator... (a, b)
    // if orientation of (p0, a, b) -> colinear sort on distance from p0
    // if orientation of (p0, a, b) -> clockwise then a comes first.
    // else b comes first.
    sort(a.begin(), a.end(), [&p0](const pt& a, const pt& b) {
        int o = orientation(p0, a, b);
        if (o == 0)
            return (p0.x-a.x)*(p0.x-a.x) + (p0.y-a.y)*(p0.y-a.y)
                < (p0.x-b.x)*(p0.x-b.x) + (p0.y-b.y)*(p0.y-b.y);
        return o < 0;
    });
    // if we have option to take or discard points that are by default on convex..
    // ex. if (2,5) , (6, 3) on convex then (4, 4) also in convex..
    // so (4, 4) is colinear point on convex... need this??
    if (include_collinear) {
        int i = (int)a.size()-1;
        while (i >= 0 && collinear(p0, a[i], a.back())) i--;
        reverse(a.begin()+i+1, a.end());
    }

    vector<pt> st;
    // in each iteration make sure that the current point and the two before it make a clockwise turn
    // otherwise the previous point is discarded, since it would make a non-convex shape
    for (int i = 0; i < (int)a.size(); i++) {
        while (st.size() > 1 && !cw(st[st.size()-2], st.back(), a[i], include_collinear))
            st.pop_back();
        st.push_back(a[i]);
    }

    if (include_collinear == false && st.size() == 2 && st[0] == st[1])
        st.pop_back();

    a = st;
}
// given two polygon A and B. return if b is strictly inside A.
void solve(){

    int n; cin >> n;
    vector<pt>a,b,c;
    for(int i=0;i<n;i++){
        pt p; cin >> p.x >> p.y;
        a.push_back(p);
        c.push_back(p);
    }
    int m; cin >> m;
    for(int i=0;i<m;i++){
        pt p; cin >> p.x >> p.y;
        b.push_back(p);
        c.push_back(p);
    }

    convex_hull(c, true);

    sort(a.begin(), a.end(), [](pt p1, pt p2){
        return make_pair(p1.x, p1.y) < make_pair(p2.x, p2.y);
    });
    sort(c.begin(), c.end(), [](pt p1, pt p2){
        return make_pair(p1.x, p1.y) < make_pair(p2.x, p2.y);
    });

    
    cout << (a == c ? "YES" : "NO") << endl;

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