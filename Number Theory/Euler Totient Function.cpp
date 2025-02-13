/**
 * @file Euler Totient Function.cpp
 * @author Sowrav Nath (Sowravnath05102002@gmail.com)
 * @version 0.1
 * @date 2024-09-11
 * @copyright Copyright (c) 2024
 * @topic: Euler Totient Function | Phi function...
 * @sources: https://cp-algorithms.com/algebra/phi-function.html
 * @problems: CSES_Exponentiation_II : https://cses.fi/problemset/task/1712
 *            CSES_Counting Coprime Pairs : https://cses.fi/problemset/task/2417
 */

/*Intro:
    Euler's totient function, also known as phi-function  
    phi(n) , counts the number of integers between 1 and  
    n  inclusive, which are coprime to  
    n. Two numbers are coprime if their greatest common divisor equals 1  
    ( 1  is considered to be coprime to any number).

    for prime number p: phi(p) = p - 1
                        phi(p^k) = p^k - p^(k-1)
    if a and b are coprime then phi(a*b) = phi(a) * phi(b)
    In general if a and b are not co-prime phi(a*b) = phi(a) * phi(b) * d/phi(d) where d = gcd(a, b)
*/

/*Derivation of phi function:
    if n = p1^e1 * p2^e2 * p3^e3....
    then phi(n) = phi(p1^e1) * phi(p2*e2) * phi(p3*e3)...
                = phi(p1^e1 - p1^(e1-1)) * phi(p2^e2 - p2^(e2-1))...
                = n * (1 - 1/p1) * (1 - 1/p2) * (1 - 1/p3)...
    Complexity O(sqrt(n)) 
    can optimize it with sieve...
 */

/*Divisor sum property:
    for all divisors of n sum(phi(n)) = n.
    ex. phi(1) + phi(2) + phi(5) + phi(10) = 10;
*/

/*ETF in modular arithmetic. if x and m are not co-prime...
    1. Generalization:
        (x^n) %m = x^[phi(m) + {n%phi(m)}] %m
    2. a^(b^c)
        - calculate x = (b^c) % phi(m)
        - calculate y = (a^x) % m
        - a^(b^c) = y
*/



#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 1e5 + 10;
const int M = 1e9 + 7;
const int inf = 1e12;

/*  O(sqrt(n)) */
int phi(int n) {
    int result = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

/*  O(nloglogn) */
void phi_1_to_n(int n) {
    vector<int> phi(n + 1);
    for (int i = 0; i <= n; i++)
        phi[i] = i;

    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
    }
}

void solve(){

    // do whatever with etf...

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