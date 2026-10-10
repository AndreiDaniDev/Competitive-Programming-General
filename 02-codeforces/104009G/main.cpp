#include <iostream>
#include <iomanip>

#define in cin
#define out cout

#include <vector>

using namespace std;

const int nmax = 1e6;
int n, nrq, john, xx, yy;

double prob[nmax + 2];
int father[nmax + 2];
vector <int> edges[nmax + 2];

int main(){

    in.tie(NULL); out.tie(NULL);
    ios_base::sync_with_stdio(false);

    in>>n>>john;
    for(int i = 1, _; i <= n; i++){
        in>>xx>>_;
        for(; _ > 0; _--){
            in>>yy; father[yy] = xx; 
            edges[xx].push_back(yy);
        }
    }

    for(int i = 1; i <= n; i++){
        prob[i] = 0.5;
    }

    for(auto nxt : edges[father[john]]){
        /// correct is 3/4 ///
        prob[nxt] = double(2.0) / double(3);
    }

    prob[john] = 1.0;

    in>>nrq;
    for(int itq = 1; itq <= nrq; itq++){
        in>>xx; 
        out<<fixed<<setprecision(10)<<prob[xx]<<"\n";
    }

    return 0;
}