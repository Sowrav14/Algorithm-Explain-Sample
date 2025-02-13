/*
 * @file LIne Intersection.cpp
 * @author Sowrav Nath
 * @version 0.1
 * @date 2024-06-16
 * @copyright Copyright (c) 2024
 * @problem: Given two Line segment determine whether they intercepto or not.
 * @approach: Orientation check
 * @explanation: https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/?ref=lbp
 *              *1. Orientation(a, b, c) : Linear, clockwise, counter-clockwise
 *                  - slope(a, b) == slope(b, c) => Linear
 *                  - slope(a, b) > slope(b, c) => clockwise
 *                  - slope(a, b) < slope(b, c) => counter-clockwise
 *              *2 . OnSegment(a, b, c) : colinear points. if b lies between line(a, c)
 *              *3. doIntersect(p1, q1, p2, q2):
 *                  - General case : they intersect if following true.
 *                      ` orientation(p1, q1, p2) != orientation(p1, q1, q2)
 *                      ` orientation(p2, q2, p1) != orientation(p2, q2, q1)
 *                  - Special Case : any of following true.
 *                      ` p1, q1, p2 are colinear and p2 lies between line(p1, q1)
 *                      ` p1, q1, q2 are colinear and q2 lies between line(p1, q1)
 *                      ` p2, q2, p1 are colinear and p1 lies between line(p2, q2)
 *                      ` p2, q2, q1 are colinear and q1 lies between line(p2, q2)
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

struct Point{
    int x,y;
};

bool onSegment(Point p, Point q, Point r) { 
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && 
		q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) 
	return true; 

	return false; 
}

int orientation(Point p, Point q, Point r) {
	int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y); 

	if (val == 0) return 0;
	return (val > 0)? 1: 2;
} 


bool doIntersect(Point p1, Point q1, Point p2, Point q2) { 
	int o1 = orientation(p1, q1, p2); 
	int o2 = orientation(p1, q1, q2); 
	int o3 = orientation(p2, q2, p1); 
	int o4 = orientation(p2, q2, q1); 

	if (o1 != o2 && o3 != o4) return true; 

	if (o1 == 0 && onSegment(p1, p2, q1)) return true; 
	if (o2 == 0 && onSegment(p1, q2, q1)) return true; 
	if (o3 == 0 && onSegment(p2, p1, q2)) return true; 
	if (o4 == 0 && onSegment(p2, q1, q2)) return true; 

	return false;
} 


void solve(){

    // line is defined by points (p, q)
    Point p1, q1;   // Line 1
    cin >> p1.x >> p1.y >> q1.x >> q1.y;
    Point p2, q2;   // Line 1
    cin >> p2.x >> p2.y >> q2.x >> q2.y;

    cout << (doIntersect(p1, q1, p2, q2) ? "YES" : "NO") << endl;

}


signed main(){
    Fast_IO()
    int t = 1;
    cin >> t;
    for(int i=1;i<=t;i++){
        // cout << "Case " << t << ": ";
        solve();
    }
}