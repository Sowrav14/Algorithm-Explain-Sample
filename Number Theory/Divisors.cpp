/**
 * @file Divisors.cpp
 * @author Sowrav Nath (Sowravnath05102002@gmail.com)
 * @version 0.1
 * @date 2024-09-11
 * @copyright Copyright (c) 2024
 * @topic: Number of divisors and Sum of divisors...
 */

#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 1e5 + 10;
const int M = 1e9 + 7;
const int inf = 1e12;

/* 
    if prime factorization is p1^(e1) * p2^(e2) * p3^(e3)....
    Number of divisors is (e1 + 1) * (e2 + 1) * (e3 + 1) ...
    Sum of divisors is [{p1^(e1+1)-1}/(p1-1)] * [{p2^(e2+1)-1}/(p2-1)] *...
    Product of divisors is n^(d(n) / 2) where d(n) = number of divisors of n.
*/

int numberOfDivisors(int num) {
    int total = 1;
    for (int i = 2;i * i <= num; i++) {
        if (num % i == 0) {
            int e = 0;
            do {
                e++;
                num /= i;
            } while (num % i == 0);
            total *= e + 1;
        }
    }
    if (num > 1) {
        total *= 2;
    }
    return total;
}

int SumOfDivisors(int num) {
    int total = 1;
    for (int i = 2;i * i <= num; i++) {
        if (num % i == 0) {
            int e = 0;
            do {
                e++;
                num /= i;
            } while (num % i == 0);

            int sum = 0, pow = 1;
            do {
                sum += pow;
                pow *= i;
            } while (e-- > 0);
            total *= sum;
        }
    }
    if (num > 1) {
        total *= (1 + num);
    }
    return total;
}


void solve(){

    int x = 20;
    cout << numberOfDivisors(20) << endl;
    cout << SumOfDivisors(20) << endl;

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
