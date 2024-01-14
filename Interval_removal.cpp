#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
const int M = 1e5 + 10;
const int blk = sqrt(N) + 1;   // block size and total block will be sqrt(N)

class query{

    public :
         int l,r,id,block;                  // each query belongs to a block
         query(int l, int r, int id){
            this->l = l;
            this->r = r;
            this->id = id;
            this->block = l/blk;            // block number will be l/blk
         }

         bool operator < (query cq){        // sort according to block then r
            if(block != cq.block) return block < cq.block;
            else return r < cq.r;
         }

};



int a[N],res[M], range[M];
query qu[M];
int freq[N], counter[N];

void solve(){
    int n; cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }

    int q; cin >> q;
    for(int i=1;i<=q;i++){
        int l, r; cin >> l >> r;
        qu[i] = query(l, r, i);
        range[i] = (r - l + 1);           // range will be (r - l + 1) if all same
    }

    sort(qu+1, qu+q+1);
    int prevl = 1, prevr = 0;             // keep trace of previous segment
    int prev_ans = 0;

    for(int i=1;i<=q;i++){
        int curl = qu[i].l;
        int curr = qu[i].r;
        int idx = qu[i].id;

        while(curl < prevl){
            --prevl;
            int val = a[prevl];
            int c = freq[val];
            counter[c]--;
            freq[val]++;
            counter[freq[val]]++;
            prev_ans = max(prev_ans, freq[val]);

        }
    }


}



int main(){
    int t; cin >> t;
    while(t--){
        solve();
    }
}