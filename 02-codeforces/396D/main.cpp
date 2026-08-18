#include <iostream>
#define in cin
#define out cout

#include <algorithm>
#pragma GCC optimize("O3")

using namespace std;

const int nmax = 1e6, mod = 1e9 + 7, inv2 = (mod + 1) >> 1;
int n, fact[nmax + 2], a[nmax + 2], sumofallinv[nmax + 2];

int cnk2(int xx){
    return (1ll * xx * (xx - 1) / 2) % mod;
}

int addmod(int xx, int yy){
    xx += yy;
    if(xx >= mod){
        xx -= mod;
    }
    return xx;
}

void selfaddmod(int &xx, int yy){
    xx += yy;
    if(xx >= mod){
        xx -= mod;
    };
    return;
}

struct segmenttree{
    struct segnode{
        int summ[2], smaller00, smaller01;

        segnode() : summ{0, 0}, smaller00(0), smaller01(0) {};

        /// i can pass this with const segnode &node because of the order i do the operations
        /// meaning i first change the contributions then the sums and this doesn't affect
        /// node.combine(self, smth) -> otherwise we get a big ahh WA
        void combine(const segnode &aa, const segnode &bb){
            smaller00 = addmod(aa.smaller00, bb.smaller00);
            smaller00 = addmod(smaller00, 1ll * aa.summ[0] * bb.summ[0] % mod);

            smaller01 = addmod(aa.smaller01, bb.smaller01);
            smaller01 = addmod(smaller01, 1ll * aa.summ[0] * bb.summ[1] % mod);

            summ[0] = aa.summ[0] + bb.summ[0];
            summ[1] = aa.summ[1] + bb.summ[1];

            return;
        }
    } tree[4 * nmax + 2];

    void build(int node, int st, int dr){
        if(st == dr){
            tree[node].summ[0] = 1;
            tree[node].summ[1] = 0;
        }else{
            int mij = (st + dr) >> 1;
            build((node << 1), st, mij);
            build((node << 1) | 1, mij + 1, dr);
            tree[node].combine(tree[(node << 1)], tree[(node << 1) | 1]);
        }; return;
    }

    void update(int node, int st, int dr, int idx){
        if(st == dr){
            tree[node].summ[0] = 0;
            tree[node].summ[1] = 1;
        }else{
            int mij = (st + dr) >> 1;
            if(idx <= mij) update((node << 1), st, mij, idx);
            if(mij < idx) update((node << 1) | 1, mij + 1, dr, idx);
            tree[node].combine(tree[(node << 1)], tree[(node << 1) | 1]);
        }; return;
    }

    segnode query(int node, int st, int dr, int leftt, int rightt){
        if(leftt <= st && dr <= rightt){
            return tree[node];
        }else{
            int mij = (st + dr) >> 1; segnode qry = segnode();
            if(leftt <= mij) qry.combine(qry, query((node << 1), st, mij, leftt, rightt));
            if(mij < rightt) qry.combine(qry, query((node << 1) | 1, mij + 1, dr, leftt, rightt));
            return qry;
        }; return segnode();
    }
} segtree;

int solve(){
    segtree.build(1, 1, n);

    int sumofinv = 0, prefinv = 0;

    for(int i = 1; i <= n; i++){
        int splitways = segtree.tree[1].smaller01;

        /// this was added in the prefix
        segtree.update(1, 1, n, a[i]);

        /// put smaller element from suffix on this position and count :) ///
        segmenttree::segnode qryprefix = segtree.query(1, 1, n, 1, a[i]);

        int smallerforpos = a[i] - qryprefix.summ[1];
        selfaddmod(sumofinv, 1ll * smallerforpos * sumofallinv[n - i] % mod);

        /// update the number of inversions with the fixed prefix - overcount from this fuckass ///
        selfaddmod(sumofinv, 1ll * prefinv * smallerforpos % mod * fact[n - i] % mod);
        selfaddmod(prefinv, (i - qryprefix.summ[1]));

        /// add contribution for any element smaller than a[i] | all possible suffix with remaining
        selfaddmod(sumofinv, 1ll * fact[n - i] * qryprefix.smaller00 % mod);

        /// add contribution for fixed prefix | any element smaller than a[i] | all suffix 
        selfaddmod(sumofinv, 1ll * smallerforpos * splitways % mod * fact[n - i] % mod);
    }

    selfaddmod(sumofinv, prefinv);

    return sumofinv;
}

int32_t main(){

    in.tie(NULL); out.tie(NULL); 
    ios_base::sync_with_stdio(false);

    in>>n; 
    for(int i = 1; i <= n; i++){
        in>>a[i]; 
    }

    fact[0] = 1;
    for(int i = 1; i <= n; i++){
        fact[i] = 1ll * fact[i - 1] * i % mod;
        sumofallinv[i] = 1ll * fact[i] * inv2 % mod * cnk2(i) % mod;
        // out<<i<<" -> "<<fact[i]<<" "<<sumofallinv[i]<<"\n";
    }; 

    out<<solve()<<"\n";

    return 0;
}