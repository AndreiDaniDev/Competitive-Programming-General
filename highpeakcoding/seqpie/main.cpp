#include <fstream>

#include <vector>

using namespace std;

ifstream in("seqpie.in");
ofstream out("seqpie.out");

const int nmax = 1e5, valmax = 500;
int n, nrq, typee, xx, yy, a[nmax + 2];

int freqprime[valmax + 2], maxfactor[valmax + 2];
vector <int> primes;

int solve(int xx, int yy){
    if(yy - xx + 1 > primes.size()){ return 0; } /// no way

    for(auto &prime : primes){
        freqprime[prime] = 0;
    }

    for(int i = xx; i <= yy; i++){
        for(int vall = a[i], lastt = -1; vall > 1; ){
            if(lastt != maxfactor[vall]){
                freqprime[maxfactor[vall]]++;
                if(freqprime[maxfactor[vall]] > 1){
                    return 0;
                }
                lastt = maxfactor[vall];
            }

            vall /= maxfactor[vall];
        }
    }

    return 1;
}

int main(){

    for(int i = 2; i <= valmax; i++){
        if(maxfactor[i]){ continue; }
        
        for(int j = i; j <= valmax; j += i){
            maxfactor[j] = i;
        }
        primes.push_back(i);
    }

    in>>n>>nrq;
    for(int i = 1; i <= n; i++){
        in>>a[i];
    }

    for(int itq = 1; itq <= nrq; itq++){
        in>>typee>>xx>>yy;

        if(typee == 1){
            a[xx] = yy;
        }else{
            out<<solve(xx, yy)<<"\n";
        }
    }

    return 0;
}