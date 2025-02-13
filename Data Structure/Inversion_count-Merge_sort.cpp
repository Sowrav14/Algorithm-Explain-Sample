/**
 * @file 12.00 Inversion_count-Merge_sort.cpp
 * @author Sowrav Nath
 * @brief 
 * @version 0.1
 * @date 2024-01-22
 * @copyright Copyright (c) 2024
 * @problem: count of inversion
 * @approach: Merge sort tree
 * @explantion:
 *                          a[] =  {8, 4, 2, 1}
 *                              {8,4}         {2,1}
 *                             {8}  {4}      {2}   {1}
 *                              {4,8}         {1,2}         inv = 1 + 1
 *                                  {1, 2, 4, 8}            inv = 2 + 2
 *                                                          ans = 6
 */


#include<bits/stdc++.h>
using namespace std;
#define int long long int
#define Fast_IO() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

int inv;

// merge function
void merge(vector<int>&arr, int n, int l, int m, int r){
    
    // initializing array for left and right partint nl = m - l + 1;
    int nl = m - l + 1, nr = r - m;
    vector<int>larr, rarr;
    for(int i=l;i<=m;i++){
        larr.push_back(arr[i]);
    }
    for(int i=m+1;i<=r;i++){
        rarr.push_back(arr[i]);
    }

    // merging left and right part
    int i = 0, j = 0, k = l;
    while(i<nl and j<nr){
        if(larr[i] < rarr[j]){
            arr[k] = larr[i];
            i++;
        } else{
            arr[k] = rarr[j];
            j++;
            inv += nl - i;          // when right element is encountered remaining in left are counted as inversion.
        }
        k++;
    }
    // adding remaining element.
    while(i < nl){
        arr[k] = larr[i];
        i++, k++;
    }
    while(j < nr){
        arr[k] = rarr[j];
        j++, k++;
    }
}

// mergesort function.
void mergesort(vector<int>&arr, int n, int l, int r){
    if(l >= r) return;

    int m = (l + r) / 2;
    mergesort(arr, n, l, m);
    mergesort(arr, n, m+1, r);
    merge(arr, n, l, m, r);
    return;
}


void solve(){

    int n; cin >> n;
    vector<int>arr(n);
    for(int i=0;i<n;i++){
        cin >> arr[i];
    }
    inv = 0;                                                // inversion counter set to zero.
    mergesort(arr, n, 0, n-1);
    // for(auto i : arr) cout << i << " "; cout << endl;    // sorted array
    cout << inv << endl;

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