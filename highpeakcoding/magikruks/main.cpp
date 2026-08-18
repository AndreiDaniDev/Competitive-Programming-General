#include <fstream>

#include <utility>
#define x first
#define y second

#include <algorithm>

#include <cassert>

using namespace std;

ifstream in("magikruks.in");
ofstream out("magikruks.out");

typedef pair <int, int> pii;
const int nmax = 250000, valmax = 2 * nmax, mod = 1e9 + 7, lgmax = 19;
int n, nrq, topp, typee; int64_t xx; pair <pii, int> norm[valmax + 2]; 

int whatcandy[valmax + 2];

int exp(int a, int b){
    if(b <= 0){ return 1; }
    int exp2 = exp(a, b >> 1);
    exp2 = 1ll * exp2 * exp2 % mod;
    return ((b & 1) ? 1ll * exp2 * a % mod : exp2);
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
    }
    return;
}

struct candy{
    int xx, yy, invxx, invyy, normraport, normraportinv;
    
    void init(){
        invxx = exp(xx, mod - 2); topp++; norm[topp] = make_pair(make_pair(yy, xx), topp);
        invyy = exp(yy, mod - 2); topp++; norm[topp] = make_pair(make_pair(xx, yy), topp);
        return;
    }
} a[nmax + 2];

void getnormalized(){
    
    sort(norm + 1, norm + 1 + topp, [](pair <pii, int> r1, pair <pii, int> r2){
        return 1ll * r1.x.x * r2.x.y > 1ll * r2.x.x * r1.x.y;
    });

    for(int i = 1; i <= topp; i++){
        if(norm[i].y & 1){
            a[(norm[i].y + 1) >> 1].normraport = i;
        }else{ a[norm[i].y >> 1].normraportinv = i; }
    }

    return;
}

/// fenwicktree ///
inline int f(int xx){ return (xx & (-xx)); }
struct fenwicktree{
    int64_t treeweight[valmax + 2], totalweight;
    int treecostt[valmax + 2], totalsatisfaction;

    void update(int node, int valuee, int costt){
        for(int i = node; i <= valmax; i += f(i)){
            treeweight[i] += valuee;
            selfaddmod(treecostt[i], costt);
        }; 
        
        totalweight += valuee; 
        selfaddmod(totalsatisfaction, costt); 
        
        return;
    }

    int64_t queryweight(int node){
        int64_t summ = 0;
        for(int i = node; i >= 1; i -= f(i)){
            summ += treeweight[i];
        }
        return summ;
    }

    int querysatisfaction(int node){
        int summ = 0;
        for(int i = node; i >= 1; i -= f(i)){
            selfaddmod(summ, treecostt[i]);
        }
        return summ;
    }

    int getkthsuffix(int64_t kth){

        int pos = 0;
        for(int bit = lgmax; bit >= 0; bit--){
            if((pos | (1 << bit)) <= valmax && treeweight[pos | (1 << bit)] <= kth){
                pos |= (1 << bit), kth -= treeweight[pos];
            }
        }

        return pos + 1;
    }
} aib;    

void flip(int idx){
    whatcandy[a[idx].normraport] = 0;
    aib.update(a[idx].normraport, -a[idx].xx, mod - a[idx].yy);
    
    swap(a[idx].xx, a[idx].yy);
    swap(a[idx].invxx, a[idx].invyy);
    swap(a[idx].normraportinv, a[idx].normraport);
    
    whatcandy[a[idx].normraport] = idx;
    aib.update(a[idx].normraport, +a[idx].xx, a[idx].yy);
    return;
}

int solvequeryaib(int64_t xx){
    if(aib.totalweight <= xx){
        return aib.totalsatisfaction;
    }

    int idxwhereover = aib.getkthsuffix(xx);

    int maxcostt = aib.querysatisfaction(idxwhereover - 1);
    xx -= aib.queryweight(idxwhereover - 1); 

    candy &obj = a[whatcandy[idxwhereover]];
    selfaddmod(maxcostt, 1ll * obj.invxx * obj.yy % mod * (xx % mod) % mod);  

    return maxcostt;
}

int32_t main(){

    in>>n>>nrq;
    for(int i = 1; i <= n; i++){
        in>>a[i].xx>>a[i].yy;
        a[i].init();
    }

    getnormalized();

    /// build my aib :) ///
    for(int i = 1; i <= n; i++){
        aib.update(a[i].normraport, a[i].xx, a[i].yy);
        whatcandy[a[i].normraport] = i;
    }

    for(; nrq > 0; nrq--){
        in>>typee>>xx;

        if(typee == 1){
            flip(xx);
        }else if(typee == 2){
            out<<solvequeryaib(xx)<<"\n";
        }
    }

    return 0;
}