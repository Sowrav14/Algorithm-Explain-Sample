#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);


// Representing Points
struct point{
    int x,y;
};

// representing straight line if form of ax + by + c = 0.
struct straight_line{
    int a,b,c;
};

// return euclidean distance between two points.
double distance(point a, point b){
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// return straight line passing through two points in form of ax + by + c = 0;
straight_line eqn_of_straight_line(point a, point b){
    // (x - a.x)/(a.x - b.x) = (y - a.y)/(a.y - b.y)
    // x * (a.y - b.y) - a.x * (a.y - b.y) = y * (a.x - b.x) - a.y * (a.x - b.x)
    // (a.y - b.y) * x + (b.x - a.x) * y + a.y * (a.x - b.x) - a.x * (a.y - b.y) = 0;
    straight_line st;
    st.a = (a.y - b.y);
    st.b = (b.x - a.x);
    st.c = a.y * (a.x - b.x) - a.x * (a.y - b.y);
    int g = __gcd(st.a, __gcd(st.b, st.c));
    st.a /= g;
    st.b /= g;
    st.c /= g;

    return st;
}

// if x is known (f = 0) it will return the point with suitable y
// if y is known (f = 1) it will return the point with suitable x
point point_lies_in_straight_line(point p, bool f, straight_line s){
    if(f == 0){

    } else {

    }
}





void solve(){

    cout << __gcd(7, 0) << endl;

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