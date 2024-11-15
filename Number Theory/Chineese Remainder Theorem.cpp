#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

// Macros...
#define int                 long long int
#define pii                 pair<int,int>
#define ordered_set         tree<int, null_type, less_equal<int>,rb_tree_tag,tree_order_statistics_node_update>
#define Sowrav_Nath         ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define f(i,n)              for(int i=0;i<n;i++)
#define f1(i,n)             for(int i=1;i<=n;i++)
#define rf(i,n)             for(int i=n-1;i>=0;i--)
#define rf1(i,n)            for(int i=n;i>=1;i--)
#define endl                '\n'
#define pb                  push_back
#define oui                 cout << "YES" << endl
#define non                 cout << "NO" << endl
#define homme               cout << "Bob" << endl
#define femme               cout << "Alice" << endl
#define un_de_minus         cout << "-1" << endl
#define duck                cout << 0 << endl;
#define reponse             cout << ans << endl
#define ici                 cout << "Je suis ici" << endl

// Global Variables...

// Inline Function...
inline int bigmod(int x,int y, int mod);
inline int inverse_mod(int n,int mod)           {return bigmod(n,mod-2, mod);}
inline int ad(int x,int y, int mod)             {int ret=(x%mod+y%mod)%mod;   if(ret<0)   {ret+=mod,ret=ret%mod;} return ret;}
inline int sub(int x,int y, int mod)            {int ret=((x%mod)-(y%mod)+mod)%mod;    if(ret<0)    {ret+=mod,ret=ret%mod;} return ret;}
inline int gun(int x,int y, int mod)            {int ret=((x%mod)*(y%mod))%mod;   if(ret<0)   {ret+=mod,ret=ret%mod;} return ret;}
inline int bigmod(int x,int y, int mod)         {int ret=1; while(y>0)  {if(y&1)    {ret=(ret*x)%mod;}    y>>=1;x=(x*x)%mod;}   return ret;}
inline int egcd(int a,int b,int &x,int &y)      {if(a==0){ x=0; y=1; return b;} int x1,y1; int d=egcd(b%a,a,x1,y1); x=y1-(b/a)*x1; y=x1; return d;}
inline int inverse(int a, int mod)              { int x, y; int g = egcd(a, mod, x, y); return (g != 1) ? -1 : (x % mod + mod) % mod; }


// Ordered Set Tree
// S.order_of_key (k) : Number of items strictly smaller than k .
// S.find_by_order(k) : K-th element in a set (counting from zero).



/* Calculate ( a*b ) % c */
int mulmod(int a, int b, int c) {
    int x = 0 , y = a % c ;
    while(b>0) {
        if(b%2) x = (x + y) % c ;
        y = (y * 2) % c;
        b /= 2;
    }
    return x % c ;
}

/* Calculate ( a^b ) % c */
int modulo(int a, int b, int c) {
    int x = 1 , y = a % c;
    while( b > 0 ) {
        if(b%2) x = mulmod(x, y, c) ;
        y = mulmod(y, y, c);
        b /= 2;
    }
    return x % c;
}

int modulus_Inverse(int A, int MOD) {
    return modulo(A,MOD-2, MOD);
}

// ax + by = __gcd(a, b)
// returns __gcd(a, b)
int extended_euclid(int a, int b, int &x, int &y) {
    int xx = y = 0;
    int yy = x = 1;
    while (b) {
        int q = a / b;
        int t = b; b = a % b; a = t;
        t = xx; xx = x - q * xx; x = t;
        t = yy; yy = y - q * yy; y = t;
    }
    return a;
}

// finds x such that x % m1 = a1, x % m2 = a2. m1 and m2 may not be coprime
// here, x is unique modulo m = lcm(m1, m2). returns (x, m). on failure, m = -1.
pair<int, int> CRT(int a1, int m1, int a2, int m2) {
    int p, q;
    int g = extended_euclid(m1, m2, p, q);
    if (a1 % g != a2 % g) return make_pair(0, -1);
    int m = m1 / g * m2;
    p = (p % m + m) % m;
    q = (q % m + m) % m;
    return make_pair((p * a2 % m * (m1 / g) % m + q * a1 % m * (m2 / g) % m) %  m, m);
}

struct Congruence {
    int a, m;
    Congruence(int a, int m) : a(a), m(m) {}
};

int chinese_remainder_theorem(vector<Congruence> const& congruences) {
    int M = 1;
    for (auto const& congruence : congruences) {
        M *= congruence.m;
    }

    int solution = 0;
    for (auto const& congruence : congruences) {
        int a_i = congruence.a;
        int M_i = M / congruence.m;
        int N_i = modulus_Inverse(M_i, congruence.m);
        int S = mulmod(M_i, N_i, M);
        S = mulmod(S, a_i, M);
        solution = ad(solution, S, M);;
    }
    return solution;
}


void solve(){

    int n; cin >> n;
    vector<Congruence> cgs;
    
    for(int i=0;i<n;i++){
        int m, a; cin >> m >> a;
        cgs.push_back(Congruence(a, m));
    }
    
    int ans = chinese_remainder_theorem(cgs);
    cout << ans << endl;

}


signed main(){
    Sowrav_Nath
    int test_cases = 1;
    cin >> test_cases;
    for(int test_case=1;test_case<=test_cases;test_case++){
        cout << "Case " << test_case << ": ";
        // memset(dp,0,n*sizeof(int));
        solve();
    }
}