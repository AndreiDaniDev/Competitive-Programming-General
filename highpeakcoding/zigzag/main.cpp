#include <fstream>

#include <vector>
#include <algorithm>

using namespace std;

ifstream in("zigzag.in");
ofstream out("zigzag.out");

const int nmax = 1e3;
int task, n, a[nmax + 2][nmax + 2];

vector <int> diags[2 * nmax + 2];

int main(){

    in>>task>>n;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            in>>a[i][j];
            diags[i + j - 1].push_back((i << 16) | j);
        }
    }

    for(int vall = 1, smth = 1; vall <= 2 * n - 1; vall++){
        if(vall & 1){ /// go in reverse order
            reverse(diags[vall].begin(), diags[vall].end()); 
        }

        for(auto _ : diags[vall]){
            int xx = _ >> 16, yy = _ & ((1 << 16) - 1);
            a[xx][yy] -= smth; smth++;
        }
    }

    vector <int> delta;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(!a[i][j]){ continue; }
            delta.push_back(a[i][j]);
        }; 
    }

    sort(delta.begin(), delta.end());
    auto lastt = unique(delta.begin(), delta.end());
    delta.erase(lastt, delta.end());

    if(task == 1){
        if(delta.size() == 0){ out<<"K = 0\n"; return 0; }
        if(delta.size() == 1){ out<<"K = 1\n"; return 0; }
        out<<"K > 1\n"; return 0; 
    }

    out<<delta.size()<<"\n";

    return 0;
}