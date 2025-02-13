/*
 * @file Line Sweep Algorithm.cpp
 * @author Sowrav Nath
 * @version 0.1
 * @date 2024-06-16
 * @copyr Copyr (c) 2024
 * @problem: Find intersection between lines.
 * @approach: Sweep Line Algorithms.
 * @explanation: https://www.geeksforgeeks.org/given-a-set-of-line-segments-find-if-any-two-segments-intersect/
 */

/**
 * see also- 
 * problem : https://cses.fi/problemset/task/1740/
 * solution : https://github.com/Sowrav14/CP-Source-Codes/blob/main/CSES/Intersection_Points.cpp
 */

#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

struct Point{ int x, y; };
struct Segment{ Point l, r; };

int n;
vector<Segment>lines;


/*
    Event is basically the points.
        - coordinate of the pooint
        - is it left of segment (left or right trace)
        - initial index of the segment.
 */
struct event {
	int x, y;
	bool isLeft;
	int index;
    event(int x, int y, bool l, int i) : x(x), y(y), isLeft(l), index(i) {}
	// This is for maintaining the order in set.
	bool operator<(const event& e) const {
			if(y == e.y) return x < e.x;
			return y < e.y;
	}
};

struct Event {
	int x, y;
	bool isLeft;
	int index;
	Event(int x, int y, bool l, int i) : x(x), y(y), isLeft(l), index(i) {}

	// This is for sorting
	bool operator<(const Event& e) const {
        if(x != e.x) return x < e.x;
        else if(y != e.y) return y < e.y;
        else return index < e.index;
	}
};


bool onSegment(Point p, Point q, Point r){
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
		q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
	return true;

	return false;
}

int orientation(Point p, Point q, Point r){
	int val = (q.y - p.y) * (r.x - q.x) -
			(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0;

	return (val > 0)? 1: 2;
}


bool doIntersect(Segment s1, Segment s2){
	Point p1 = s1.l, q1 = s1.r, p2 = s2.l, q2 = s2.r;
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


// Find predecessor of iterator in s.
set<event>::iterator pred(set<event> &s, set<event>::iterator it) {
	return it == s.begin() ? s.end() : --it;
}

// Find successor of iterator in s.
set<event>::iterator succ(set<event> &s, set<event>::iterator it) {
	return ++it;
}




int findIntersect(){
	unordered_map<string,int> mp;  // to note the pair for which intersection is checked already
	vector<Event> e; // Pushing all points to a vector of events
	for (int i = 0; i < n; ++i) {
		e.push_back(Event(lines[i].l.x, lines[i].l.y, true, i));
		e.push_back(Event(lines[i].r.x, lines[i].r.y, false, i));
	}

	// Sorting all events according to x coordinate.
	sort(e.begin(), e.end());

	set<event> s; // For storing active segments.
	int ans = 0;
	for (int i=0;i<2*n;i++){ // Traversing through sorted points
		Event curr = e[i];
		int index = curr.index;

		// If current point is l of its segment
		if (curr.isLeft){
			// Get above and below points
			auto next = s.lower_bound(event(curr.x, curr.y, curr.isLeft, curr.index));
			auto prev = pred(s, next);
			// Check if current point intersects with any of its adjacent
			bool flag = false;
			if (next != s.end() && doIntersect(lines[next->index], lines[index])){
				string s = to_string(next->index+1) + " " + to_string(index+1);
				if(mp.count(s) == 0){ mp[s]++; ans++; } //if not already checked we can increase count in map
			}
			if (prev != s.end() && doIntersect(lines[prev->index], lines[index])){
					string s = to_string(prev->index+1) + " " + to_string(index+1);
				if(mp.count(s) == 0){ mp[s]++; ans++; } //if not already checked we can increase count in map
			}
			// if same line segment is there then decrease answer as it got increased twice
			if(prev != s.end() && next != s.end() && next->index == prev->index) ans--;

			// Insert current point (or event)
			s.insert(event(curr.x, curr.y, curr.isLeft, curr.index));
		} else { // If current point is r of its segment
			// Find the iterator
			auto it = s.find(event(lines[index].l.x, lines[index].l.y, true, index));
			// Find above and below points
			auto next = succ(s, it);
			auto prev = pred(s, it);

			// If above and below point intersect
			if (next != s.end() && prev != s.end()){ 
                string s = to_string(next->index+1) + " " + to_string(prev->index+1);
				string s1 = to_string(prev->index+1) + " " + to_string(next->index+1);
				if (mp.count(s) == 0 && mp.count(s1) == 0 && doIntersect(lines[prev->index], lines[next->index])){
					ans++;
					mp[s]++;
                }
			}
			// Remove current segment
			s.erase(it);
		}
	}
	//print pair of lines having intersection
	/* for(auto &pr:mp){
		cout<<"Line: "<<pr.first<<"\n";
	} */
	return ans;
}

void solve(){

    cin >> n;
    for(int i=0;i<n;i++){
        Point p, q; cin >> p.x >> p.y >> q.x >> q.y;
        Segment s; s.l = p, s.r = q;
        lines.push_back(s);
    }

    cout << findIntersect() << endl;

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