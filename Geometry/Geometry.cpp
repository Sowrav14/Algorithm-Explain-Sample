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
// (x - a.x)/(a.x - b.x) = (y - a.y)/(a.y - b.y)
// x * (a.y - b.y) - a.x * (a.y - b.y) = y * (a.x - b.x) - a.y * (a.x - b.x)
// (a.y - b.y) * x + (b.x - a.x) * y + a.y * (a.x - b.x) - a.x * (a.y - b.y) = 0;
straight_line eqn_of_straight_line(point a, point b){
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

// return x value of point (x, y) lies on straght line given y.
// return in form of x/y
// ax + by + c = 0
// ax = - c - by
// x = (-c -by) / a
pair<int,int> x_value_of_y_from_straight_line(straight_line st, int y){

    pair<int,int>ret;
    ret.first = (-st.c - st.b * y);
    ret.second = st.a;
    int g = __gcd(ret.first, ret.second);
    ret.first /= g;
    ret.second /= g;

    return ret;
}

// return y value of point (x, y) lies on straght line given x.
// return in form of x/y
// ax + by + c = 0
// by = -c - ax
// y = (-c - ax) / b
pair<int,int> y_value_of_x_from_straight_line(straight_line st, int x){

    pair<int,int>ret;
    ret.first = (-st.c - st.a * x);
    ret.second = st.b;
    int g = __gcd(ret.first, ret.second);
    ret.first /= g;
    ret.second /= g;

    return ret;
}

// both pair are fraction numbers 
// returns bigger from them.
pair<int,int> givebig(pair<int,int>a, pair<int,int>b){
    if(a.second == 0) return b;
    if(b.second == 0) return a;

    double x = (a.first * 1.0) / (a.second * 1.0);
    double y = (b.first * 1.0) / (b.second * 1.0);

    if(x > y) return a;
    else return b;
}

// return distance on basis of x as y is same
// (a/b) - (c/d)
// ((a*d - c*b) / bd)
// return in form of x/y.
pair<int,int> fraction_subtract(pair<int,int> a, pair<int,int> b){
    pair<int,int>ret;
    ret.first = (a.first * b.second - b.first * a.second);
    ret.second = (b.second * a.second);

    int g = __gcd(ret.first, ret.second);
    ret.first /= g;
    ret.second /= g;

    return ret;
    
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