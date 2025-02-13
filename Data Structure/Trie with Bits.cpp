/**
 * @file Trie.cpp
 * @author Sowrav Nath (Sowravnath05102002@gmail.com)
 * @version 0.1
 * @date 2024-10-14
 * @copyright Copyright (c) 2024
 * @problem: https://codeforces.com/problemset/problem/665/E
 * @approach: Trie for bits
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 3e5 + 10;
const int M = 1e9 + 7;
const int inf = 1e12;

struct Trie {
  	static const int B = 31;
	
	// Node structure of Trie...
  	struct Node {
    	Node* links[2];	// two possibility to go next.
    	int sz;			// how many prefixes
		Node() {
			links[0] = links[1] = NULL;
			sz = 0;
		}
		bool containsKey(int ind) {
        	return (links[ind] != NULL); 
		}
		Node* get(int ind) {
			return links[ind]; 
		}
		void put(int ind, Node* Node) {
			links[ind] = Node; 
		}
  	} *root;
	Trie() {
		root = new Node();
	}

	// insert value in trie.
	void insert(int val) {
		Node* cur = root;
		cur->sz++;
		for (int i = B - 1; i >= 0; i--) {
			int b = val >> i & 1;
			if(!cur->containsKey(b)) {
                cur->put(b, new Node()); 
            }
			cur = cur->links[b];
			cur->sz++;
		}
	}

	// delete node from trie...
	void del(Node* cur) {
    	for (int i = 0; i < 2; i++) if (cur -> links[i]) del(cur -> links[i]);
    	delete(cur);
  	}

	// number of values in trie (formally given in array)
	// such that val ^ x < k
  	int query(int x, int k) {
    	Node* cur = root;
    	int ans = 0;
    	for (int i = B - 1; i >= 0; i--) {
      		if (cur == NULL) break;
      		int b1 = x >> i & 1, b2 = k >> i & 1;
      		if (b2 == 1) {
       			if (cur->containsKey(b1)) ans += cur->links[b1]->sz;
        		cur = cur->links[!b1];
      		} else {
				cur = cur->links[b1];
			}
    	}
    	return ans;
  	}

	// get ans such that ans ^ x is maximized where x is in trie(formally given in array).
	// complexity O(32)
	int get_max(int x) { 
		Node* cur = root;
		int ans = 0;
		for (int i = B - 1; i >= 0; i--) {
			int k = x >> i & 1;
			if (cur->containsKey(!k)){
				cur = cur->links[!k];
				ans <<= 1;
				ans++;
			} else {
				cur = cur->links[k];
				ans <<= 1;
			}
		}
		return ans;
	}

	// get ans such that ans ^ x is minimized where x is in trie(formally given in array).
	// complexity O(32)
  	int get_min(int x) {
    	Node* cur = root;
    	int ans = 0;
    	for (int i = B - 1; i >= 0; i--) {
      		int k = x >> i & 1;
			if (cur->containsKey(k)){
				cur = cur->links[k];
				ans <<= 1;
			} else { 
				cur = cur->links[!k];
				ans <<= 1;
				ans++;
			}
    	}
    	return ans;
  	}

} trie;

/*

	problem is count of total subarrays where xor of it is at least k.
	s[i] = a[1] ^ [a2] ^ .... a[i]
	now for every j belongs to (1, n)
	if(s[i] ^ s[j] >= k) ans++;	where i belongs to (1..i-1)
	because s[i] ^ s[j] = s[i+1] ^ s[i+2] ^ ... ^ s[j]
	and this iteration of j generate all possible subarray.
	still complexity is O(n*n).

	lets optimize with trie.
	with trie we can get number of values in trie such that val ^ x(in trie) < k
	so for every s[j] ans -= query(s[j], k) // substract all i's(i < j) where s[j] ^ s[i] < k

*/


void solve(){

    int n,k; cin >> n >> k;
	int ans = (n * (n + 1)) / 2;
	int cur = 0;
	trie.insert(0);
	for(int i=0;i<n;i++){
		int x; cin >> x;
		cur ^= x;
		ans -= trie.query(cur, k);
		trie.insert(cur);
	}
	cout << ans << endl;

}


signed main(){
    Fast_IO()
    int t = 1;
    // cin >> t;
    for(int i=1;i<=t;i++){
        // cout << "Case #" << i << ": ";
        solve();
    }
}