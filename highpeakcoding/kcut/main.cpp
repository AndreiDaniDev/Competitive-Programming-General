#include <fstream>

#include <utility>
#define x first
#define y second

#include <vector>
#include <algorithm>

using namespace std;

ifstream in("kcut.in");
ofstream out("kcut.out");

typedef pair <int, int> pii;
const int nmax = 1e5;
int n, kk, xx, yy, costt;
vector <pii> edges[nmax + 2];

void selfmax(auto &xx, auto yy){ if(xx < yy) xx = yy; return; }

int ordertag[nmax + 2];

void dfsinit(int node, int parent, int &idx){

    for(auto &[nxt, _] : edges[node]){
        if(nxt == parent){ continue; }
        dfsinit(nxt, node, idx);
    }

    ordertag[++idx] = node;

    for(auto it = edges[node].begin(); it != edges[node].end(); it++){
        if(it -> first == parent){ edges[node].erase(it); return; }
    }

    return;
}

/// binary search on the answer ///
/// if the maximum diameter of a little cut tree is xx and i got this using P cuts
/// i can make the maximum diameter of a little cut tree xx + 1 with o <= P cuts 

/// dp[i] = minimum number of cuts such that this subtree has a diameter <= xx 
int dp[nmax + 2]; int64_t maxdistfromnode[nmax + 2];

int64_t stk[nmax + 2];

void processnode(int node, int64_t maxlength, int &mincostt){
    /// reinit dp ///
    maxdistfromnode[node] = 0;

    int prevsz = stk[0];

    for(auto &[nxt, distt] : edges[node]){
        mincostt += dp[nxt]; /// super simple loop

        if(distt + maxdistfromnode[nxt] > maxlength){
            mincostt++; continue; 
        }

        stk[++stk[0]] = distt + maxdistfromnode[nxt];
    }

    sort(stk + prevsz + 1, stk + stk[0] + 1);

    for(; stk[0] - prevsz >= 2; ){
        /// do i need to make a cut? is george the curious monkey's question (idek)
        
        if(stk[stk[0]] + stk[stk[0] - 1] > maxlength){
            mincostt++; stk[0]--; /// i must make a cut here 
        }else{ break; }
    }

    for(; stk[0] > prevsz; stk[0]--){
        selfmax(maxdistfromnode[node], stk[stk[0]]);
    };

    return;
}

int check(int64_t xx){
    
    int costt = 0;
    for(int i = 1; i <= n; i++){
        processnode(ordertag[i], xx, costt);
    }

    return costt;
}

int main(){

    in>>n>>kk; int64_t summ = 0;
    for(int i = 1; i <= n - 1; i++){
        in>>xx>>yy>>costt; summ += costt;
        edges[xx].push_back(make_pair(yy, costt));
        edges[yy].push_back(make_pair(xx, costt));
    }

    /// binary search on dfs is ahh because of recursion overhead * log
    int idx = 0; dfsinit(1, 0, idx); 

    /// O(n log n log valmax) ///
    int64_t st = 0, dr = summ, mij, bestt = summ;
    
    for(; st <= dr; ){
        mij = (st + dr) >> 1;
        if(check(mij) <= kk){
            dr = mij - 1, bestt = mij;
        }else{ st = mij + 1; }
    }

    out<<bestt<<"\n";

    return 0;
}