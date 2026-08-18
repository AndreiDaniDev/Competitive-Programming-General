#include <fstream>

#include <algorithm>

using namespace std;

ifstream in("3picioare.in");
ofstream out("3picioare.out");

const int nmax = 2e5, mod = 1e9 + 7;
int n, ways, fact[nmax + 2], invfact[nmax + 2];

int dpderanjamente[nmax + 2];

int addmod(int xx, int yy){
    xx += yy;
    if(xx >= mod){
        xx -= mod;
    }
    return xx;
}

void addselfmod(int &xx, int yy){
    xx += yy;
    if(xx >= mod){
        xx -= mod;
    }
    return;
}

int exp(int a, int b){
    if(b <= 0){ return 1; }
    int exp2 = exp(a, b >> 1);
    exp2 = 1ll * exp2 * exp2 % mod;
    return ((b & 1) ? 1ll * exp2 * a % mod : exp2);
}

void precomputecombi(){

    fact[0] = 1;
    for(int i = 1; i <= nmax; i++){
        fact[i] = 1ll * fact[i - 1] * i % mod;
    }

    /// modulo is prime -> phi(mod) = mod - 1
    invfact[nmax] = exp(fact[nmax], mod - 2); 
    for(int i = nmax - 1; i >= 0; i--){
        invfact[i] = 1ll * invfact[i + 1] * (i + 1) % mod;
    }

    return;
}

int cnk(int n, int kk){
    if(n < 0 || kk < 0 || n - kk < 0){ return 0; }
    return 1ll * fact[n] * invfact[kk] % mod * invfact[n - kk] % mod;
}

int computeperm(int xx){
    return 1ll * fact[2 * xx] * exp((mod + 1) >> 1, xx) % mod;
}

void computedpderanjamente(){
    // dpderanjamente[i] = #deranjamente pt o perm cu i elemente

    for(int i = 1; i <= n; i++){
        dpderanjamente[i] = 1ll * dpderanjamente[i - 1] * i % mod;
        addselfmod(dpderanjamente[i], (i & 1) ? mod - 1 : 1); 
    }

    return;
}

int function(int xx){
    int ways = 1ll * fact[2 * xx] * invfact[xx] % mod;
    return 1ll * ways * exp((mod + 1) >> 1, xx) % mod;
}

int main(){

    in>>n; /// fixez nr de elemente pare din prima conditie

    /// sa zicem ca as avea sirul 1, 1, 2, 2, 3, 3, 4, 4
    /// answer nu este cumva numarul de permutari a.i. a[i] != a[i + 1] pt i impar?

    precomputecombi();
    computedpderanjamente();

    /// count how many permutation of 2n elements with n unique ones (each has a freq of 2) 
    /// are there such that a[i] != a[i + 1] for i odd and then divide by n! and we have the answer 

    for(int fixedinvalid = 0; fixedinvalid <= n; fixedinvalid++){
        int smolways = cnk(n, fixedinvalid); /// ce perechi o sa am cu a[i] == a[i + 1]
        /// pe restul le pot permuta cum imi doreste sufletelul

        smolways = 1ll * smolways * function(n - fixedinvalid) % mod;
        addselfmod(ways, (fixedinvalid & 1) ? mod - smolways : smolways);
    }

    out<<ways<<"\n";
 
    return 0;
}