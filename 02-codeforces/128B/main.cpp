#include <iostream>
#define in cin
#define out cout

#include <vector>

#include <numeric>
#include <algorithm>

#include <utility>
#define x first
#define y second

#include <queue>

#pragma GCC optimize("O3")

using namespace std;

typedef pair <int, int> pii;
const int nmax = 1e5, max32_t = (1 << 30);
int kk, radix[nmax + 2]; string ss;

void getsuffixarray(string &ss, vector <int> &ranksuff){

    /// i have this indexed from 1 ///
    ss.push_back('$'); int sz = ss.size(); 

    vector <int> suffpos(sz); ranksuff.resize(sz, 0);
    iota(suffpos.begin(), suffpos.end(), 0);

    sort(suffpos.begin(), suffpos.end(), [&ss](int a0, int a1){
        return ss[a0] < ss[a1];
    });

    for(int i = 0, rnk = 0; i < sz; i++){
        rnk += (i == 0 || ss[suffpos[i]] != ss[suffpos[i - 1]]);
        ranksuff[suffpos[i]] = rnk;
    }

    /// auxiliary vectors ///
    vector <int> copyrank(sz), copypos(sz);

    /// log iterations of radix sort for pow of 2 lengths 
    for(int p = 0; (1 << p) < sz; p++){ 
        for(int i = 0; i < sz; i++){
            copypos[i] = suffpos[i] - (1 << p);
            if(copypos[i] < 0) copypos[i] += sz;
        }

        /// do radix sort now ///
        for(int vall = 1; vall <= sz; vall++){
            radix[vall] = 0;
        }

        for(int i = 0; i < sz; i++){
            radix[ranksuff[copypos[i]]]++;
        }

        for(int vall = 1; vall <= sz; vall++){
            radix[vall] += radix[vall - 1];
        }

        /// radix to sort pairs {suffpos[a], suffpos[(a + (1 << p)) % n]}
        for(int i = sz - 1; i >= 0; i--){
            int _rnk = ranksuff[copypos[i]];
            suffpos[--radix[_rnk]] = copypos[i];
        }

        pii _lst = make_pair(-max32_t, -max32_t);
        for(int i = 0, rnk = 0; i < sz; i++){
            pii _now = make_pair(ranksuff[suffpos[i]], ranksuff[(suffpos[i] + (1 << p)) % sz]);
            rnk += (_lst != _now); _lst = _now; copyrank[suffpos[i]] = rnk;
        }

        swap(ranksuff, copyrank);
    }

    ss.pop_back(); ranksuff.pop_back();

    /// pop back (aka rank 1) ///
    for(int i = 0; i < sz - 1; i++){
        ranksuff[i]--; 
    }

    return;
}

const int lgmax = 17;
struct lcp_sparse_with_suffixarray{
    int rmq[lgmax][nmax + 2], lg2[nmax + 2], lcpadj[nmax + 2];

    vector <int> ranksuff, whererank;

    void build(string &ss){
        /// build lcp with kasai's algorithm ///
        int sz = ss.size(); whererank.resize(sz + 2, 0);

        getsuffixarray(ss, ranksuff);
        for(int i = 0; i < sz; i++){
            whererank[ranksuff[i]] = i;
        }

        for(int i = 0, _lcpbound = 0; i < sz; i++){
            if(ranksuff[i] == sz){
                _lcpbound = 0; continue; 
            }

            int j = whererank[ranksuff[i] + 1];
            for(; i + _lcpbound < sz && j + _lcpbound < sz && ss[i + _lcpbound] == ss[j + _lcpbound]; _lcpbound++);

            lcpadj[ranksuff[i]] = _lcpbound;
            _lcpbound = max(0, _lcpbound - 1);
        }

        lg2[0] = -1;
        for(int i = 1; i <= sz; i++){
            lg2[i] = lg2[i >> 1] + 1;
            rmq[0][i] = lcpadj[i];
        }

        for(int p = 1; (1 << p) <= sz; p++){
            for(int i = 1; i + (1 << p) - 1 <= sz; i++){
                rmq[p][i] = min(rmq[p - 1][i], rmq[p - 1][i + (1 << (p - 1))]);
            }
        }
    }

    int getlcp(int xx, int yy){
        if(xx == yy){ return +max32_t; }
        if(ranksuff[xx] > ranksuff[yy]){ swap(xx, yy); }

        int e = lg2[ranksuff[yy] - ranksuff[xx]];
        return min(rmq[e][ranksuff[xx]], rmq[e][ranksuff[yy] - (1 << e)]);
    }
} lcpsparse;

auto cmp = [](const pii &a0, const pii &a1){ 
    int lcp = lcpsparse.getlcp(a0.x, a1.x);
    if(lcp >= a0.y || lcp >= a1.y){
        return a0.y > a1.y;
    }
    return ss[a0.x + lcp] > ss[a1.x + lcp]; 
};

priority_queue <pii, vector <pii>, decltype(cmp)> pq(cmp);

int main(){

    in.tie(NULL); out.tie(NULL);
    ios_base::sync_with_stdio(false);

    in>>ss>>kk; 
    lcpsparse.build(ss);

    if(kk > 1ll * ss.size() * (ss.size() + 1) / 2){
        out<<"No such line.\n"; return 0;
    }

    int n = ss.size();
    for(int i = 0; i < n; i++){
        pq.push(make_pair(i, 1));
    }

    for(; !pq.empty(); ){
        auto [xx, length] = pq.top(); pq.pop(); kk--;

        if(!kk){ 
            out<<ss.substr(xx, length)<<"\n"; 
            return 0;
        }

        if(xx + length < n){
            pq.push(make_pair(xx, length + 1));
        }
    }

    return 0;
}