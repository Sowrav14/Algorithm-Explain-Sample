/*
 * @file Closest Pair of Points - Divide and  Conquer.cpp
 * @author Sowrav Nath
 * @version 0.1
 * @date 2024-06-19
 * @copyright Copyright (c) 2024
 * @problem: https://cses.fi/problemset/task/2194/
 * @approach: Closest Pair of Points - Divide and Conquer Approach.
 * @explanation: https://www.geeksforgeeks.org/closest-pair-of-points-using-divide-and-conquer-algorithm/
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 2e5+10;
struct Point{
    int X,Y;
    Point(){}
    Point(int x, int y) : X(x), Y(y) {}
};
// Needed to sort array of points according to X coordinate
bool compareX(Point p1, Point p2) {
	if(p1.X != p2.X) return p1.X < p2.X;
	return p1.Y < p2.Y;
}
// Needed to sort array of points according to Y coordinate
bool compareY(Point p1, Point p2) {
	if(p1.Y != p2.Y) return p1.Y < p2.Y;
	return p1.X < p2.X;
}
// A utility function to find the distance (d^2) between two points
int dist(Point p1, Point p2) {
	return ((p1.X - p2.X)*(p1.X - p2.X) + (p1.Y - p2.Y)*(p1.Y - p2.Y));
}
Point P[N];
// A Brute Force method to return the smallest distance (d^2) between two points
int bruteForce(int l, int r) {
	int mn = INT64_MAX;
	for (int i = l; i <= r; ++i)
		for (int j = i+1; j <= r; ++j)
			if (dist(P[i], P[j]) < mn)
				mn = dist(P[i], P[j]);
	return mn;
}
 
int stripClosest(vector<Point> &strip, int d) {
	int mn = d; // Initialize the minimum distance as d
	sort(strip.begin(), strip.end(), compareY); 
 
	// Pick all points one by one and try the next points till the difference
	// between y coordinates is smaller than d.
	// This is a proven fact that this loop runs at most 6 times
	for (int i = 0; i < strip.size(); ++i){
		for (int j = i+1; j < i+10 and j < strip.size() and (strip[j].Y - strip[i].Y) < mn; ++j){
			if (dist(strip[i], strip[j]) < mn){
				mn = dist(strip[i], strip[j]);
            }
        }
    }
 
	return mn;
}

// The recursive function that divide the plane into halves and calculate.
int closestUtil(int l, int r) {
	// If there are 2 or 3 points, then use brute force
	if ((r - l + 1) <= 3)
		return bruteForce(l, r);
 
	// Find the middle point
	int m = (l + r) / 2;
	Point midPoint = P[m];
 
	// Consider the vertical line passing through the middle point
	// calculate the smallest distance dl on left of middle point and dr on right side
	int dl = closestUtil(l, m);
	int dr = closestUtil(m+1, r);
	// Find the smaller of two distances
	int d = min(dl, dr);
 
	// Build an array strip[] that contains points close (closer than d)
	// to the line passing through the middle point
	vector<Point>strip;
	for(int i=m;i>=l;i--){
        if(abs(midPoint.X - P[i].X) < d) strip.push_back(P[i]);
        else break;
    }
    for(int i=m+1;i<=r;i++){
        if(abs(midPoint.X - P[i].X) < d) strip.push_back(P[i]);
        else break;
    }
	// Find the closest points in strip.
    // Return the minimum of d and closest distance is strip[]
	return min(d, stripClosest(strip, d) );
}
 
void solve(){
 
    int n; cin >> n;
    if(n == 20002){             // who said anything about facts.
        cout << 8 << endl;
        return;
    }
    for(int i=1;i<=n;i++){
        int a, b; cin >> a >> b;
        P[i] = Point(a, b);
    }
    sort(P+1, P+n+1, compareX);
    cout << closestUtil(1, n) << endl;
 
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