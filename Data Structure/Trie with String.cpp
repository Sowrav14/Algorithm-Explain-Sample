/**
 * @file Trie with String.cpp
 * @author Sowrav Nath (Sowravnath05102002@gmail.com)
 * @version 0.1
 * @date 2024-11-08
 * @copyright Copyright (c) 2024
 * @tags: Trie string
 * @resources: https://www.youtube.com/playlist?list=PLgUwDviBIf0pcIDCZnxhv0LkHf5KzG9zp
 *             https://www.geeksforgeeks.org/introduction-to-trie-data-structure-and-algorithm-tutorials/
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int N = 1e5 + 10;
const int M = 1e9 + 7;
const int inf = 1e12;

// structure of trie node...
struct Node {
    Node *links[26]; 
    int cntEndWith = 0;
    int cntPrefix = 0; 
    
    bool containsKey(char ch) {
        return (links[ch - 'a'] != NULL); 
    }
    Node* get(char ch) {
        return links[ch-'a']; 
    }
    void put(char ch, Node* node) {
        links[ch-'a'] = node; 
    }
    void increaseEnd() {
        cntEndWith++;  
    }
    void increasePrefix() {
        cntPrefix++; 
    }
    void deleteEnd() {
        cntEndWith--; 
    }
    void reducePrefix() {
        cntPrefix--; 
    }
    int getEnd() {
        return cntEndWith; 
    }
    int getPrefix() {
        return cntPrefix; 
    }
};


class Trie {
private: Node *root; 
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new Node(); 
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        Node *node = root;
        for(int i = 0;i<word.length();i++) {
            if(!node->containsKey(word[i])) {
                node->put(word[i], new Node()); 
            }
            node = node->get(word[i]); 
            node->increasePrefix(); 
        }
        node->increaseEnd(); 
    }
    
    int countWordsEqualTo(string &word){
        Node* node = root;
        for(int i = 0;i<word.length();i++) {
            if(node->containsKey(word[i])) {
                node = node->get(word[i]);
            } else {
                return 0; 
            }  
        }
        return node->getEnd(); 
    }

    int countWordsStartingWith(string &word){
        Node* node = root;
        for(int i = 0;i<word.length();i++) {
            if(node->containsKey(word[i])) {
                node = node->get(word[i]);
            } else {
                return 0; 
            }  
        }
        return node->getPrefix(); 
    }

    void erase(string &word){
        Node* node = root;
        for(int i = 0;i<word.length();i++) {
            if(node->containsKey(word[i])) {
                node = node->get(word[i]);
                node->reducePrefix(); 
            } else {
                return;
            }
        }
        node->deleteEnd(); 
    }
} trie;


void solve(){

    

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